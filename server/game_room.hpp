#ifndef GAMEROOM_H
#define GAMEROOM_H 

#include <string>
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

public:

    System::RoomMeta meta;

    GameRoom( int _playerNum ): playerNum(_playerNum) {
    }

    bool is_full();

    bool get_rival_meta( int user_id, System::User* rival );

    bool get_rival_name( int user_id, System::User* rival );

    void add_player( System::User& user );

    void initialize( System::RoomMeta&&  _meta );

    void set_player_meta( int id, System::Meta&& meta );

    System::Meta get_player_meta( int id );

};


#endif
