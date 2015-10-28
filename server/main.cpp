#include <iostream>
#include <fstream>
#include <cstdio>
#include <map>
#include "connection.hpp"
#include "game_system.hpp"

void parse_config_file( std::map<std::string,std::string>& config, char* filename ){
    
    std::ifstream config_file(filename);
    std::string line;
    char key[30],value[30];

    if( config_file.is_open() ){
        while( std::getline( config_file, line ) ){
            if( sscanf( line.c_str(), "%s = %s", key, value ) < 2 ){
                std::cout << "Config file wrong format!  Should be `[key] = [value]`" << std::endl;
                exit(0);
            }
            if( key && value )
                config[ key ] = std::string(value);
        }
    }
    else {
        std::cout << "Fail opening " + std::string( filename ) << std::endl;
        exit(0);
    }

}
int main(int argc, char *argv[])
{
    if( argc < 2 ){
        std::cout << "Usage: " << argv[0] << " [configuartion file] " << std::endl; 
        exit(1);
    }

    std::map<std::string,std::string> config;

    parse_config_file( config, argv[1] );

    Connection connection( std::stoi(config["CONFIG::server_port"]) );

    GameSystem game_system( std::move(connection), std::move(config));

    game_system.start();

    return 0;
}
