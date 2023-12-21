#ifndef HTTPTCPCLIENT_H_INCLUDED
#define HTTPTCPCLIENT_H_INCLUDED

#include "tcpclient.h"

class HttpTcpClientCLI: public TcpClient
{
private:

public:
    bool postHTTP(const string& url, const string& msv);
    bool putHTTP (const string& url, const string& msv, const string& path);
    string HttpResponse(int byte_sent);
};


#endif // HTTPTCPCLIENT_H_INCLUDED

