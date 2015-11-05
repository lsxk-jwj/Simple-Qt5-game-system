#include "game_room.hpp"

bool GameRoom::is_full(){
    return player_list.player_size() >= playerNum;
}

bool GameRoom::add_player( System::User& user ){
    *(player_list.add_player()) = user;
}

const System::PlayerList& GameRoom::get_player_list(){
    std::lock_guard<std::mutex> lock(mutex);
    return player_list;
}
