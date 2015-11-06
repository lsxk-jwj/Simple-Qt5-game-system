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

#define TIMEOUT_LIMIT 3

void start_game();
void initialize_game(Connection&& conn);

static void process(int req_socket);
static void initialize_user( System::User& user );

#endif
