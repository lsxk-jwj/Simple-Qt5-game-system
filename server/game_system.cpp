#include "game_system.hpp"

GameSystem::GameSystem(Connection&& conn, std::map<std::string,std::string>&& config): 
    connection(conn), 
    initial_money( std::stoi(config["CONFIG::initial_money"]) ) {

    guess_num = new GuessNumServer( std::stoi(config["GUESSNUM::room_number"]), std::stoi(config["GUESSNUM::play_number"]) );
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

    Connection::set_timeout(req_socket);

    System::User user;

    while(1){

        Model::Request request;
        if( !Connection::receive_message(req_socket, request) ){
            /* TODO */
            /* Handle Timeout */
            Connection::send_error("Fail reading request from socket " + std::to_string(req_socket));
            return;
        }
        
        bool ok = false;
        Model::Reply response;

        if( request.has_black_jack() ){
            // ok = guess_num->handle_req( request.user_id(), request.guess_num(), response );
        }
        else if( request.has_guess_num() ){
            ok = guess_num->handle_req( user, request.guess_num(), response );
        }
        else if( request.has_system() ){
            const System::Request& req = request.system();
            if( req.has_join() ){
                ok = this->join_game( user, req.join().game_type(), response );
            }
            else if( req.has_new_user() ){
                ok = this->add_user( response );
                user = response.system().user();
            }
        }

        if( !ok )
            response.set_status(false); 
        else
            response.set_status(true);

        if( !Connection::send_message(req_socket, response) ){
            /* TODO */
            /* Handle Timeout */
        }
    }
}

bool GameSystem::join_game( System::User& user , System::Request_Type game_type, Model::Reply& response ){
    switch( game_type ){
        case System::Request_Type_GUESSNUM:
            guess_num->add_user( user, response );
            set_response( user, response );
            break;
        case System::Request_Type_JACK:
            break;
    }
}
bool GameSystem::add_user( Model::Reply& response ){
    
    auto user = System::User();
    user.set_money( initial_money );
    user.set_id( generate_new_id() );
    set_response( user, response );
    return true;
}

void GameSystem::set_response( System::User& user, Model::Reply& response ){

    System::Reply* sys = response.mutable_system();
    System::Reply res;
    System::User* _user = res.mutable_user();

    *_user = user;
    *sys = res;
}
int GameSystem::generate_new_id(){
    std::srand(std::time(0)); // use current time as seed for random generator
    return std::rand();
}
