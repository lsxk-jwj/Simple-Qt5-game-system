#ifndef REQUEST_H
#define REQUEST_H

#include <QThreadPool>
#include <QRunnable>
#include <QDebug>
#include <functional>
#include "main.model.pb.h"
#include "connection.hpp"

using CallBack = std::function<void(Model::Reply*)>;

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
    void joinGame( System::Type type, CallBack callback );
    void system( System::Request::Operation, CallBack callback );

public slots:
    void send_fail();
    void receive_fail();

private:
    void registerRequest( Model::Request* req, std::function<void(Model::Reply*)> callback );

};




#endif // REQUEST_H