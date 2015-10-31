#include "game_room.hpp"

bool GameRoom::is_full(){
    return player_list.size() >= playerNum;
}

bool GameRoom::add_user( System::User& user ){
    player_list.push_back( user );
}
