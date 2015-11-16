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

class GamePrototype {
    
    const int playerNum;
    const int roomNum;

protected:

    std::mutex mutex;
    std::map<int, GameRoom*> rooms_in_game;
    std::queue< std::pair<int, GameRoom*> > rooms_in_wait;

public:

    GamePrototype(int _roomNum, int _playerNum): roomNum(_roomNum), playerNum(_playerNum){
        if( playerNum <= 0 || roomNum <= 0 ){
            std::cerr << "Impossible room number: " << roomNum << " or impossible player number: " << playerNum << std::endl;
            exit(0);
        }
    }

    bool do_operation( System::Request::Operation op, System::User& current_user, System::User* response_user );
    void kick_off( System::User& user );

private:

    int generate_room_id();
    bool get_rival_name( GameRoom* room, int user_id, System::User* rival );
    bool get_rival_meta( GameRoom* room, int user_id, System::User* rival );
    bool check_rival_finish( GameRoom* room, int user_id, System::User* rival );
    bool check_game_ready( GameRoom* room );
    bool add_player( System::User& current_user );
    bool quit_room( int room_id, int id );
    bool quit_wait_rival( int room_id );

protected:
    bool room_exist( int room_id );
    virtual void initialize( int room_id ) = 0;

};

#endif
