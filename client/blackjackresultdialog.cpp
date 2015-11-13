#include "blackjackresultdialog.h"
#include "ui_blackjackresultdialog.h"

BlackjackResultDialog::BlackjackResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlackjackResultDialog)
{
    ui->setupUi(this);


}

BlackjackResultDialog::~BlackjackResultDialog()
{
    delete ui;
}

void BlackjackResultDialog::showResult( int you_vs_dealer, int you_vs_rival ){
    QString balance;
    setMessage(you_vs_dealer, ui->dealer_result, balance);
    setMessage(you_vs_rival, ui->rival_result, balance);
    ui->bet_balance->setText(balance);

    this->exec();
}

void BlackjackResultDialog::setMessage(int result, QLabel* result_label, QString& balance){
    static const QString win_mesg = QString("<font color=green>You win!</font>");
    static const QString lose_mesg = QString("<font color=red>You lose!</font>");
    static const QString tie_mesg = QString("<font color=red>There is a tie</font>");

    static const QString win_bal_mesg =
       QString("<font color=green> +") + QString::number(Config::BlackjackBet) + QString("</font>");
    static const QString tie_bal_mesg =
       QString("<font color=grey> +0</font>");
    static const QString lose_bal_mesg =
       QString("<font color=green> -") + QString::number(Config::BlackjackBet) + QString("</font>");

    if( result > 0 ){
        result_label->setText(win_mesg);
        balance.append(win_bal_mesg);
    }
    else if( result == 0 ){
        result_label->setText(lose_mesg);
        balance.append(lose_bal_mesg);
    }
    else{
        result_label->setText(tie_mesg);
        balance.append(win_bal_mesg);
    }

}
