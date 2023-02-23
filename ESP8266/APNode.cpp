#include "APNode.h"


APNode::APNode()
{
    m_ap = NULL;
    m_next = NULL;
}

APNode::~APNode()
{

}

void APNode::createAP(char * ssid, uint8_t * bssid, int signal, int clients, int channel)
{
    m_ap = new AP();
    
    m_ap->setSSID(ssid);
    m_ap->setSignal(signal);
    m_ap->setClients(clients);
    m_ap->setBSSID(bssid);
    m_ap->setSignal(signal);
    m_ap->setChannel(channel);
}

void APNode::setNextNode(APNode * next)
{
    m_next = next;
}

AP * APNode::getAP()
{
    return m_ap;
}

APNode * APNode::getNextNode()
{
    return m_next;
}