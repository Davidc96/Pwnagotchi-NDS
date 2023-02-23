#include "AP.h"

AP::AP()
{
    m_ssid = new char[32];
    m_bssid = new uint8_t[6];
    m_signal = 0;
    m_clients = 0;
    m_channel = 0;
}

AP::~AP()
{

}

void AP::setSSID(char * ssid)
{
    Serial.println("Set SSID function");

    /*for(int i = 0; i < 32; i++)
    {
      m_ssid[i] = ssid[i];
    }*/
    memcpy(m_ssid, ssid, 32);
}

void AP::setSignal(int signal)
{
    m_signal = signal;
}

void AP::setClients(int clients)
{
    m_clients = clients;
}

void AP::setBSSID(uint8_t * bssid)
{
    Serial.println("Set BSSID function");
    memcpy(m_bssid, bssid, 6);
}

void AP::setChannel(int channel)
{
    m_channel = channel;
}

char * AP::getSSID()
{
    return m_ssid;
}

uint8_t * AP::getBSSID()
{
    return m_bssid;
}

int AP::getSignal()
{
    return m_signal;
}

int AP::getClients()
{
    return m_clients;
}

int AP::getChannel()
{
    return m_channel;
}
