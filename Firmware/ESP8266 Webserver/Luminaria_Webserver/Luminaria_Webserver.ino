/*
 Udp NTP Client
 Get the time from a Network Time Protocol (NTP) time server
 Demonstrates use of UDP sendPacket and ReceivePacket
 For more on NTP time servers and the messages needed to communicate with them,
 see http://en.wikipedia.org/wiki/Network_Time_Protocol
 created 4 Sep 2010
 by Michael Margolis
 modified 9 Apr 2012
 by Tom Igoe
 updated for the ESP8266 12 Apr 2015
 by Ivan Grokhotkov
 This code is in the public domain.
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Time.h>
#include <TimeLib.h>

#include <SoftwareSerial.h>

#include "credentials.h"
char ssid[] = credentialsSSID;  //  your network SSID (name)
char pass[] = credentialsPASS;       // your network password


boolean timeReset = true;
boolean timeAlreadySet = false;
#include "NTP-request.h"



WiFiServer server(80);

SoftwareSerial swSer(14, 12, false, 128); //(RX, TX, invert, buffer)




void setup()
{
  Serial.begin(115200);
  swSer.begin(9600);
  Serial.println();
  Serial.println();

  initWiFi();
}

void loop()
{
  if (hour() > 20 && timeReset) {
    timeAlreadySet = false;
    timeReset = false;
  }
  if (hour() == 19) {
    timeReset = true;
  }

  if (timeAlreadySet && server.status() != 1) {
    // Start the server
    server.begin();
    Serial.println(server.status());
  }
  if (server.status() == 1) {
    webServer();
  }

  if (!timeAlreadySet) {
    getAndPrintTime();
  }
}




void initWiFi(){
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  // config static IP
  IPAddress ip(10,0,1,200); // where xx is the desired IP Address
  IPAddress gateway(10,0,1,1); // set gateway to match your network
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
  WiFi.config(ip, gateway, subnet);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  }

