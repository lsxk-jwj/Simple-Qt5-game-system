#ifndef SYSTEMREQUEST_H
#define SYSTEMREQUEST_H

#include "request.h"

class SystemRequest : public Request
{
public:
    SystemRequest();
    void system( System::Request::Operation op, CallBack callback );
    void newUser( std::string& name, CallBack callback );
    void joinGame( System::Type type, CallBack callback );
};

#endif // SYSTEMREQUEST_H
