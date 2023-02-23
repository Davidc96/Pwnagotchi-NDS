#ifndef H_WIFICONTROLLER_H
#define H_WIFICONTROLLER_H

#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <String.h>

#include "APListController.h"

class WifiController
{
  // Extracted from https://github.com/justcallmekoko/ESP8266_Deauth_All/blob/master/deauth_all.ino

    uint8_t deauthPacket[26] = {
          /*  0 - 1  */ 0xC0, 0x00, //type, subtype c0: deauth (a0: disassociate)
          /*  2 - 3  */ 0x00, 0x00, //duration (SDK takes care of that)
          /*  4 - 9  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,//reciever (target) -> broadcast
          /* 10 - 15 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, //source (ap)
          /* 16 - 21 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, //BSSID (ap)
          /* 22 - 23 */ 0x00, 0x00, //fragment & squence number
          /* 24 - 25 */ 0x01, 0x00 //reason code (1 = unspecified reason)
    };

    public:
        WifiController();
        ~WifiController();

        void init();
        void changeAPMode();
        void changeSTAMode();
        void scanEnvironment();
        void deauthAP();
        void changeCurrentNode();
        void selectCurrentNode();

        void debugPrintNodes();
        AP * getCurrentAPInfo();
        int getTotalAPs();

    private:
        APListController * m_aplist;
        AP * m_selected;

};

#endif
