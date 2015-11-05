#include "game_structure.hpp"

bool GameStructure::has_no_room(){
    return rooms_in_game.size() + rooms_in_wait.size() >= roomNum;
}

bool GameStructure::add_player( System::User& user ){
    GameRoom* new_room;
    int room_id;

    std::lock_guard<std::mutex> lock(mutex);

    if( rooms_in_wait.empty() ){
        new_room = new GameRoom( playerNum );
        new_room->add_player( user );
        room_id = generate_room_id();
        rooms_in_wait.push( std::make_pair( room_id, new_room ) );
    }
    else{
        new_room = rooms_in_wait.front().second;
        new_room->add_player( user );
        if( new_room->is_full() ){
            rooms_in_game.insert( rooms_in_wait.front() );
            rooms_in_wait.pop();
        }
    }

    user.set_room_id( room_id );
}

bool GameStructure::get_players( int room_id, System::PlayerList& players ){

    if( rooms_in_game.find( room_id ) != rooms_in_game.end() ){
        players = rooms_in_game[room_id]->get_player_list(); 
        return true;
    }

    return false;
}

bool GameStructure::check_game_ready( int room_id ){
    return rooms_in_game.find( room_id ) != rooms_in_game.end();
}

int GameStructure::generate_room_id(){
    std::srand(std::time(0)); // use current time as seed for random generator
    return std::rand();
}
