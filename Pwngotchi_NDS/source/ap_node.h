#ifndef AP_NODE_H
#define AP_NODE_H
#include "ap.h"
#include <cstddef>

class APNode
{
    public:
        APNode();
        ~APNode();
        void setValue(int value);
        void createAP(char * ssid, int connectedClients, int signalStrength);
        void setNode(APNode * next_node);
        void setAttacked(bool attacked);

        int getValue();
        bool isAttacked();
        AP * getAP();
        APNode * getNode();

    private:
        int m_value;
        AP * m_ap;
        APNode * m_next;
        bool m_attacked;
};

#endif