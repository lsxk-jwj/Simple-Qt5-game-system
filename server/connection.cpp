#include "connection.hpp"
#include "guess_num.hpp"

Connection::Connection(int port){

    this->socket = ::socket(AF_INET, SOCK_STREAM, 0);

    int val = 1;
    if( ::setsockopt( this->socket, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val) ) < 0 ){
        std::cerr << "Fail setting socket\n";
    }

    sockaddr_in a;
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    a.sin_addr.s_addr = INADDR_ANY;
    a.sin_port = htons(port);
    if( ::bind(this->socket, (sockaddr*)&a, sizeof(sockaddr)) < 0 ){
        std::cerr << "Fail binding socket\n";
    }

    if( ::listen( this->socket, 10 ) < 0 ){
        std::cerr << "Fail binding socket\n";
    }
    else {
        std::cout << "Game server starts listening at port " << port << std::endl;
    }

}

int Connection::accept() const{

    static struct sockaddr_in client;
    static int client_socket_size = sizeof(struct sockaddr_in);
    return ::accept( this->socket, (struct sockaddr *)&client, (socklen_t*)&client_socket_size);

}

bool Connection::send_message(int socket, const google::protobuf::MessageLite& message)
{
    google::protobuf::uint32 message_length = message.ByteSize();
    int prefix_length = sizeof(message_length);
    int buffer_length = prefix_length + message_length;

    // Prepare buffer
    google::protobuf::uint8 buffer[buffer_length];

    google::protobuf::io::ArrayOutputStream array_output(buffer, buffer_length);
    google::protobuf::io::CodedOutputStream coded_output(&array_output);

    coded_output.WriteLittleEndian32(message_length);
    message.SerializeToCodedStream(&coded_output);

    int sent_bytes = 0;
    for (int i=0; i < buffer_length; i += sent_bytes) {      
        sent_bytes = write(socket, buffer + i, buffer_length - i);
        if (sent_bytes < 0) /* write error */
            return false;
    }

    return true;
}

bool Connection::receive_message(int socket, google::protobuf::MessageLite& message)
{
    google::protobuf::uint32 message_length;
    int prefix_length = sizeof(message_length);
    google::protobuf::uint8 prefix[prefix_length];

    // Receive the length information
    if (prefix_length != ::recv(socket, prefix, prefix_length, MSG_WAITALL )) {
        return false;
    }

    google::protobuf::io::CodedInputStream::ReadLittleEndian32FromArray(prefix, &message_length);

    // Prepare the buffer for the specified length of incoming message
    google::protobuf::uint8 buffer[message_length];

    // Read the message, read will return only when full length of data is read
    if (message_length != recv(socket, buffer, message_length, MSG_WAITALL )) {
        return false;
    }

    buffer[message_length] = '\0'; 

    return buffer;

    google::protobuf::io::ArrayInputStream array_input(buffer, message_length);
    google::protobuf::io::CodedInputStream coded_input(&array_input);

    if (!message.ParseFromCodedStream(&coded_input)) {
        return false;
    }

    return true;
}

bool Connection::send_error( std::string&& error_mesg ){
   /* TODO */ 
}

void Connection::set_timeout( int req_socket ){

    struct timeval timeout;      
    timeout.tv_sec = socket_time_out;
    timeout.tv_usec = 0;

    if (::setsockopt (req_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0 ||
        ::setsockopt (req_socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
        std::cerr < "(setsockopt): Fail setting timeout\n"; 
}

