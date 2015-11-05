#include "guessnum.h"
#include "ui_guessnum.h"
#define UPDATE_FREQUENCY 3000

GuessNumClient::GuessNumClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuessNumClient)
{
    ui->setupUi(this);

    setUpDisplay();
    QTimer* updator = new QTimer;  
    updator->start(UPDATE_FREQUENCY);

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

void GuessNumClient::setUpDisplay(){

    for( int i = 0 ; i < 4; ++i ){
        int random_num = i;
        QLabel* magic_num = new QLabel("?");
        magic_num->setAlignment(Qt::AlignCenter);
        magic_num->setStyleSheet("border: 1px solid grey;"
                                 "font-size: 30px;"
                                 );

        magic_numbers.push_back(magic_num);
        ui->magic_numbers->addWidget(magic_num);
    }

    for( int i = 0 ; i < 4; ++i ){
        QLineEdit* guess_num = new QLineEdit("");
        guess_numbers.push_back(guess_num);
        guess_num->setAlignment(Qt::AlignCenter);
        guess_num->setMaxLength(1);
        guess_num->setStyleSheet("font-size: 30px; line-height: 45px");
        ui->guess_numbers->addWidget(guess_num);
    }
}

void GuessNumClient::submitAnswer(){

    ui->result->setText("Checking...");
    for( int i = 0 ; i < 4; ++i ){


    }

}

void GuessNumClient::update(){


}
