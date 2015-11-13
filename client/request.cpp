#include "request.h"

void Request::guessnum_submit( GuessNum::Guesses* guesses, Callback callback ){
    auto req = new Model::Request();
    auto guessnum_req = req->mutable_guess_num();
    guessnum_req->set_allocated_submission(guesses);
    guessnum_req->set_command(GuessNum::SUBMIT);
    registerRequest( req, callback );
}
void Request::blackjack( BlackJack::Command cmd, Callback callback ){
    auto req = new Model::Request();
    req->mutable_blackjack()->set_command(cmd);
    registerRequest( req, callback );
}
void Request::blackjack_hit( bool acted_on_deck2, Callback callback ){
    auto req = new Model::Request();
    req->mutable_blackjack()->set_command(BlackJack::HIT);
    req->mutable_blackjack()->set_flag(acted_on_deck2);
    registerRequest( req, callback );
}
void Request::blackjack_set_finish( bool deck2_the_best, Callback callback ){
    auto req = new Model::Request();
    req->mutable_blackjack()->set_command(BlackJack::FINISH);
    req->mutable_blackjack()->set_flag(deck2_the_best);
    registerRequest( req, callback );
}

void Request::system_joinGame( System::Type type, Callback callback ){
    auto req = new Model::Request();
    auto sys_req = req->mutable_system();
    sys_req->set_operation(System::Request_Operation_JoinGame);
    sys_req->set_game_type(type);
    registerRequest( req, callback );
}
void Request::system_newUser( const std::string& name, Callback callback ){
    auto req = new Model::Request();
    auto sys_req = req->mutable_system();
    sys_req->set_operation(System::Request_Operation_NewUser);
    sys_req->set_name(name);
    registerRequest( req, callback );
}
void Request::system( System::Request::Operation op, Callback callback ){
    auto req = new Model::Request();
    req->mutable_system()->set_operation(op);
    registerRequest( req, callback );
}
void Request::setUp(int _socket){
    socket = _socket;
    processor.setMaxThreadCount(10);
}

void Request::registerRequest( Model::Request* req, Callback callback ){
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

