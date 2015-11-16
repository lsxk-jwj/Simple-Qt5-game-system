#include "mainwindow.h"
#include "configureserverdialog.h"
#include "ui_mainwindow.h"
#include "changename.h"

extern Request request;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    // Initialize Bet
    ui->GuessNumBet->setNum(Config::GuessNumBet);
    ui->BlackJackBet->setNum(Config::BlackjackBet);

    // Initialize server configs
    this->socket = -1;
    this->serverIP = ui->serverIPDisplay->text();
    this->serverPort = ui->serverPortDisplay->text().toInt();

    // Initialize games
    this->guess_num_client = new GuessNumClient(this);
    this->blackjack_client = new BlackJackClient(this);
    this->guess_num_client->setModal(true);
    this->blackjack_client->setModal(true);

    // Initialize keep alive timer
    this->keepAlive = new QTimer();
    this->keepAlive->setInterval(Config::KeepAliveFrequency);

    // Initialize dialog
    this->initializeWaitDialog();
    this->initializeGuessNumDialogs();
    this->initializeBlackjackDialogs();

    *(user.mutable_name()) = "Anomynous";
    ui->name->setText(QString("Anomynous"));
    ui->BlackJackButton->setEnabled(false);
    ui->GuessNumButton->setEnabled(false);

    // Register custom type so QObject::connect can work
    qRegisterMetaType<System::Type>("System::Type");

    QObject::connect(ui->ConfigureServerButton,     SIGNAL(clicked()),                 this, SLOT(showServerConfigDialog()));
    QObject::connect(ui->TryConnectionButton,       SIGNAL(clicked()),                 this, SLOT(tryConnect()));
    QObject::connect(this,                          SIGNAL(connectionInvalid()),       this, SLOT(warnConnection()));
    QObject::connect(this->keepAlive,               SIGNAL(timeout()),                 this, SLOT(keepAlivePokeServer()));

    QObject::connect(this->guess_num_client,        SIGNAL(waitForRival()),            this->guessnum_congrat, SLOT(exec()));
    QObject::connect(this->guess_num_client,        SIGNAL(loseGame()),                this->guessnum_loser, SLOT(exec()));
    QObject::connect(this->guess_num_client,        SIGNAL(winGame()),                 this->guessnum_winner, SLOT(exec()));
    QObject::connect(this->guess_num_client,        SIGNAL(modify_player_money(int)),  this, SLOT(increaseMoney(int)));
    QObject::connect(this->guess_num_client,        SIGNAL(finished(int)),             this->guess_num_client, SLOT(cleanUp()));

    QObject::connect(this->blackjack_client,        SIGNAL(modify_player_money(int)),  this, SLOT(increaseMoney(int)));
    QObject::connect(this->blackjack_client,        SIGNAL(waitForRival()),            this->blackjack_wait, SLOT(exec()));
    QObject::connect(this->blackjack_client,        SIGNAL(showBlackjackResult(int,int)), this->blackjack_result_dialog, SLOT(showResult(int,int)));
    QObject::connect(this->blackjack_client,        SIGNAL(finished(int)),             this->blackjack_client, SLOT(cleanUp()));

    QObject::connect(this->blackjack_result_dialog, SIGNAL(finished(int)),             this->blackjack_client, SLOT(accept()));

    QObject::connect(ui->GuessNumButton,            &QPushButton::clicked,             [this](){ joinGame(System::GUESSNUM); });
    QObject::connect(ui->BlackJackButton,           &QPushButton::clicked,             [this](){ joinGame(System::JACK); });
    QObject::connect(this->guess_num_client,        SIGNAL(rival_die()),  this, SLOT(handleGuessNumPlayerDie()));
    QObject::connect(this->blackjack_client,        SIGNAL(rival_die()),  this, SLOT(handleBlackJackPlayerDie()));

    // Prompt for change name at startup.
    changeName();
}

MainWindow::~MainWindow(){
    delete ui;
    delete keepAlive;
    delete waitDialog;
    delete guessnum_loser; delete guessnum_winner; delete guessnum_congrat;
    delete blackjack_wait; delete blackjack_result_dialog;
}
void MainWindow::initializeWaitDialog(){
    this->waitDialog = new QDialog(this);
    auto cancel = new QPushButton("Cancel");
    auto msg    = new QLabel("Waiting for your rival to come...\n Please be patient.");
    auto layout = new QHBoxLayout();
    layout->addWidget(msg);
    layout->addWidget(cancel);
    this->waitDialog->setModal(true);
    this->waitDialog->setLayout(layout);
    this->waitDialog->setWindowTitle("Waiting for rivals");
    connect(cancel, &QPushButton::clicked, this->waitDialog, &QDialog::reject);
}
void MainWindow::initializeGuessNumDialogs(){
    guessnum_loser = new QMessageBox(this);
    guessnum_winner = new QMessageBox(this);
    guessnum_congrat = new QMessageBox(this);
    blackjack_wait = new QMessageBox(this);
    guessnum_loser->setText(
                       "<font size=18>"
                       "You're done! Unfortunately, your rival is one step further than you! <br/>"
                       "<font color=red><strong>You will lose all your bet!</strong></font>"
                       "</font>"
                );
    guessnum_winner->setText(
                       "<font size=18>"
                       "Thanks for your great patience! <br/>"
                       "<font color=green><strong>You won all the bet!</strong></font>"
                       "</font>"
                );
    guessnum_congrat->setText(
                       "<font size=18>"
                       "Congradulations! You're done! <font color=green><strong>You'll win all the bet! </strong></font><br/>"
                       "Please wait until your rival is done."
                       "</font>"
                );
    blackjack_wait->setText(
                        "<font size=18>"
                        "You're done!"
                        "</font><br/>"
                        "<font size=16>"
                        "Please wait until your rival is done.  <strong>Be patient!</strong>"
                        "</font>"
                );
}
void MainWindow::initializeBlackjackDialogs(){
    this->blackjack_result_dialog = new BlackjackResultDialog(this);
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "Leaving the game";
    request.system( System::Request_Operation_QuitGame,  [=](Model::Reply* reply){
        qDebug() << "Left the game";
        event->accept();
    });
}
void MainWindow::handleBlackJackPlayerDie(){
    increaseMoney( Config::GuessNumBet );
    guess_num_client->reject();

    QMessageBox mesg;
    mesg.setText("<font size=18>Your rival has exited the room.  Don't worry, we will give your money back.</font>");
    mesg.exec();
}
void MainWindow::handleGuessNumPlayerDie(){
    increaseMoney( Config::BlackjackBet );
    blackjack_client->reject();

    QMessageBox mesg;
    mesg.setText("<font size=18>Your rival has exited the room.  Don't worry, we will give your money back.</font>");
    mesg.exec();
}

