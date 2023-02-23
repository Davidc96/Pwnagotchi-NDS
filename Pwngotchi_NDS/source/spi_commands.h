#ifndef SPI_COMMANDS_H
#define SPI_COMMANDS_H

// Sending Commands
#define SPI_PING 0x10 // To know if the ESP is conencted
#define SPI_GETAPCOUNT 0x11 // Get APs number
#define SPI_GIVEMEAP 0x12 // Give new AP (Response: AP_NAME - Number of clients)
#define SPI_SELECTAP 0x14 // Select AP
#define SPI_ATTACK 0x15 // Deauth one client

// Responses

typedef struct 
{
    char * ssid;
    int connected_clients;
    int signal_strength;

}GiveAPResponse;

#endif