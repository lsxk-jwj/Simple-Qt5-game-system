#include "blackjack.h"
#include "ui_blackjack.h"

BlackJackClient::BlackJackClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlackJackClient)
{
    ui->setupUi(this);
}

BlackJackClient::~BlackJackClient()
{
    delete ui;
}
