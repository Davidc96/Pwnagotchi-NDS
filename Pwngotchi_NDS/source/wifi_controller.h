#ifndef H_WIFICONTROLLER_H
#define H_WIFICONTROLLER_H
#include <nds.h>
#include <dswifi9.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

class WifiController
{
    public:
        WifiController();
        ~WifiController();
        int connectAP();
        void sendCommand(char * command, char * response);
};

#endif