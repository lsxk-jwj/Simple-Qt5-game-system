#include "guessnum.h"
#include "ui_guessnum.h"
#include "config.h"

#define UPDATE_FREQUENCY 3000

extern Request request;

GuessNumClient::GuessNumClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuessNumClient)
{
    ui->setupUi(this);

    setUpDisplay();

    updator = new QTimer;
    updator->setInterval(Config::GameMetaUpdateFrequency);

    waitRivalTimer = new QTimer;
    waitRivalTimer->setInterval(Config::CheckRivalFinishFrequency);

    connect(updator,SIGNAL(timeout()),this,SLOT(update()));
    connect(waitRivalTimer,SIGNAL(timeout()),this,SLOT(checkRivalFinish()));
    connect(ui->submit, SIGNAL(clicked()), this, SLOT(submitAnswer()));
}


GuessNumClient::~GuessNumClient()
{
    delete ui; 
}
void GuessNumClient::cleanUp(){
    updator->stop();
    waitRivalTimer->stop();

    for( int i = 0 ; i < 4; ++i){
        delete magic_numbers[i];
        delete guess_numbers[i];
    }
    delete updator;
    delete waitRivalTimer;
}

void GuessNumClient::start(){
    request.system( System::Request_Operation_RivalName, [this](Model::Reply* reply){
        qDebug() << "Got rival name: " << QString::fromStdString( reply->system().user().name() );
        ui->RivalName->setText(QString::fromStdString( reply->system().user().name() ));
        updator->start();
        this->exec();
    });
}

void GuessNumClient::setUpDisplay(){

    for( int i = 0 ; i < 4; ++i ){
        QLabel* magic_num = new QLabel("?");
        magic_num->setAlignment(Qt::AlignCenter);
        magic_num->setStyleSheet("border: 1px solid grey;"
                                 "font-size: 30px; line-height: 45px"
                                 );

        magic_numbers.push_back(magic_num);
        ui->magic_numbers->addWidget(magic_num);
    }

    auto validator = new QIntValidator(0, 10, this);
    for( int i = 0 ; i < 4; ++i ){
        QLineEdit* guess_num = new QLineEdit("");
        guess_numbers.push_back(guess_num);
        guess_num->setAlignment(Qt::AlignCenter);
        guess_num->setMaxLength(1);
        guess_num->setStyleSheet("font-size: 30px; line-height: 45px");
        guess_num->setValidator(validator);
        ui->guess_numbers->addWidget(guess_num);
    }
}

void GuessNumClient::submitAnswer(){
    ui->result->setText("Checking...");

    bool duplicate = false;
    auto guesses = new GuessNum::Guesses();

    for( int i = 0 ; i < 4; ++i ){
        int guess = guess_numbers[i]->text().toInt();
        for( int j = 0; j < i; ++j ){
            if( guess == guesses->guesses(j) ){
                duplicate = true;
                break;
            }
        }
        guesses->add_guesses(guess);
    }

    if( duplicate ){
        delete guesses;
        QMessageBox warning;
        warning.setText("Your guesses contain duplicates!!  This is not allowed!");
        warning.exec();
        ui->result->setText("None");
    }
    else{
        request.guessnum_submit(guesses, [this](Model::Reply* reply){
            qDebug() << "submittion done";
            auto res = reply->guess_num();
            setGuessResult(res.result_a(), res.result_b());
        });
    }

}
void GuessNumClient::setGuessResult(int resultA, int resultB ){
    round++; // Increment the number of rounds
    ui->round->setNum(round);

    ui->result->setText( QString::number(resultA) + QString("A ") + QString::number(resultB) + QString("B ") );
    if( resultA == 4 ){ // If you're done
        setMagicNumber();
        request.system( System::Request_Operation_CheckFinish, [this](Model::Reply* reply){
            if(reply->status()){
                emit loseGame(); // Your rival has already done, so you lose.
                you_loseGame();
            }
            else{
                emit waitForRival(); // You finish the puzzle before your rival, so you win!  Now wait for your rival.
                you_waitForRival();
            }

        });

    }
}
void GuessNumClient::checkRivalFinish(){
    request.system( System::Request_Operation_CheckFinish, [this](Model::Reply* reply){
        if(reply->status()){
            emit winGame();
            you_winGame();
        }
    });
}
void GuessNumClient::setMagicNumber(){
    for( int i = 0; i < 4; ++i ){
        magic_numbers[i]->setText(guess_numbers[i]->text());
        magic_numbers[i]->setStyleSheet("background-color: rgb(254, 223, 187);"
                                        "font-size: 30px; line-height: 45px;"
                                        "border: 1px solid grey;");
    }
}

void GuessNumClient::update(){
    request.system( System::Request_Operation_RivalMeta, [this](Model::Reply* reply){
        qDebug() << "Got rival meta";
        ui->RivalRound->setText(QString::number(reply->system().user().meta().guess_num().round()));
    });
}
void GuessNumClient::you_waitForRival(){
    qDebug() << "You win the game, now wait for rival";
    updator->stop();
    waitRivalTimer->start();

}
void GuessNumClient::you_loseGame(){
    updator->stop();
    this->done(QDialog::Rejected);
}

void GuessNumClient::you_winGame(){
    qDebug() << "Rival has done.  You win the game";
    waitRivalTimer->stop();
    QThread::msleep(2000);

    // You earn these money.  Balanced in main window
    emit modifyPlayerMoney( 2 * Config::GuessNumBet );

    request.system( System::Request_Operation_QuitRoom, [this](Model::Reply* reply){
        this->done(QDialog::Accepted);
    });

}
