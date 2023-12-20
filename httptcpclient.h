#ifndef HTTPTCPCLIENT_H_INCLUDED
#define HTTPTCPCLIENT_H_INCLUDED

#include "tcpclient.h"

class HttpTcpClientCLI: public TcpClient
{
private:

public:
    //bool echo(const string& msg);
    bool getHTTP(const string& url);
    bool postHTTP(const string& url, const string& msv);
    string HttpResponse(int byte_sent);
};


#endif // HTTPTCPCLIENT_H_INCLUDED

