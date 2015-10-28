#include "game_system.hpp"

GameSystem::GameSystem(Connection&& conn, std::map<std::string,std::string>&& config): 
    connection(conn), 
    initial_money( std::stoi(config("CONFIG::initial_money")) ) {

    guess_num = new GuessNum( std::stoi(config["GUESSNUM::room_number"]), std::stoi(config["GUESSNUM::play_number"]) );
    if( initial_money <= 0 ){
        std::cerr << "Possible Corruption: InitialMoney set to " << initial_money << std::endl;
    }

}
void GameSystem::start(){
    while(1){
        int req = connection.accept();        
        std::thread( &GameSystem::process, this, req );
        ::close(req);
    }
}

void GameSystem::process(int req_socket){


    while(1){

        Model::Request request;
        if( !Connection::receive_message(req_socket, request) ){
            Connection::send_error("Fail reading request from socket " + std::to_string(req_socket));
            return;
        }
        
        bool ok = false;
        Model::Reply response;
        switch(request.type()){
            case Model::System_Type_JACK: 
                ok = guess_num->handle_req( request.user_id(), std::move(request.guess_num), response );
                break;
            case Model::System_Type_GUESSNUM: 
                ok = guess_num->handle_req( request.user_id(), std::move(request.guess_num), response );
                break;
            case Model::System_Type_SYS: 
                ok = this->handle_req( request.user_id(), std::move(request.system), response );
                break;
        }

        if( !ok )
            response.set_status(false); 
        else
            response.set_status(true);

        Connection::send_message(req_socket, response);
    }
}


void GameSystem::handle_req( int user_id, Model::Request&& req, Model::Reply& response ){
    switch(req.type()){
        case Model::System_Request_Type_JOIN:
            return joinGame( user_id, req.join.game_type(), response );
        case Model::System_Request_Type_NEWUSER:
            return addUser( req.new_user.name(), response );
    }

}

bool GameSystem::joinGame( int user_id, Model::System_Type game_type, Model::Reply& response ){

}
bool GameSystem::addUser( const std::string& new_user_name, Model::Reply& response ){
    
    auto user = new Model::User();
    user->set_name( new_user_name );
    user->set_money( initial_money );

    int new_id;
    std::lock_guard<std::mutex> guard(m);

    if( available_index.size() == 0 ){
        new_id = user_list.size();  
        user_list.push_back(user);
    }
    else {
       new_id = available_index.top();
       available_index.pop();
    }
    
    user->set_id( new_id );

    Model::System_Reply res;
    res.set_user( *user );
    response_sucess( res, response ); 
    return true;
}

void response_sucess( Model::System_Reply& res, Model::Reply& response ){
    response.set_system( res );
}
