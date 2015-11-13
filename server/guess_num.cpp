#include "guess_num.hpp"

GuessNumServer::GuessNumServer( int roomNum ,int playerNum ):GamePrototype(roomNum, playerNum){
    for( int i = 0 ; i < 10; ++i ){
        random_num_list[i] = i;
    }
}

bool GuessNumServer::handle_req( System::User& user, const GuessNum::Request& req, GuessNum::Reply* res ){

    mutex.lock();

    GameRoom* room;
    if( rooms_in_game.find( user.room_id() ) != rooms_in_game.end() ){
        room = rooms_in_game[ user.room_id() ];
        mutex.unlock();
    }
    else{
        mutex.unlock();
        return false;
    }


    int user_id = user.id();

    switch( req.command() ){
        case GuessNum::SUBMIT:
            update_meta( room, user.id() );
            if( check_answer( room->meta.guess_num(), req.submission(), res ) ){ // If the player has all numbers correct
                room->set_finished( user.id() );
            }
            break;

    }
}

void GuessNumServer::update_meta( GameRoom* room, int id ){
    // Increment round number by 1
    room->update_player_meta( id, []( System::Meta* meta ){
        int r = meta->guess_num().round();
        meta->mutable_guess_num()->set_round( r + 1 );
    } );
}

bool GuessNumServer::check_answer( const GuessNum::RoomMeta& meta, const GuessNum::Guesses& submission, GuessNum::Reply* res ){
    
    std::cerr << "Checking submission\n";
    std::cerr << "answers: ";
    
    for( int i = 0; i < 4; ++i ){
        std::cerr << meta.answers(i) << " ";
    }
    std::cerr << std::endl;
    std::cerr << "guesses: ";
    for( int i = 0; i < 4; ++i ){
        std::cerr << submission.guesses(i) << " ";
    }
    std::cerr << std::endl;

    int A = 0, B = 0;
    for( int i = 0; i < 4; ++i ){
        for( int j = 0; j < 4; ++j ){
            if( meta.answers(i) == submission.guesses(j) ){
                if( i == j )
                    ++A;
                else
                    ++B;
            }
        }
    }

    res->set_result_a(A);
    res->set_result_b(B);

    if( A == 4 )
        return true;
    else
        return false;
}

void GuessNumServer::initialize( int room_id ){
    /* Randomly generate four unique number */
    std::srand( (unsigned) std::time(0));
    std::random_shuffle ( random_num_list.begin(), random_num_list.end() );
    
    auto meta = new GuessNum::RoomMeta();

    std::cerr << "Room " << room_id << " guess num initialized:\n";

    for( int i = 0; i < 4 ; ++i ){
        std::cerr << random_num_list[i] << " ";
        meta->add_answers( random_num_list[i] );
    }

    std::cerr << std::endl;

    System::RoomMeta room_meta;
    room_meta.set_allocated_guess_num(meta);

    rooms_in_game[ room_id ]->initialize( std::move(room_meta) );

}

