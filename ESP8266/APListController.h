#ifndef H_APLISTCONTROLLER_H
#define H_APLISTCONTROLLER_H

#include <Arduino.h>
#include "APNode.h"
#include "AP.h"

class APListController
{
    public:
        APListController();
        ~APListController();

        void createNode(char * ssid, uint8_t * bssid, int signal, int clients, int channel);
        void changeCurrentNode();
        void flush();

        AP * getAPFromCurrentNode();
        AP * getAPFromSSID(char * ssid);
        int getTotalNodes();

        void debugPrintNodes();


    private:
        APNode * m_first;
        APNode * m_currentNode;
        int m_total;
};

#endif
