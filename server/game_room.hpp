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

    GameRoom( int _playerNum ): playerNum(_playerNum) {
    }

    bool is_full();

    bool add_player( System::User& user );

    const System::PlayerList& get_player_list();
};


#endif
