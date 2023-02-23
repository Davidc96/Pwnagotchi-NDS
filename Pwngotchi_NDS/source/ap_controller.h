#ifndef APCONTROLLER_H
#define APCONTROLLER_H

#include <string.h>
#include "ap_node.h"

class APController
{
    public:
        APController();
        ~APController();

        void createNode(char * ssid, int connectedClients, int signal_strength, float value);
        
        APNode * getNodeBySSID(char * ssid);
        APNode * getFirstElement();
        void flush();
        int getNumElements();

    private:
        APNode * m_apnode;
        int m_count;
};

#endif