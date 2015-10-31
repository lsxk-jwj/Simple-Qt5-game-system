#ifndef GAMEROOM_H
#define GAMEROOM_H 

#include <string>
#include <mutex>
#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include "connection.hpp"
#include "main.model.pb.h"

class GameRoom {
    
    const int playerNum;
    std::mutex mutex;
    std::vector<System::User> player_list;

public:

    GameRoom( int _playerNum ): playerNum(_playerNum) {
    }

    bool is_full();

    bool add_user( System::User& user );

};


#endif
