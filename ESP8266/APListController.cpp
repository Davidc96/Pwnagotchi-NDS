#include "APListController.h"

APListController::APListController()
{
    m_first = new APNode(); // Create the first element with nothing to start the list
    m_currentNode = m_first;
    m_total = 0;
}

APListController::~APListController()
{

}

void APListController::createNode(char * ssid, uint8_t * bssid, int signal, int clients, int channel)
{
    Serial.println("Create node function");
    Serial.print("SSID char: "); Serial.println(ssid);
    APNode * iterator = m_first;
    APNode * current_node = iterator;

    while(iterator != NULL)
    {
        current_node = iterator;
        iterator = iterator->getNextNode();
    }

    Serial.println("End of iteration: Creating APNode");
    APNode * new_node = new APNode();
    new_node->createAP(ssid, bssid, signal, clients, channel);

    current_node->setNextNode(new_node);
    m_total += 1;
}

void APListController::changeCurrentNode()
{
    if(m_total == 0)
    {
        return; // If there is no element, why use this function?
    }

    if(m_currentNode->getNextNode() == NULL)
    {
        m_currentNode = m_first->getNextNode();
    }

    m_currentNode = m_currentNode->getNextNode();
}

void APListController::flush()
{
    // Delete the root element (TODO: Delete all the elements to avoid memory overflows)
    m_total = 0;
    m_first->setNextNode(NULL);
}

AP * APListController::getAPFromCurrentNode()
{
    return m_currentNode->getAP();
}

int APListController::getTotalNodes()
{
    return m_total;
}

AP * APListController::getAPFromSSID(char * ssid)
{
    APNode * iterator = m_first->getNextNode();
    APNode * current_node = iterator;
    while(iterator != NULL)
    {
        current_node = iterator;
        if(strcmp(current_node->getAP()->getSSID(), ssid) == 0)
        {
            return current_node->getAP();
        }
        iterator = iterator->getNextNode();
    }

    return NULL;
}

void APListController::debugPrintNodes()
{
    Serial.println("------- DEBUG PRINT AP NODES -------");
    Serial.print("TOTAL: "); Serial.println(m_total);
    APNode * iterator = m_first->getNextNode();
    APNode * current_node = iterator;
    while(iterator != NULL)
    {
        current_node = iterator;
          
        Serial.print("SSID: "); Serial.println(current_node->getAP()->getSSID());
        Serial.print("RSSI: "); Serial.println(current_node->getAP()->getSignal());
        Serial.print("Channel: "); Serial.println(current_node->getAP()->getChannel());
        Serial.print("BSSID: "); Serial.println(current_node->getAP()->getBSSID()[0]);
        iterator = iterator->getNextNode();
    }
    Serial.println("------- END DEBUG PRINT AP NODES -------");
}
