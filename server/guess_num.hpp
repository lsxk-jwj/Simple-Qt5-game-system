#ifndef GUESS_NUMBER_HEADER
#define GUESS_NUMBER_HEADER 

#include "model.pb.h"

class GuessNum {

    int playerNum;
    int roomNum;

public:
    GuessNum( int _roomNum ,int _playerNum ):roomNum(_roomNum), playerNum(_playerNum){
        if( playerNum <= 0 || roomNum <= 0 ){
            std::cerr << "Impossible room number: " << roomNum << " or impossible player number: " << playerNum << std::endl;
            exit(0);
        }
    }

    void handle_req( Model::Request&& req );

    void available();

};

#endif
