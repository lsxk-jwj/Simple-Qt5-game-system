#ifndef GuessNumClient_H
#define GuessNumClient_H

#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QList>
#include <QLabel>
#include <QTimer>
#include <QLineEdit>

namespace Ui {
class GuessNumClient;
}

class GuessNumClient : public QDialog
{
    Q_OBJECT

public:
    explicit GuessNumClient(QWidget *parent = 0);
    ~GuessNumClient();

private slots:

    void submitAnswer();
    void update();

private:

    void setUpDisplay();

    Ui::GuessNumClient *ui;
    QList<QLabel*> magic_numbers;
    QList<QLineEdit*> guess_numbers;
};

#endif // GuessNumClient_H
