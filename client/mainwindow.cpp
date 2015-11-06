#include "mainwindow.h"
#include "configureserverdialog.h"
#include "ui_mainwindow.h"
#include "changename.h"

extern Request request;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    this->socket = -1;
    this->serverIP = ui->serverIPDisplay->text();
    this->serverPort = ui->serverPortDisplay->text().toInt();
    this->guess_num_client = new GuessNumClient(this);
    this->blackjack_client = new BlackJackClient(this);
    this->guess_num_client->setModal(true);
    this->blackjack_client->setModal(true);
    this->keepAlive = new QTimer();
    this->keepAlive->setInterval(Config::KeepAliveFrequency);
    this->initializeWaitDialog();


    *(user.mutable_name()) = "Anomynous";
    ui->name->setText(QString("Anomynous"));
    ui->BlackJackButton->setEnabled(false);
    ui->GuessNumButton->setEnabled(false);

    QObject::connect(ui->ChangeNameButton,      SIGNAL(clicked()),           this, SLOT(changeName()));
    QObject::connect(ui->ConfigureServerButton, SIGNAL(clicked()),           this, SLOT(showServerConfigDialog()));
    QObject::connect(ui->TryConnectionButton,   SIGNAL(clicked()),           this, SLOT(tryConnect()));
    QObject::connect(this,                      SIGNAL(connectionInvalid()), this, SLOT(warnConnection()));
    QObject::connect(this->keepAlive,           SIGNAL(timeout()), this, SLOT(keepAlivePokeServer()));
    QObject::connect(ui->GuessNumButton,        &QPushButton::clicked, [this](){ joinGame(System::GUESSNUM); });
    QObject::connect(ui->BlackJackButton,       &QPushButton::clicked, [this](){ joinGame(System::JACK); });
}

MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::initializeWaitDialog(){
    this->waitDialog = new QDialog(this);
    auto cancel = new QPushButton("Cancel");
    auto msg    = new QLabel("Waiting for your rival to come...\n Please be patient.");
    auto layout = new QHBoxLayout();
    layout->addWidget(msg);
    layout->addWidget(cancel);
    this->waitDialog->setLayout(layout);
    this->waitDialog->setWindowTitle("Waiting for rivals");
    connect(cancel, &QPushButton::clicked, this->waitDialog, &QDialog::reject);
}

void MainWindow::joinGame(System::Type type){
    if( this->socket == -1 ){
        emit connectionInvalid();
        return;
    }
    qDebug() << "Joining game\n";

    request.system_joinGame( type, [this, type](Model::Reply* reply){
        waitForRival(type);
    });
}

void MainWindow::waitForRival(System::Type type){

    qDebug() << "Waiting for new rivals\n";

    this->keepAlive->stop();

    auto timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(checkReady()));
    timer->start(Config::CheckReadyFrequency);

    this->waitDialog->exec();

    if( this->waitDialog->result() == QDialog::Accepted){
        timer->stop();
        if( type == System::GUESSNUM ){
            qDebug() << "Starting guess num";
            guess_num_client->start();
        }
        else {
            qDebug() << "Starting blackjack";
            // blackjack_client->start();
        }
    }
    else {
        qDebug() << "Cancel waiting\n";

        this->keepAlive->start();

        request.system( System::Request_Operation_QuitRoom,  [this](Model::Reply* reply){
            qDebug() << "Room cleaned up";
        });
    }
}
void MainWindow::checkReady(){
    qDebug() << "Checking if room is ready\n";

    request.system( System::Request_Operation_CheckReady, [this](Model::Reply* reply){
        if( reply->status() ){
            waitDialog->done(QDialog::Accepted);
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
        *(user.mutable_name()) = newName.toStdString();
        ui->name->setText(newName);
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
        request.system(System::Request_Operation_QuitGame, [this](Model::Reply* reply){
            makeConnection();
        });
    }
    else{
        this->makeConnection();
    }
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

    user.set_money( user_info.money() );
    ui->money->setText(QString::number(user.money()));
    ui->BlackJackButton->setEnabled(true);
    ui->GuessNumButton->setEnabled(true);
}
