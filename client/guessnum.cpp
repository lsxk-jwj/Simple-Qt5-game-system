#include "guessnum.h"
#include "ui_guessnum.h"
#include "config.h"
#include <QMessageBox>
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

    connect(updator,SIGNAL(timeout()),this,SLOT(update()));
    connect(ui->submit, SIGNAL(clicked()), this, SLOT(submitAnswer()));
}


GuessNumClient::~GuessNumClient()
{
    for( int i = 0 ; i < 4; ++i){
        delete magic_numbers[i];
        delete guess_numbers[i];
    }
    delete ui;
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
                                 "font-size: 30px;"
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
    ui->result->setText( QString::number(resultA) + QString("A") + QString::number(resultB) + QString("B") );
    if( resultA == 4 ){
        QMessageBox congrat;
        congrat.setText("Congradulations! You're done! Please wait until your rival is done");
        congrat.exec();
        waitRivalDone();
    }
}
void GuessNumClient::waitRivalDone(){

}

void GuessNumClient::update(){
    request.system( System::Request_Operation_RivalMeta, [this](Model::Reply* reply){
        qDebug() << "Got rival meta";
    });

}
