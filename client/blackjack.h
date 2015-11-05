#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <QDialog>

namespace Ui {
class BlackJackClient;
}

class BlackJackClient : public QDialog
{
    Q_OBJECT

public:
    explicit BlackJackClient(QWidget *parent = 0);
    ~BlackJackClient();

private:
    Ui::BlackJackClient *ui;
};

#endif // BLACKJACK_H
