#ifndef GUESS_NUMBER_HEADER
#define GUESS_NUMBER_HEADER 

#include <iostream>
#include "game_structure.hpp"
#include "main.model.pb.h"

class GuessNumServer: public GameStructure {

public:
    GuessNumServer( int roomNum ,int playerNum ):GameStructure(roomNum, playerNum){}

    bool handle_req( System::User& user, const GuessNum::Request& req, Model::Reply& res );

};

#endif
