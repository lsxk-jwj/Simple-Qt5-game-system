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
    
    static const int socket_time_out = 7000;
    static const int buffer_size = 1000;
    int socket;

public:

    Connection();
    int accept() const;
    void useAsServer(int port);
    int useAsClient(int port, const char* ip = nullptr);
    void initializeSocket();

    static bool send_message(int socket, const google::protobuf::MessageLite& message);
    static bool receive_message(int socket, google::protobuf::MessageLite& message);
    static void set_timeout( int req_socket );

};

#endif 
