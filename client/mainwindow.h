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
#include "blackjackresultdialog.h"
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
    void tryConnect();
    void checkReady();
    void keepAlivePokeServer();
    void increaseMoney(int amount);

signals:
    void connectionInvalid();

private:

    void initializeWaitDialog();
    void initializeGuessNumDialogs();
    void initializeBlackjackDialogs();
    void initializeUser(const System::User& user);
    void changeName();
    void makeConnection();
    void waitForRival(System::Type t);
    void joinGame(System::Type t);
    void startGame();


    System::User user;
    Ui::MainWindow *ui;
    QDialog* waitDialog;
    QTimer* keepAlive;
    Connection connection;
    QString serverIP;
    int serverPort;
    int socket;

    // Game
    GuessNumClient* guess_num_client;
    BlackJackClient* blackjack_client;
    BlackjackResultDialog* blackjack_result_dialog;

    // Dialogs for Guess Number
    QMessageBox* guessnum_congrat;
    QMessageBox* guessnum_loser;
    QMessageBox* guessnum_winner;

    // Dialogs for Blackjack
};

#endif // MAINWINDOW_H
