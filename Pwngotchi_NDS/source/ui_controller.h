#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

#include <nds.h>
#include <stdio.h>

// FACES
#include "angry.h"
#include "awaked.h"
#include "bored.h"
#include "cool.h"
#include "happy.h"
#include "intense.h"
#include "left_happy.h"
#include "right_happy.h"
#include "left_looking.h"
#include "right_looking.h"
#include "sad.h"
//#include "messages.h"

enum FACES 
{
    ANGRY,
    AWAKED,
    BORED,
    COOL,
    HAPPY,
    INTENSE,
    LEFT_HAPPY,
    RIGHT_HAPPY,
    LEFT_LOOKING,
    RIGHT_LOOKING,
    SAD
};

class UIController
{
    public:
        UIController();
        ~UIController();
        void init();
        void update();
        void setFace(FACES selectedFace);
        void setCurrentChannel(int currentChannel);
        void setAPinChannel(int APinChannel);
        void setAPTotal(int APTotal);
        void setSentence(char * sentence);
        void setDbgFrame(int dbg_frame);
        void setSSIDName(char * ssid);

    private:
        FACES m_selectedFace;
        int m_bg;
        int m_currentChannel;
        int m_APinChannel;
        int m_APTotal;
        int m_dbg_frame;
        
        char * m_sentence;
        char * m_ssid;
    
};

#endif