#ifndef GAME_SYSTEM_HEADER
#define GAME_SYSTEM_HEADER 

#include <string>
#include <thread>
#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include "connection.hpp"
#include "main.model.pb.h"
#include "guess_num.hpp"

class GameSystem {

    const int initial_money;

    Connection connection;
    GuessNumServer* guess_num;

public:
    void start();
    void process(int req_socket);
    GameSystem(Connection&& conn, std::map<std::string,std::string>&& config);

private:
    void set_response( System::User& user, Model::Reply& response );
    void response_sucess( System::Reply& res, Model::Reply& response );
    bool handle_req( System::User& user, const System::Request& req, Model::Reply& response );
    bool join_game( System::User& user, System::Request_Type game_type, Model::Reply& response );
    bool add_user( Model::Reply& response );
    int generate_new_id();
};

#endif
