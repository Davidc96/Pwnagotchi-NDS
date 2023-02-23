#include "ap_node.h"

APNode::APNode()
{
    m_ap = NULL;
    m_next = NULL;
    m_attacked = false;

    m_value = 0;
}

APNode::~APNode()
{

}

void APNode::createAP(char * ssid_name, int connectedClients, int signalStrength)
{
    m_ap = new AP();
    
    m_ap->setSSID(ssid_name);
    m_ap->setConnectedClients(connectedClients);
    m_ap->setSignalStrength(signalStrength);

}

void APNode::setNode(APNode * next_node)
{
    m_next = next_node;
}

void APNode::setValue(int value)
{
    m_value = value;
}

void APNode::setAttacked(bool attacked)
{
    m_attacked = attacked;
}

AP * APNode::getAP()
{
    return m_ap;
}

APNode * APNode::getNode()
{
    return m_next;
}

int APNode::getValue()
{
    return m_value;
}

bool APNode::isAttacked()
{
    return m_attacked == true;
}
