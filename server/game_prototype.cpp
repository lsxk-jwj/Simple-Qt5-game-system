#include "game_prototype.hpp"

bool GamePrototype::do_operation( System::Request::Operation op, System::User& current_user, System::User* user_info_response ){

    if( op == System::Request_Operation_JoinGame )
        return add_player( current_user );

    GameRoom* room = nullptr;

    mutex.lock();

    if( rooms_in_game.find( current_user.room_id() ) != rooms_in_game.end() ){
        room = rooms_in_game[ current_user.room_id() ];
    }

    mutex.unlock();

    int id = current_user.id();
    switch( op ){

        case System::Request_Operation_CheckReady:
            return room;

        case System::Request_Operation_CheckFinish:
            return check_rival_finish( room, id );

        case System::Request_Operation_RivalMeta:
            return get_rival_meta( room, id, user_info_response );

        case System::Request_Operation_RivalName:
            return get_rival_name( room, id, user_info_response );

        case System::Request_Operation_QuitRoom:
            return quit_room( current_user.room_id() );

        default:
            std::cerr << "Invalid operation issue\n";
            return false;
    }

}

bool GamePrototype::get_rival_meta( GameRoom* room, int user_id, System::User* rival ){
    if( room ) return room->get_rival_meta( user_id, rival ); 
}

bool GamePrototype::get_rival_name( GameRoom* room, int user_id, System::User* rival ){
    if( room ) return room->get_rival_name( user_id, rival ); 
}

bool GamePrototype::check_rival_finish( GameRoom* room, int user_id ){
    if( room ){
        user_id = user_id == 1 ? 0 : 1; // rival id
        return room->check_finish( user_id );
    }
    return true;
}
bool GamePrototype::add_player( System::User& current_user ){
    GameRoom* new_room;
    int room_id; 
    int user_index; // user's index in room

    std::lock_guard<std::mutex> lock(mutex);

    if( rooms_in_wait.empty() ){
        new_room = new GameRoom( playerNum );
        room_id = generate_room_id();
        user_index = 0; // The first player in room
        rooms_in_wait.push( std::make_pair( room_id, new_room ) );
        std::cerr << "Creating new room of id " << room_id << std::endl;
    }
    else{
        room_id  = rooms_in_wait.front().first;
        new_room = rooms_in_wait.front().second;
        user_index = 1; // The second player in room

        rooms_in_game.insert( rooms_in_wait.front() );
        rooms_in_wait.pop();
        this->initialize( room_id );
        std::cerr << "Starting a new room of id " << room_id << std::endl;
    }

    new_room->add_player( current_user );
    current_user.set_room_id( room_id );
    current_user.set_id( user_index );
    std::cerr << "Adding user into room id: " << room_id << std::endl;

    return true;
}
bool GamePrototype::quit_room( int room_id ){
    if( rooms_in_game.find( room_id ) != rooms_in_game.end() ){
        delete rooms_in_game[ room_id ];
        rooms_in_game.erase( room_id );
    }
    return true;
}
int GamePrototype::generate_room_id(){
    std::srand(std::time(0)); // use current time as seed for random generator
    return std::rand();
}
