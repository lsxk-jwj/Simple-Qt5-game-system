#include "request.h"

void Request::setUp(int _socket){
    socket = _socket;
    processor.setMaxThreadCount(10);
}

void Request::registerRequest( Model::Request* req, CallBack callback ){
    RequestProcessor* worker = new RequestProcessor(socket, req);
    QObject::connect(worker, &RequestProcessor::receive_done, 
        [=]( Model::Reply* reply){ 
            callback(reply);
            delete reply;
        }
    );
    QObject::connect(worker, &RequestProcessor::receive_fail, this, &Request::receive_fail );
    QObject::connect(worker, &RequestProcessor::send_fail, this, &Request::send_fail );
    processor.start(worker); // Let threadpool take over RequestProcessor, no need to delete it
}
void Request::joinGame( System::Type type, CallBack callback ){
    auto req = new Model::Request();
    auto sys_req = req->mutable_system();
    sys_req->set_operation(System::Request_Operation_JoinGame);
    sys_req->set_game_type(type);
    registerRequest( req, callback );
}
void Request::system( System::Request::Operation op, CallBack callback ){
    auto req = new Model::Request();
    req->mutable_system()->set_operation(op);
    registerRequest( req, callback );
}

void Request::receive_fail(){
    qDebug() << "Receive fail\n";
}
void Request::send_fail(){
    qDebug() << "Send fail\n";
}

RequestProcessor::RequestProcessor(int _socket, Model::Request* req ): socket(_socket), request(req){}

void RequestProcessor::run()
{
    qDebug() << "Sending requests\n";

    auto reply = new Model::Reply();

    if( !Connection::send_message(socket, *request) ){
        qDebug() << "Sending: error or timeout\n";

        emit send_fail();
        return;
    }
    else{
        delete request;
    }

    if( Connection::receive_message(socket, *reply) ){    
        emit receive_done(reply);
    }
    else{
        qDebug() << "Receiving: error or timeout\n";
        emit receive_fail();
    }
}

