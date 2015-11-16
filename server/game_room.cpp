#include "game_room.hpp"

void GameRoom::initialize( System::RoomMeta&& _meta ){
    std::lock_guard<std::mutex> lock(mutex);
    meta = _meta;
}

bool GameRoom::is_full(){
    return player_list.player_size() >= playerNum;
}

void GameRoom::add_player( System::User& user ){
    std::lock_guard<std::mutex> lock(mutex);
    *(player_list.add_player()) = user;
}
bool GameRoom::is_dead( int user_id ){
    std::lock_guard<std::mutex> lock(mutex);
    return player_list.player(user_id).dead();
}
bool GameRoom::get_player_name( int user_id, System::User* rival ){
    std::lock_guard<std::mutex> lock(mutex);
    rival->set_name(player_list.player(user_id).name());
    return true;
}

bool GameRoom::get_player_meta( int user_id, System::User* rival ){
    std::lock_guard<std::mutex> lock(mutex);
    *(rival->mutable_meta()) = player_list.player(user_id).meta();
    return true;
}
void GameRoom::set_player_meta( int id, System::Meta&& meta ){
    std::lock_guard<std::mutex> lock(mutex);
    *(player_list.mutable_player(id)->mutable_meta()) = meta;
}

void GameRoom::update_player_meta( int id, std::function<void(System::Meta* meta)> update_function ){
    std::lock_guard<std::mutex> lock(mutex);
    update_function( player_list.mutable_player(id)->mutable_meta() );
}

void GameRoom::set_finished( int id ){
    std::lock_guard<std::mutex> lock(mutex);
    hasFinished[id] = true;
}

bool GameRoom::check_finish( int id ){
    std::lock_guard<std::mutex> lock(mutex);
    return hasFinished[id];
}

void GameRoom::set_died( int id ){
    std::lock_guard<std::mutex> lock(mutex);
    player_list.mutable_player(id)->set_dead(true);
}
