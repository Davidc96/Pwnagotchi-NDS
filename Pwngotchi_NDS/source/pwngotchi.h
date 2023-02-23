#ifndef PWNGOTCHI_H
#define PWNGOTCHI_H

#include <nds.h>

#include "ap.h"
#include "ap_node.h"
#include "ap_controller.h"
#include "messages.h"
#include "spi_controller.h"
#include "wifi_controller.h"
#include "wifi_commands.h"
#include "spi_commands.h"
#include "ui_controller.h"
#include "utils.h"

#define PWNGOTCHI_DONOTHING 1
#define PWNGOTCHI_OBTAIN 2
#define PWNGOTCHI_ATTACK 3
#define PWNGOTCHI_EVALUATE 4

//#define DEBUG


class Pwngotchi
{
    public:
        Pwngotchi();
        ~Pwngotchi();

        void init();
        void run();
        void setDebugFrame(int frame);
    private:
        UIController * m_uicontroller;
        SPIController * m_spicontroller;
        APController * m_apcontroller;
        WifiController * m_wificontroller;

        FACES m_status;
        int m_totalAPs;
        int m_happyness;
        int m_currentChannel;
        int m_APTargetsCount;
        int m_dbg_frame;

        APNode * m_selectedTarget;

        int m_grade;
        bool  m_isWorking;

        bool m_isObtaining;
        bool m_isEvaluating;
        bool m_isAttacking;

        bool m_askTotalAP;
        bool m_askRescanAP;
        
        void doWorkCallback();
        void changeHappyness(int rate);
        int calculateWhatHeWants();



};
#endif