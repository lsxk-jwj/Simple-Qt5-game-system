#ifndef GAMEROOM_H
#define GAMEROOM_H 

#include <string>
#include <functional>
#include <mutex>
#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include "main.model.pb.h"

class GameRoom {
    
    const int playerNum;


    std::mutex mutex;

    System::PlayerList player_list;

    bool hasFinished[2];

public:

    System::RoomMeta meta;

    GameRoom( int _playerNum ): playerNum(_playerNum) {
        hasFinished[0] = hasFinished[1] = false;
    }

    bool is_full();

    bool is_dead( int id );

    bool get_player_meta( int user_id, System::User* rival );

    bool get_player_name( int user_id, System::User* rival );

    bool check_finish( int id );

    void set_finished( int id );

    void add_player( System::User& user );

    void initialize( System::RoomMeta&&  _meta );

    void set_player_meta( int id, System::Meta&& meta );

    void set_died( int id );

    void update_player_meta( int id, std::function<void(System::Meta* meta)> update_function );

};


#endif
