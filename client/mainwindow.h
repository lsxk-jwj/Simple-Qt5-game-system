#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtDebug>
#include <QTimer>
#include <QEventLoop>
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <QMainWindow>
#include "connection.hpp"
#include "main.model.pb.h"
#include "request.h"
#include "guessnum.h"
#include "blackjack.h"
#include "config.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void showServerConfigDialog();
    void warnConnection();
    void changeName();
    void tryConnect();
    void checkReady();
    void keepAlivePokeServer();
signals:
    void connectionInvalid();

private:

    void initializeWaitDialog();
    void makeConnection();
    void waitForRival();
    void joinGame(System::Type t);
    void startGame();

    System::User user;
    Ui::MainWindow *ui;
    QDialog* waitDialog;
    QTimer* keepAlive;
    Connection connection;
    QString serverIP;
    Request request;
    int serverPort;
    int socket;

    // Game
    GuessNumClient* guess_num_client;
    BlackJackClient* blackjack_client;

};

#endif // MAINWINDOW_H
