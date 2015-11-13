#include "systemrequest.h"

SystemRequest::SystemRequest()
{
}

void SystemRequest::joinGame( System::Type type, CallBack callback ){
    auto req = new Model::Request();
    auto sys_req = req->mutable_system();
    sys_req->set_operation(System::Request_Operation_JoinGame);
    sys_req->set_game_type(type);
    registerRequest( req, callback );
}
void SystemRequest::newUser( std::string& name, CallBack callback ){
    auto req = new Model::Request();
    auto sys_req = req->mutable_system();
    sys_req->set_operation(System::Request_Operation_NewUser);
    sys_req->set_name(name);
    registerRequest( req, callback );
}
void SystemRequest::system( System::Request::Operation op, CallBack callback ){
    auto req = new Model::Request();
    req->mutable_system()->set_operation(op);
    registerRequest( req, callback );
}
