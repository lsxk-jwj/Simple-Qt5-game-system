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

bool GameRoom::get_rival_name( int user_id, System::User* rival ){
    std::lock_guard<std::mutex> lock(mutex);
    if( is_full() ){
        rival->set_name( player_list.player(0).id() == user_id ?
            player_list.player(1).name() :
            player_list.player(0).name()
        );
        return true;
    }

    return false;
}

bool GameRoom::get_rival_meta( int user_id, System::User* rival ){
    std::lock_guard<std::mutex> lock(mutex);
    if( is_full() ){
        *(rival->mutable_meta()) = player_list.player(0).id() == user_id ?
            player_list.player(1).meta() :
            player_list.player(0).meta();
        return true;
    }

    return false;
}
void GameRoom::set_player_meta( int id, System::Meta&& meta ){
    std::lock_guard<std::mutex> lock(mutex);
    *(player_list.mutable_player(id)->mutable_meta()) = meta;
}

const System::Meta& GameRoom::get_player_meta( int id ){
    std::lock_guard<std::mutex> lock(mutex);
    return player_list.player(id).meta();
}

void GameRoom::update_player_meta( int id, std::function<void(System::Meta* meta)> update_function ){
    std::lock_guard<std::mutex> lock(mutex);
    update_function( player_list.mutable_player(id)->mutable_meta() );
}

void GameRoom::set_finished( int id ){
    hasFinished[id] = true;
}

bool GameRoom::check_finish( int id ){
    return hasFinished[id];
}
