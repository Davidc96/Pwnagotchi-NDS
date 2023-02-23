#include "ui_controller.h"

UIController::UIController()
{
    m_APinChannel = 0;
    m_APTotal = 0;
    m_currentChannel = 0;
    m_bg = 0;
    m_selectedFace = HAPPY;
    m_sentence = (char *)"Hello world";
}

UIController::~UIController()
{

}

void UIController::init()
{
    videoSetMode(MODE_4_2D);
    videoSetModeSub(MODE_4_2D);
    vramSetBankA(VRAM_A_MAIN_BG_0x06000000);

	consoleInit(0, 0, BgType_Text4bpp, BgSize_T_256x256, 4, 0, true, true);

	m_bg = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 5,0); 
}

void UIController::update()
{
    switch(m_selectedFace)
    {
        case ANGRY:
            dmaCopy(angryBitmap, bgGetGfxPtr(m_bg), 256*256);
	        dmaCopy(angryPal, BG_PALETTE, 256*2);
            break;
        case AWAKED:
            dmaCopy(awakedBitmap, bgGetGfxPtr(m_bg), 256*256);
	        dmaCopy(awakedPal, BG_PALETTE, 256*2);
            break;
        case BORED:
            dmaCopy(boredBitmap, bgGetGfxPtr(m_bg), 256*256);
	        dmaCopy(boredPal, BG_PALETTE, 256*2);
            break;
        case COOL:
            dmaCopy(coolBitmap, bgGetGfxPtr(m_bg), 256*256);
	        dmaCopy(coolPal, BG_PALETTE, 256*2);
            break;
        case HAPPY:
            dmaCopy(happyBitmap, bgGetGfxPtr(m_bg), 256*256);
	        dmaCopy(happyPal, BG_PALETTE, 256*2);
            break;
        case INTENSE:
            dmaCopy(intenseBitmap, bgGetGfxPtr(m_bg), 256*256);
	        dmaCopy(intensePal, BG_PALETTE, 256*2);
            break;
        case LEFT_HAPPY:
            dmaCopy(left_happyBitmap, bgGetGfxPtr(m_bg), 256*256);
	        dmaCopy(left_happyPal, BG_PALETTE, 256*2);
            break;
        case RIGHT_HAPPY:
            dmaCopy(right_happyBitmap, bgGetGfxPtr(m_bg), 256*256);
	        dmaCopy(right_happyPal, BG_PALETTE, 256*2);
            break;
        case LEFT_LOOKING:
            dmaCopy(left_lookingBitmap, bgGetGfxPtr(m_bg), 256*256);
	        dmaCopy(left_lookingPal, BG_PALETTE, 256*2);
            break;
        case RIGHT_LOOKING:
            dmaCopy(right_lookingBitmap, bgGetGfxPtr(m_bg), 256*256);
	        dmaCopy(right_lookingPal, BG_PALETTE, 256*2);
            break;
        case SAD:
            dmaCopy(sadBitmap, bgGetGfxPtr(m_bg), 256*256);
	        dmaCopy(sadPal, BG_PALETTE, 256*2);
            break;
        default:
            dmaCopy(angryBitmap, bgGetGfxPtr(m_bg), 256*256);
	        dmaCopy(angryPal, BG_PALETTE, 256*2);
            break;

    }

    #ifndef DEBUG
        // Clear screen first
        iprintf("\x1b[2J");

        // HEADER -> Current Channel, Current APS in channel, APS found in total
        iprintf("\x1b[2;2HCH: %d    APS %d (%d)   Ping:%d", m_currentChannel, m_APinChannel, m_APTotal, m_dbg_frame % 100);

        // BODY (NAME, DIALOG)
        iprintf("\x1b[6;18HName>");
        iprintf("\x1b[15;1H%s", m_sentence);
        
        
        //FOOTER
        iprintf("\x1b[22;1H Selected AP: %s", m_ssid);
    #endif
}

void UIController::setAPinChannel(int APinChannel)
{
    m_APinChannel = APinChannel;
}

void UIController::setAPTotal(int APTotal)
{
    m_APTotal = APTotal;
}

void UIController::setCurrentChannel(int currentChannel)
{
    m_currentChannel = currentChannel;
}

void UIController::setFace(FACES selectedFace)
{
    m_selectedFace = selectedFace;
}

void UIController::setSentence(char * sentence)
{
    m_sentence = sentence;
}

void UIController::setDbgFrame(int dbg_frame)
{
    m_dbg_frame = dbg_frame;
}

void UIController::setSSIDName(char * ssid)
{
    m_ssid = ssid;
}