void MainWindow::joinGame(System::Type type){
    if( this->socket == -1 ){
        emit connectionInvalid();
        return;
    }

    request.system_joinGame( type, [this, type](Model::Reply* reply){
        waitForRival(type);  
    });
}

void MainWindow::waitForRival(System::Type type){

    this->keepAlive->stop();

    auto timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(checkReady()));
    timer->start(Config::CheckReadyFrequency);

    this->waitDialog->exec();

    if( this->waitDialog->result() == QDialog::Accepted){
        timer->stop();

        // Once the player starts the game, take her bet and start the game
        if( type == System::GUESSNUM ){
            increaseMoney( (-1) * Config::GuessNumBet );
            guess_num_client->start();
        }
        else{
            increaseMoney( (-1) * Config::BlackjackBet );
            blackjack_client->start();
        }

    }
    else {
        qDebug() << "Cancel waiting\n";

        timer->stop();

        this->keepAlive->start();

        request.system( System::Request_Operation_QuitWaitRoom,  [this](Model::Reply* reply){
            qDebug() << "Room cleaned up";
        });
    }

    delete timer;
}
void MainWindow::checkReady(){
    qDebug() << "Checking if room is ready\n";
    request.system( System::Request_Operation_CheckReady, [this](Model::Reply* reply){
        if( reply->status() ){
            waitDialog->done(QDialog::Accepted);
        }
        else{
            qDebug() << "Reply: Room not ready\n";
        }
    });
}


void MainWindow::warnConnection(){
   
    qDebug() << "Invalid connection or timeout\n";
    QString warning = "Cannot connect to server at " + serverIP + ":" + QString::number(serverPort);
    ui->connectionStatus->setText(warning);
    ui->connectionStatus->setStyleSheet("color: red");

}
void MainWindow::keepAlivePokeServer(){
    qDebug() << "Poke server for every" << Config::KeepAliveFrequency << " ms\n";
    request.system(System::Request_Operation_KeepAlive, [](Model::Reply* reply){
       qDebug() << "Poke success\n";
    });

}

void MainWindow::changeName(){
    ChangeName dialog(this, this->user.name());
    dialog.setModal(true);

    if(dialog.exec() == QDialog::Accepted){
        QString newName = dialog.getName();
        if( !newName.isEmpty() ){
            *(user.mutable_name()) = newName.toStdString();
            ui->name->setText(newName);
        }

    }

}

void MainWindow::showServerConfigDialog(){
    ConfigureServerDialog dialog(this);
    dialog.setModal(true);

    if(dialog.exec() == QDialog::Accepted){

      this->serverIP = dialog.getServerIP();
      QString serverPortStr = dialog.getServerPort();

      ui->serverIPDisplay->setText(serverIP);
      ui->serverPortDisplay->setText(serverPortStr);

      this->serverPort = serverPortStr.toInt();

      qDebug() << "Setting server ip: " << serverIP << " port: " << serverPort << "\n";

    }
}
void MainWindow::tryConnect(){

    // If there has been any connection, close it first
    if( this->socket > 0 ){
        qDebug() << "Make the connection again";
        this->keepAlive->stop();
        request.system(System::Request_Operation_QuitGame, [this](Model::Reply* reply){});

        QThread::sleep(1);

        this->socket = -1;
        makeConnection();
        qDebug() << "Quit the game";

    }
    else{
        this->makeConnection();
    }
}
void MainWindow::increaseMoney(int amount){
    qDebug() << "Money changed to: " << user.money() + amount;
    user.set_money( user.money() + amount );
    ui->money->setNum( user.money() );
}
void MainWindow::makeConnection(){

    const char* ip = serverIP.toStdString().c_str();
    if( ( this->socket = connection.useAsClient(serverPort, ip ) ) > 0 ){
        ui->connectionStatus->setText("You're connected!");
        ui->connectionStatus->setStyleSheet("color: green");

        qDebug() << "Connect to server successfully\n";
        request.setUp(this->socket);
        
        this->keepAlive->start();

        if( !user.has_id() ){
            request.system_newUser( user.name(), [this](Model::Reply* reply){
                qDebug() << "New user done\n";
                initializeUser(reply->system().user());
            });
        }
    }
    else{
      emit connectionInvalid();
    }

}

void MainWindow::initializeUser( const System::User& user_info ){

    // Set initial money
    increaseMoney( user_info.money() );
    ui->BlackJackButton->setEnabled(true);
    ui->GuessNumButton->setEnabled(true);
}
