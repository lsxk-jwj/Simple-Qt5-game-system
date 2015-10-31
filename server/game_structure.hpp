#ifndef GAMESTRUCTURE_H
#define GAMESTRUCTURE_H 

#include <mutex>
#include <string>
#include <thread>
#include <iostream>
#include <cstring>
#include <map>
#include <queue>
#include <ctime>
#include <cstdlib>
#include "main.model.pb.h"
#include "game_room.hpp"

class GameStructure {
    
    const int playerNum;
    const int roomNum;

    std::mutex mutex;
    std::map<int, GameRoom*> rooms_in_game;
    std::queue< std::pair<int, GameRoom*> > rooms_in_wait;

public:
    GameStructure(int _roomNum, int _playerNum): roomNum(_roomNum), playerNum(_playerNum){
        if( playerNum <= 0 || roomNum <= 0 ){
            std::cerr << "Impossible room number: " << roomNum << " or impossible player number: " << playerNum << std::endl;
            exit(0);
        }
    }

    bool add_user( System::User& user, Model::Reply& response );

    bool has_no_room();
private:
    int generate_room_id();

};

#endif
