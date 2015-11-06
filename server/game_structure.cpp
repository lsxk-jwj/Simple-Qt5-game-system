#include "game_structure.hpp"

bool GameStructure::do_operation( System::Request::Operation op, System::User& current_user, System::User* user_info_response ){

    int room_id = current_user.room_id(), id = current_user.id();
    switch( op ){

        case System::Request_Operation_RivalMeta:
            return get_rival_meta( room_id, id, user_info_response );

        case System::Request_Operation_RivalName:
            return get_rival_name( room_id, id, user_info_response );

        case System::Request_Operation_CheckReady:
            return check_game_ready( room_id );

        case System::Request_Operation_JoinGame:
            return add_player( current_user );

        case System::Request_Operation_QuitRoom:
            return quit_game( current_user );

        default:
            std::cerr << "Invalid operation issue\n";
    }

}

bool GameStructure::get_rival_meta( int room_id, int user_id, System::User* rival ){
    std::lock_guard<std::mutex> lock(mutex);
    if( rooms_in_game.find( room_id ) != rooms_in_game.end() )
        return rooms_in_game[room_id]->get_rival_meta( user_id, rival ); 

    return false;
}

bool GameStructure::get_rival_name( int room_id, int user_id, System::User* rival ){
    std::lock_guard<std::mutex> lock(mutex);
    if( rooms_in_game.find( room_id ) != rooms_in_game.end() )
        return rooms_in_game[room_id]->get_rival_name( user_id, rival ); 

    return false;
}

bool GameStructure::check_game_ready( int room_id ){
    std::lock_guard<std::mutex> lock(mutex);
    bool ans = rooms_in_game.find( room_id ) != rooms_in_game.end();
    if( ans ) std::cerr << "Checking if room of id: " << room_id << " has started: Ans: Yes\n";
    else  std::cerr << "Checking if room of id: " << room_id << " has started: Ans: No\n";
    return ans;
}

bool GameStructure::add_player( System::User& current_user ){
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
bool GameStructure::quit_game( System::User& user ){

}
int GameStructure::generate_room_id(){
    std::srand(std::time(0)); // use current time as seed for random generator
    return std::rand();
}
