#ifndef GUESS_NUMBER_HEADER
#define GUESS_NUMBER_HEADER 

#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <array>
#include "game_prototype.hpp"
#include "main.model.pb.h"

class GuessNumServer: public GamePrototype {
    
    std::array<int,10> random_num_list;

public:
    GuessNumServer( int roomNum ,int playerNum );

    bool handle_req( System::User& user, const GuessNum::Request& req, GuessNum::Reply* res );

protected:

    virtual void initialize( int room_id );

private:

    void update_meta( GameRoom* room, int id );

    bool check_answer( const GuessNum::RoomMeta& meta, const GuessNum::Guesses& submission, GuessNum::Reply* res );
};

#endif
