#ifndef AP_H
#define AP_H
#include <string.h>

class AP
{
    public:
        AP();
        ~AP();

        void setSSID(char * ssid_name);
        void setConnectedClients(int connectedClients);
        void setSignalStrength(int signalStrength);

        char * getSSID();
        int getConnectedClients();
        int getSignalStrength();

    private:
        char * m_ssid_name;
        int m_connectedClients;
        int m_signalStrength;

};


#endif