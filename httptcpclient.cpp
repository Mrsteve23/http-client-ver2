#include "httptcpclient.h"
#include <iostream>
#include <string>

string BeforeSplash(string url)
{
    size_t pos = url.find('/');
    return url.substr(0, pos);
}

string AfterSplash(string url)
{
    size_t pos = url.find('/');
    if(pos != string::npos){
        return url.substr(pos);
    }else{
        return "/";
    }
}

bool HttpTcpClientCLI::getHTTP (const string& url)
{
    if(!isConnected())
    {
        cout << "Loi: chua co connection." << endl;
        return false;
    }
    else
    {
        string httpRequest;
        // tao request theo format
        httpRequest = "GET " + AfterSplash(url) + " HTTP/1.1\r\n";
        httpRequest.append("User-Agent: Http-Client-2.0\r\n");
        httpRequest.append("Host: "+ BeforeSplash(url) + "\r\n");
        httpRequest.append("Connection: keep-alive\r\n");
        httpRequest.append("\r\n");
        cout << httpRequest << endl;
        int byte_sent = sendStringRequest(httpRequest);  // gui ban tin Echo request
        cout << byte_sent << endl;
        if(byte_sent > 0) // neu gui thanh cong request
        {
            // chuan bi nhan phan hoi tu HTTP Server
            string httpResponse;
            int byte_recv = 0; // tong so byte nhan lai
            int bytes; // so byte nhan trong 1 lan
            char buffer[256]; // bo dem buffer kich thuoc 128 byte
            // vong lap nhan phan hoi tu Echo Server
            do
            {
                bytes = recvStringBuffer(buffer,sizeof(buffer)); // nhan 1 xau ki tu vao buffer
                if(bytes>0) // nhan duoc du lieu neu bytes > 0, neu khong thi error
                {
                    byte_recv += bytes; // tang so byte nhan duoc
                    httpResponse += buffer; // ghep xau nhan duoc trong buffer vao ket qua response
                }
            }
            while(bytes > 0);
            cout << "byte recvice: " << byte_recv << endl;
            if(bytes==0)
            {
                cout <<"Server da dong ket noi" << endl;
                print(httpResponse);
            }
            else
            {
                cout << "Loi: nhan response" << endl;
            }
        }
        else
        {
            cout << "Loi: gui request" << endl;
        }
    }
    return true;
}

bool HttpTcpClientCLI::postHTTP (const string& url, const string& msv)
{
    if(!isConnected())
    {
        cout << "Loi: chua co connection." << endl;
        return false;
    }
    else
    {
        string httpRequest;
        string body = "{\"student_id\":\"" + msv + "\"}";
        int cLength= body.length();
        // tao request theo format
        httpRequest = "POST " + AfterSplash(url) + " HTTP/1.1\r\n";
        httpRequest.append("Content-Type: application/json\r\n");
        httpRequest.append("Host: "+ BeforeSplash(url) + "\r\n");
        httpRequest.append("Content-Length: " + to_string(cLength) +"\r\n");
        httpRequest.append("Connection: close\r\n");
        httpRequest.append("\r\n");
        httpRequest.append(body);
        cout << httpRequest << endl;
        int byte_sent = sendStringRequest(httpRequest);  // gui ban tin Echo request
        cout << byte_sent << endl;

        if(byte_sent > 0) // neu gui thanh cong request
        {
            // chuan bi nhan phan hoi tu HTTP Server
            string httpResponse;
            int byte_recv = 0; // tong so byte nhan lai
            int bytes; // so byte nhan trong 1 lan
            char buffer[256]; // bo dem buffer kich thuoc 128 byte

            // vong lap nhan phan hoi tu Echo Server
            do
            {
                bytes = recvStringBuffer(buffer,sizeof(buffer)); // nhan 1 xau ki tu vao buffer
                if(bytes>0) // nhan duoc du lieu neu bytes > 0, neu khong thi error
                {
                    byte_recv += bytes; // tang so byte nhan duoc
                    httpResponse += buffer; // ghep xau nhan duoc trong buffer vao ket qua response
                }
            }
            while(bytes>0);
            cout << "byte recvice: " << byte_recv << endl;
            if(bytes==0)
            {
                cout <<"Server da dong ket noi" << endl;
                print(httpResponse);
            }
            else
            {
                cout << "Loi: nhan response" << endl;
            }


        }
        else
        {
            cout << "Loi: gui request" << endl;
        }


    }
    return true;
}


//bool HttpTcpClientCLI::echo (const string& msg)
//{
//    if(!isConnected())
//    {
//        cout << "Loi: chua co connection." << endl;
//        return false;
//    }
//    else
//    {
//        // add code here
//        int byte_sent = sendStringRequest(msg);  // gui ban tin Echo request
//        if(byte_sent > 0) // neu gui thanh cong request
//        {
//            string response;
//            int byte_recv = 0; // tong so byte nhan lai
//            int bytes; // so byte nhan trong 1 lan
//            char buffer[128]; // bo dem buffer kich thuoc 128 byte
//
//            /* vong lap nhan phan hoi tu Echo Server */
//            do
//            {
//                bytes = recvStringBuffer(buffer,sizeof(buffer)); // nhan 1 xau ki tu vao buffer
//                if(bytes>0) // nhan duoc du lieu neu bytes > 0, neu khong thi error
//                {
//                    byte_recv += bytes; // tang so byte nhan duoc
//                    response += buffer; // ghep xau nhan duoc trong buffer vao ket qua response
//                }
//            }
//            while(bytes>0 && byte_recv < byte_sent);
//
//            if(byte_recv == byte_sent) // da nhan du? phan hoi tu Echo Server
//            {
//                cout << "Server: ";
//                print(response);  // in ket qua phan hoi cua Echo Server
//                return true;
//            }
//            else  // co loi xay ra (socket error)
//            {
//                cout << "Loi: nhan response." << endl;
//                return false;
//            }
//        }
//        else
//        {
//            cout << "Loi: gui request." << endl;
//            return false;
//        }
//    }
//}
//
