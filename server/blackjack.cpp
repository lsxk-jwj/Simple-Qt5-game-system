
#include "blackjack.hpp"

BlackJackServer::BlackJackServer( int roomNum ,int playerNum ):GamePrototype(roomNum, playerNum){
#if defined ( DEBUG_SAME )
    for( int i = 0 ; i < 52; ++i ){
        cards[i] = 9;
    }
#elif defined ( DEBUG_CARD )
    int a[] = {10,11,12,13,24,25,26};
    int len = sizeof(a)/sizeof(int);
    int t = 0;
    for( int i = 0 ; i < 52; ++i ){
        cards[i] = a[t];
        t = (t+1)%len;
    }
#else
    for( int i = 0 ; i < 52; ++i ){
        cards[i] = i+1;
    }
#endif
}

bool BlackJackServer::handle_req( System::User& user, const BlackJack::Request& req, BlackJack::Reply* res ){
    
    GameRoom* room;

    mutex.lock();
    if( room_exist(user.room_id()) ){
        room = rooms_in_game[ user.room_id() ];
        mutex.unlock();
    }
    else{
        mutex.unlock();
        return false;
    }

    int user_id = user.id();

    switch( req.command() ){
        case BlackJack::UPDATE:
            return command_update( room, user_id, res );
        case BlackJack::HIT:
            return command_hit( req.flag(), room, user_id, res );
        case BlackJack::DEAL:
            return command_deal( room, user_id, res );
        case BlackJack::SPLIT:
            return command_split( room, user_id, res );
        case BlackJack::FINISH:
            return command_set_finish( req.flag(), room, user_id, res );
        case BlackJack::GET_DEALER_DECK:
            return command_get_dealer_deck( room, user_id, res );
        case BlackJack::GET_RIVAL_DECK:
            return command_get_rival_deck( room, user_id, res );
            break;
    }
    return false;
}

bool BlackJackServer::command_update( GameRoom* room, int id, BlackJack::Reply* res ){
    id = ( id == 0 ) ? 1 : 0; // Rival id
    res->set_dead( room->is_dead( id ) );
    room->update_player_meta( id, [=]( System::Meta* meta ){
        res->set_count( meta->blackjack().cards1_size() );
    });
    return true;
}
bool BlackJackServer::command_deal( GameRoom* room, int id, BlackJack::Reply* res ){
    
    int c1 = deal(), c2 = deal();
    int v1 = value(c1), v2 = value(c2);

    room->update_player_meta( id, [=]( System::Meta* meta ){
        meta->mutable_blackjack()->add_cards1(c1);
        meta->mutable_blackjack()->add_cards1(c2);

        res->set_card1(c1);
        res->set_card2(c2);

    } );

    if( isAce(c1) ^ isAce(c2) ) // c1 is Ace or c2 is Ace, but not both 
        if( v1 == 10 || v2 == 10 ){ 
            // BlackJack!!
            room->set_finished( id );
            return true;
        }
    return false;
}

bool BlackJackServer::command_hit( bool acted_on_deck2, GameRoom* room, int id, BlackJack::Reply* res ){

    int c = deal();

    room->update_player_meta( id, [=]( System::Meta* meta ){
        if( acted_on_deck2 )
            meta->mutable_blackjack()->add_cards2(c);
        else
            meta->mutable_blackjack()->add_cards1(c);

        res->set_card1(c);

    } );
    
    return false;
}

bool BlackJackServer::command_split( GameRoom* room, int id, BlackJack::Reply* res ){

    room->update_player_meta( id, [=]( System::Meta* meta ){

        int card2 = meta->blackjack().cards1(1);
        meta->mutable_blackjack()->mutable_cards1()->RemoveLast(); // Remove card 2
        meta->mutable_blackjack()->add_cards2(card2);

    } );

    return true;
}

bool BlackJackServer::command_get_dealer_deck( GameRoom* room, int id, BlackJack::Reply* res ){
    const BlackJack::RoomMeta& dealer = room->meta.blackjack();
    *(res->mutable_cards()) = dealer.cards();
    return true;
}

bool BlackJackServer::command_set_finish( bool cards2_the_best, GameRoom* room, int id, BlackJack::Reply* res ){
    
    if( cards2_the_best )
        std::cerr << "Setting cards 2 as best\n";
    else
        std::cerr << "Setting cards 1 as best\n";

    room->set_finished(id);
    room->update_player_meta( id, [=]( System::Meta* meta ){
        meta->mutable_blackjack()->set_cards2_the_best( cards2_the_best );
    });
    return true;
}

bool BlackJackServer::command_get_rival_deck( GameRoom* room, int id, BlackJack::Reply* res ){
    id = ( id == 0 ) ? 1 : 0; // Rival id
    room->update_player_meta( id, [=]( System::Meta* meta ){
        if( meta->blackjack().cards2_the_best() )
            *(res->mutable_cards()) = meta->blackjack().cards2();
        else
            *(res->mutable_cards()) = meta->blackjack().cards1();
    });
    return true;
}
void BlackJackServer::initialize( int room_id ){
    /* Randomly shuffle the cards */
    std::srand( (unsigned) std::time(0));
    std::random_shuffle ( cards.begin(), cards.end() );

    /* The counter will be incremented when a new card is withdrawn from deck */
    deck_counter = 0;
    
    /* Initialize Dealer's cards */
    auto meta = new BlackJack::RoomMeta();

    std::cerr << "Room " << room_id << " blackjack initialized:\n";

    int card, card_value, aceCount = 0, sum = 0;
    while( sum < 17 && sum + 10*aceCount < 17 ){ // Dealer should stop when he got more than 17

        card = deal(); card_value = value( card );
        if( sum + card_value > 21 ){
            meta->add_cards( card ); // Bursted
            break;
        }

        if( isAce( card ) )
            ++aceCount;

        sum += card_value;
        meta->add_cards( card );

        std::cerr << card_value << " ";
    }

    std::cerr << std::endl;

    System::RoomMeta room_meta;
    room_meta.set_allocated_blackjack(meta);

    rooms_in_game[ room_id ]->initialize( std::move(room_meta) );

}

int BlackJackServer::value( int card ){
    int mod = card % 13;
    if( mod == 0 || mod > 10 ) /* J, Q, K */
        return 10;
    return mod;
}

bool BlackJackServer::isAce( int card ){
    return card % 13 == 1;    
}

int BlackJackServer::deal(){
    return cards[deck_counter++];    
}
