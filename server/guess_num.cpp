#include "guess_num.hpp"

GuessNumServer::GuessNumServer( int roomNum ,int playerNum ):GameStructure(roomNum, playerNum){
    for( int i = 0 ; i < 10; ++i ){
        random_num_list[i] = i;
    }
}

bool GuessNumServer::handle_req( System::User& user, const GuessNum::Request& req, GuessNum::Reply* res ){

    mutex.lock();

    auto meta = rooms_in_game[ user.room_id() ]->meta.guess_num();

    mutex.unlock();

    int user_id = user.id();

    switch( req.command() ){
        case GuessNum::SUBMIT:
            update_meta( rooms_in_game[ user.room_id() ], user.id() );
            if( check_answer( meta, req.submission(), res ) ){ // If the player has all numbers correct
            }
            break;

    }
}

void GuessNumServer::update_meta( GameRoom* room, int id ){
    System::Meta updated_meta;
    auto player_meta = room->get_player_meta( id ).guess_num();
    updated_meta.mutable_guess_num()->set_round( player_meta.round() + 1 );
    room->set_player_meta( id, std::move(updated_meta) );
}

bool GuessNumServer::check_answer( const GuessNum::RoomMeta& meta, const GuessNum::Guesses& submission, GuessNum::Reply* res ){

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
    for( int i = 0; i < 4 ; ++i ){
        meta->add_answers( random_num_list[i] );
    }

    System::RoomMeta room_meta;
    room_meta.set_allocated_guess_num(meta);

    std::lock_guard<std::mutex> lock(mutex);
    rooms_in_game[ room_id ]->initialize( std::move(room_meta) );
}

