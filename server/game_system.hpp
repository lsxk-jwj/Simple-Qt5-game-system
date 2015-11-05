#ifndef GAME_SYSTEM_HEADER
#define GAME_SYSTEM_HEADER 

#include <string>
#include <thread>
#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include "connection.hpp"
#include "config.hpp"
#include "guess_num.hpp"
#include "main.model.pb.h"

#define BUSY_TIMEOUT_LIMIT 2
#define IDE_TIMEOUT_LIMIT 10

void start_game();
void initialize_game(Connection&& conn);

static void process(int req_socket);
static void set_response( System::User& user, Model::Reply& response );
static void response_sucess( System::Reply& res, Model::Reply& response );
static bool handle_req( System::User& user, const System::Request& req, Model::Reply& response );
static bool join_game( System::User& user, System::Type game_type, Model::Reply& response );
static bool add_user( Model::Reply& response );
static bool check_ready( System::User& user, System::Type game_type );
static bool update_player_list( int room_id, System::Type game_type );
static int generate_new_id();

#endif
