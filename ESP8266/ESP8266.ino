#include "WifiController.h"
#include <ESP8266WebServer.h>

volatile byte i;
volatile bool pin;
volatile int command;
WifiController wifi_controller;
ESP8266WebServer server(80);

void getTotalAPs()
{
  Serial.println("FUNCTION TOTAL AP");
  int total_aps = wifi_controller.getTotalAPs();
  char response[255];
  sprintf(response, "%d", total_aps);
  Serial.print("DATA: ");
  Serial.println(response);
  server.send(200, "text/plain", response);
}

void getCurrentAPInfo()
{
  char response[255];
  Serial.println("FUNCTION CURRENTAP INFO");
  char * ssid_name = wifi_controller.getCurrentAPInfo()->getSSID();
  int connected_clients = wifi_controller.getCurrentAPInfo()->getClients();
  int signal_strength = wifi_controller.getCurrentAPInfo()->getSignal();
  Serial.println("OBTAINED DATA");
  sprintf(response, "%s;%d;%d", ssid_name, connected_clients, signal_strength);
  Serial.println(response);
  server.send(200, "text/plain", response);
}

void changeCurrentNode()
{
  Serial.println("FUNCTION CHANGE NODE");
  wifi_controller.changeCurrentNode();
  server.send(200, "text/plain", "OK");
}

void selectCurrentNode()
{
  Serial.println("FUNCTION SELECT NODE");
  wifi_controller.selectCurrentNode();
  server.send(200, "text/plain", "OK");
}

void attackSelectedNode()
{
  Serial.println("FUNCTION ATTACK");
  server.send(200, "text/plain", "OK");
  wifi_controller.changeSTAMode();
  wifi_controller.deauthAP();
  wifi_controller.changeAPMode();
}

void rescanAPs()
{
  Serial.println("FUNCTION RESCAN");
  server.send(200, "text/plain", "OK");
  wifi_controller.changeSTAMode();
  wifi_controller.scanEnvironment();
  wifi_controller.changeAPMode();
}

void setup() 
{
  Serial.begin(9600);
  wifi_controller.init();

  // Let's scan the environment to get all the APs and then swap to AP Mode
  wifi_controller.changeSTAMode();
  wifi_controller.scanEnvironment();
  wifi_controller.changeAPMode();
  
  // Config webserver
  server.on("/count", getTotalAPs);
  server.on("/give", getCurrentAPInfo);
  server.on("/next", changeCurrentNode);
  server.on("/select", selectCurrentNode);
  server.on("/attack", attackSelectedNode);
  server.on("/rescan", rescanAPs);

  server.begin();
}



void loop() 
{
  server.handleClient();
}
