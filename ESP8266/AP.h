#ifndef H_AP_H
#define H_AP_H
#include <string.h>
#include <Arduino.h>
class AP
{
    public:
        AP();
        ~AP();
        void setSSID(char * ssid);
        void setSignal(int signal);
        void setClients(int clients);
        void setBSSID(uint8_t * bssid);
        void setChannel(int channel);

        char * getSSID();
        uint8_t * getBSSID();
        int getSignal();
        int getChannel();
        int getClients();
    
    private:
        char * m_ssid;
        uint8_t * m_bssid;
        int m_signal;
        int m_clients;
        int m_channel;
};

#endif
