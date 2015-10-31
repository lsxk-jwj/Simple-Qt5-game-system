#include "game_structure.hpp"

bool GameStructure::has_no_room(){
    return rooms_in_game.size() + rooms_in_wait.size() >= roomNum;
}

bool GameStructure::add_user( System::User& user, Model::Reply& response ){
    GameRoom* new_room;
    int room_id;

    std::lock_guard<std::mutex> lock(mutex);

    if( rooms_in_wait.empty() ){
        new_room = new GameRoom( playerNum );
        new_room->add_user( user );
        room_id = generate_room_id();
        rooms_in_wait.push( std::make_pair( room_id, new_room ) );
        user.set_room_owner(true); /* The first user in a room is the room owner.  He can decide when to start a game */
    }
    else{
        new_room = rooms_in_wait.front().second;
        new_room->add_user( user );
        user.set_room_owner(false);
        if( new_room->is_full() ){
            rooms_in_game.insert( rooms_in_wait.front() );
            rooms_in_wait.pop();
        }
    }

    user.set_room_id( room_id );
}

int GameStructure::generate_room_id(){
    std::srand(std::time(0)); // use current time as seed for random generator
    return std::rand();
}
