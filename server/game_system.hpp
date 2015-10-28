#ifndef GAME_SYSTEM_HEADER
#define GAME_SYSTEM_HEADER 

#include <string>
#include <thread>
#include <mutex>
#include <cstring>
#include <iostream>
#include <vector>
#include "connection.hpp"
#include "model.pb.h"
#include "guess_num.hpp"

class GameSystem {

    const int initial_money;

    Connection connection;
    GuessNum* guess_num;

    std::mutex mutex;
    std::vector<Model::User*> user_list;
    /* Will return the smallest available index */
    std::priority_queue<int, std::vector<int>, std::greater<int> > available_index;
    

public:
    void start();
    void process(int req_socket);
    GameSystem(Connection&& conn, std::map<std::string,std::string>&& config);

private:
    void response_sucess( Model::System_Reply& res, Model::Reply& response );
    void handle_req(Model::Request&& req );
    bool addUser();
};

#endif
