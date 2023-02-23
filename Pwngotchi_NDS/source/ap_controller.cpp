#include "ap_controller.h"
#include <stdio.h>

APController::APController()
{
    m_apnode = new APNode();
    m_count = 0;
}

APController::~APController()
{

}

void APController::createNode(char * ssid, int connectedClients, int signal_strength, float value)
{
    APNode * iterator = m_apnode;
    APNode * current_node = iterator;

    while(iterator != NULL)
    {
        current_node = iterator;
        iterator = iterator->getNode();
    }

    APNode * new_node = new APNode();
    new_node->setValue(value);
    new_node->createAP(ssid, connectedClients, signal_strength);

    current_node->setNode(new_node);
    m_count++;
}

APNode * APController::getNodeBySSID(char * ssid)
{
    APNode * iterator = m_apnode->getNode();
    APNode * current_node = iterator;
    while(iterator != NULL)
    {
        current_node = iterator;
        if(strcmp(current_node->getAP()->getSSID(), ssid) == 0)
        {
            return current_node;
        }
        iterator = iterator->getNode();
    }

    return NULL;
}

APNode * APController::getFirstElement()
{
    return m_apnode;
}

int APController::getNumElements()
{
    return m_count;
}

void APController::flush()
{
    // Let's do it for each value in the list except the first node
    m_count = 0;
    m_apnode->setNode(NULL);
}