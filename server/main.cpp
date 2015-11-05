#include <iostream>
#include <fstream>
#include <cstdio>
#include <map>
#include "config.hpp"
#include "connection.hpp"
#include "game_system.hpp"

void parse_config_file( std::map<std::string,std::string>& config, char* filename ){
    
    std::ifstream config_file(filename);
    std::string line;
    char key[30];
    int value;

    if( config_file.is_open() ){
        while( std::getline( config_file, line ) ){
            if( sscanf( line.c_str(), "%s = %d", key, &value ) < 2 ){
                std::cout << "Config file wrong format!  Should be `[key] = [value]`" << std::endl;
                exit(0);
            }
            else{
                std::cout << "Config: " << key << " = " << value << std::endl;
                if( key && value )
                    config[ key ] = value;
            }

        }
    }
    else {
        std::cout << "Fail opening " + std::string( filename ) << std::endl;
        exit(0);
    }

}
int main(int argc, char *argv[])
{

    // if( argc < 2 ){
        // std::cout << "Usage: " << argv[0] << " [configuartion file] " << std::endl; 
        // exit(1);
    // }

    // std::map<std::string,int> config;

    // parse_config_file( config, argv[1] );

    Connection connection;

    connection.useAsServer(CONFIG::SERVER_PORT);

    initialize_game( std::move(connection) );

    start_game();

    return 0;
}
