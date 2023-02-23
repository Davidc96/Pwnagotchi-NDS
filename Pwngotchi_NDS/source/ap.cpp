#include "ap.h"

AP::AP()
{
    m_ssid_name = "\0";
    m_connectedClients = 0;
}

AP::~AP()
{

}

void AP::setSSID(char * ssid_name)
{
    //m_ssid_name = ssid_name;
    strcpy(m_ssid_name, ssid_name);
}

void AP::setConnectedClients(int connectedClients)
{
    m_connectedClients = connectedClients;
}

void AP::setSignalStrength(int signalStrength)
{
    m_signalStrength = signalStrength;
}

char * AP::getSSID()
{
    return m_ssid_name;
}

int AP::getConnectedClients()
{
    return m_connectedClients;
}

int AP::getSignalStrength()
{
    return m_signalStrength;
}