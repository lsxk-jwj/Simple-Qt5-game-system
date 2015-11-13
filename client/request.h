#ifndef REQUEST_H
#define REQUEST_H

#include <QThreadPool>
#include <QRunnable>
#include <QDebug>
#include <QDebug>
#include <functional>
#include "main.model.pb.h"
#include "connection.hpp"

using Callback = std::function<void(Model::Reply*)>;

class RequestProcessor : public QObject,  public QRunnable
{
    Q_OBJECT

    int socket;
    Model::Reply* reply;
    Model::Request* request;
signals:
    void send_fail();
    void receive_fail();
    void receive_done(Model::Reply* reply);

public:
    RequestProcessor(int _socket, Model::Request* req);
    void run();
};

class Request: public QObject {

    Q_OBJECT

    int socket;
    QThreadPool processor;

public:

    void setUp(int _socket);

    // System-wide requests
    void system( System::Request::Operation, Callback callback );
    void system_joinGame( System::Type type, Callback callback );
    void system_newUser( const std::string& name, Callback callback );

    // Requests specific to guess_num
    void guessnum_submit( GuessNum::Guesses* guesses, Callback callback );

    // Requests specific to blackjack
    void blackjack( BlackJack::Command cmd, Callback callback );
    void blackjack_hit( bool acted_on_deck2, Callback callback);
    void blackjack_set_finish( bool deck2_the_best, Callback callback );

private slots:
    void send_fail();
    void receive_fail();

protected:
    void registerRequest( Model::Request* req, std::function<void(Model::Reply*)> callback );

};




#endif // REQUEST_H
