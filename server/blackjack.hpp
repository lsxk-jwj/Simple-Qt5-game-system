#ifndef BLACKJACK_HEADER
#define BLACKJACK_HEADER 

#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <array>
#include "game_prototype.hpp"
#include "main.model.pb.h"

class BlackJackServer: public GamePrototype {
    
    std::array<int,52> cards;
    int deck_counter;

public:

    BlackJackServer( int roomNum ,int playerNum );

    bool handle_req( System::User& user, const BlackJack::Request& req, BlackJack::Reply* res );

protected:

    virtual void initialize( int room_id );

private:

    bool command_update( GameRoom* room, int id, BlackJack::Reply* res );

    bool command_hit( bool acted_on_deck2, GameRoom* room, int id, BlackJack::Reply* res );

    bool command_deal( GameRoom* room, int id, BlackJack::Reply* res );

    bool command_split( GameRoom* room, int id, BlackJack::Reply* res );

    bool command_set_finish( bool deck2_the_best, GameRoom* room, int id, BlackJack::Reply* res );

    bool command_get_dealer_deck( GameRoom* room, int id, BlackJack::Reply* res );

    bool command_get_rival_deck( GameRoom* room, int id, BlackJack::Reply* res );
   

    int deal();

    static bool isAce( int card );

    static int value( int card );
};

#endif
