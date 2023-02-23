#ifndef H_APNODE_H
#define H_APNODE_H
#include <Arduino.h>
#include "AP.h"

class APNode
{
    public:
        APNode();
        ~APNode();
        void createAP(char * ssid, uint8_t * bssid, int signal, int clients, int channel);
        void setNextNode(APNode * next);

        AP * getAP();
        APNode * getNextNode();
    
    private:
        AP * m_ap;
        APNode * m_next;
};

#endif
