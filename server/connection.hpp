#ifndef CONNECTION_HEADER
#define CONNECTION_HEADER 

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <string>
#include <thread>
#include <cstring>
#include <iostream>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

struct Connection {
    
    static const int buffer_size = 1000;
    int socket;
    char* buffer;

public:

    Connection(int port);
    int accept() const;

    static bool send_message(int socket, const google::protobuf::MessageLite& message);
    static bool receive_message(int socket, google::protobuf::MessageLite& message);
    static bool send_error( std::string&& error_mesg );
};

#endif
