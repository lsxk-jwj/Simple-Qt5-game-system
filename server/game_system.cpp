#include "game_system.hpp"

Connection connection;
GuessNumServer* guess_num;

void initialize_game(Connection&& conn){
    connection = conn; 
    guess_num = new GuessNumServer(CONFIG::ROOM_NUMBER, CONFIG::PLAYER_NUMBER);
}

void start_game(){

    while(1){
        int req = connection.accept();        
        std::cerr << "New connection: fd = " << req << std::endl;

        if( req < 0 )
            std::cerr << "Fail accepting incomming connection\n";
        else{
            std::thread spawn( process, req );
            spawn.detach();
        }
    }
}

static void process(int req_socket){

    Connection::set_timeout(req_socket);

    System::User user;

    int timeout_count = 0;

    bool keep_running = true;

    while(keep_running){

        Model::Request request;
        if( !Connection::receive_message(req_socket, request) ){
            /* Handle Timeout */
            std::cerr << "Error or timeout\n"; 

            ++timeout_count;
            if( user.has_room_id() /* If the user is in some game */){ 
                if( timeout_count > BUSY_TIMEOUT_LIMIT ){
                    /* purge game  */
                    // return;
                }
            }
            else if( timeout_count > IDE_TIMEOUT_LIMIT ){ 
                // return;
            }
        }
        else{

            std::cerr << "Getting a new request\n";
            timeout_count = 0;
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

            if( req.operation() == System::Request_Operation_KeepAlive )
                continue;

            switch( req.operation() ){
                case System::Request_Operation_Update:
                    ok = update_player_list( user.room_id(), req.game_type() );
                    break;
                case System::Request_Operation_CheckReady:
                    ok = check_ready( user, req.game_type() );
                    break;
                case System::Request_Operation_JoinGame:
                    ok = join_game( user, req.game_type(), response );
                    break;
                case System::Request_Operation_NewUser:
                    ok = add_user( response );
                    user = response.system().user();
                    break;
                case System::Request_Operation_QuitRoom:
                    // TODO
                    break;
                case System::Request_Operation_QuitGame:
                    ok = true;
                    keep_running = false;
                    break;
            }
        }

        if( !ok )
            response.set_status(true);
        else
            response.set_status(false); 

        if( !Connection::send_message(req_socket, response) ){
            /* TODO */
            /* Handle Timeout */
        }
    }

    /* Do some cleanup here */

    std::cerr << "Connection fd = " << req_socket << " closed\n";

    ::close( req_socket );

}

static bool update_player_list( int room_id, System::Type game_type ){

    System::PlayerList players;

    switch( game_type ){
        case System::GUESSNUM:
            return guess_num->get_players( room_id, players );
            break;
        case System::JACK:
            // return guess_num->get_players( room_id, players );
            break;
    }
}
static bool check_ready( System::User& user, System::Type game_type ){
    switch( game_type ){
        case System::GUESSNUM:
            return guess_num->check_game_ready( user.room_id() );
            break;
        case System::JACK:
            // return guess_num->check_game_ready( user );
            break;
    }
}
static bool join_game( System::User& user , System::Type game_type, Model::Reply& response ){
    switch( game_type ){
        case System::GUESSNUM:
            guess_num->add_player( user );
            break;
        case System::JACK:
            break;
    }

    set_response( user, response );
}
static bool add_user( Model::Reply& response ){
    
    auto user = System::User();
    user.set_money( CONFIG::INITIAL_MONEY );
    user.set_id( generate_new_id() );
    set_response( user, response );
    return true;
}

static void set_response( System::User& user, Model::Reply& response ){

    System::Reply* sys = response.mutable_system();
    System::Reply res;
    System::User* _user = res.mutable_user();

    *_user = user;
    *sys = res;
}
static int generate_new_id(){
    std::srand(std::time(0)); // use current time as seed for random generator
    return std::rand();
}
