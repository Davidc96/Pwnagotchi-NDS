#include "wifi_controller.h"

WifiController::WifiController() {}

WifiController::~WifiController() {}

int WifiController::connectAP()
{
    if(!Wifi_InitDefault(WFC_CONNECT)) 
    {
        return -1;    
    }

    return 1;
}

void WifiController::sendCommand(char * command, char * response)
{
    char request[255];
    memset(request, '\0', sizeof(request));

    sprintf(request, "GET /%s HTTP/1.1\r\nHost: david.com\r\nUser-Agent: Nintendo DS\r\n\r\n", command);
     
    // Create a TCP socket
    int my_socket;
    my_socket = socket( AF_INET, SOCK_STREAM, 0 );

    // Tell the socket to connect to the IP address we found, on port 80 (HTTP)
    struct sockaddr_in sain;
    sain.sin_family = AF_INET;
    sain.sin_port = htons(80);
    sain.sin_addr.s_addr= inet_addr("192.168.5.1");
    
    connect( my_socket,(struct sockaddr *)&sain, sizeof(sain) );

    // send our request
    send( my_socket, request, strlen(request), 0 );

    // get response
    int recvd_len;
    while( ( recvd_len = recv( my_socket, response, 255, 0 ) ) != 0 ) 
    { 
        // if recv returns 0, the socket has been closed.
        if(recvd_len>0) 
        { 
            // data was received!
            response[recvd_len] = 0; // null-terminate
		}
	}

	shutdown(my_socket,0); // good practice to shutdown the socket.
	closesocket(my_socket); // remove the socket.
}