#ifndef BLACKJACKRESULTDIALOG_H
#define BLACKJACKRESULTDIALOG_H

#include <QDialog>
#include "blackjack.h"
#include "config.h"

namespace Ui {
class BlackjackResultDialog;
}

class BlackjackResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BlackjackResultDialog(QWidget *parent = 0);
    ~BlackjackResultDialog();

public slots:
    void showResult( int you_vs_dealer, int you_vs_rival );

private:

    void setMessage(int result, QLabel* result_label, QString& balance);

    Ui::BlackjackResultDialog *ui;

};

#endif // BLACKJACKRESULTDIALOG_H
