#include "game_prototype.hpp"

bool GamePrototype::do_operation( System::Request::Operation op, System::User& current_user, System::User* user_info_response ){

    if( op == System::Request_Operation_JoinGame )
        return add_player( current_user );

    GameRoom* room = nullptr;

    mutex.lock();
    
    if( room_exist(current_user.room_id()) ){
        room = rooms_in_game[ current_user.room_id() ];
    }

    mutex.unlock();

    int id = current_user.id();
    int room_id = current_user.room_id();

    switch( op ){

        case System::Request_Operation_CheckReady:
            return room;

        case System::Request_Operation_CheckFinish:
            return check_rival_finish( room, id, user_info_response );

        case System::Request_Operation_RivalMeta:
            return get_rival_meta( room, id, user_info_response );

        case System::Request_Operation_RivalName:
            return get_rival_name( room, id, user_info_response );

        case System::Request_Operation_QuitRoom:
            current_user.clear_room_id();
            return quit_room( room_id, id );

        case System::Request_Operation_QuitWaitRoom:
            current_user.clear_room_id();
            return quit_wait_rival( room_id );
    }

    std::cerr << "Invalid operation issue\n";
    return false;

}
void GamePrototype::kick_off( System::User& user ){
    int room_id = user.room_id();
    std::lock_guard<std::mutex> lock(mutex);
    if( room_exist( room_id ) )
        rooms_in_game[room_id]->set_died(user.id());
}
bool GamePrototype::get_rival_meta( GameRoom* room, int user_id, System::User* rival ){
    user_id = user_id == 1 ? 0 : 1; // rival id
    rival->set_dead( room->is_dead( user_id ) );
    if( room ) return room->get_player_meta( user_id, rival ); 
}

bool GamePrototype::get_rival_name( GameRoom* room, int user_id, System::User* rival ){
    user_id = user_id == 1 ? 0 : 1; // rival id
    if( room ) return room->get_player_name( user_id, rival ); 
}

bool GamePrototype::check_rival_finish( GameRoom* room, int user_id, System::User* rival ){
    if( room ){
        user_id = user_id == 1 ? 0 : 1; // rival id
        rival->set_dead( room->is_dead( user_id ) );
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
bool GamePrototype::quit_wait_rival( int room_id ){
    std::lock_guard<std::mutex> lock(mutex);

    if( rooms_in_wait.front().first == room_id ){
        delete rooms_in_wait.front().second;
        rooms_in_wait.pop();
    }
    else {
        std::queue< std::pair<int, GameRoom*> > tmp;
        int size = rooms_in_wait.size();
        while( rooms_in_wait.front().first != room_id ){
            tmp.push( rooms_in_wait.front() );
            rooms_in_wait.pop();
        }

        rooms_in_wait.pop();

        while( rooms_in_wait.size() ){
            tmp.push( rooms_in_wait.front() );
            rooms_in_wait.pop();
        }

        if( size != tmp.size() )
            std::swap( tmp, rooms_in_wait );
    }
}
bool GamePrototype::quit_room( int room_id, int id ){
    
    int rival_id = id == 1 ? 0 : 1; 

    std::lock_guard<std::mutex> lock(mutex);

    if( room_exist(room_id) ){
        // If rival is dead
        if( rooms_in_game[room_id]->is_dead(rival_id) ){
            delete rooms_in_game[ room_id ];
            rooms_in_game.erase( room_id );
        }
        // Otherwise, kill yourself and let rival delete the room later
        else{
            rooms_in_game[room_id]->set_died(id);
        }
    }

    return true;
}
int GamePrototype::generate_room_id(){
    std::srand(std::time(0)); // use current time as seed for random generator
    return std::rand();
}
bool GamePrototype::room_exist( int room_id ){
    return ( rooms_in_game.find( room_id ) != rooms_in_game.end() );
}
