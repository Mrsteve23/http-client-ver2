
#ifndef HTTPCLI_H_INCLUDED
#define HTTPCLI_H_INCLUDED

#include "cli.h"
#include "tcpsocket.h"
#include "httptcpclient.h"

class HttpClientCLI : public CmdLineInterface {
private:
    HttpTcpClientCLI client;
public:
    HttpClientCLI();
    ~HttpClientCLI();
    void initCmd();
private:
   //add code here

   void doOpen(string cmd_argv[], int cmd_argc);
   void doClose(string cmd_argv[], int cmd_argc);
   void doHelp(string cmd_argv[], int cmd_argc);
   void doPost(string cmd_argv[], int cmd_argc);
   void doPut(string cmd_argv[], int cmd_argc);
};


#endif // HTTPCLI_H_INCLUDED
