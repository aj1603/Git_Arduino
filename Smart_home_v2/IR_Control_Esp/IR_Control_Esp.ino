#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <IRsend.h>
// Add this library: https://github.com/markszabo/IRremoteESP8266
#include <IRremoteESP8266.h>

#define IR_SEND_PIN 4
#define DELAY_BETWEEN_COMMANDS 1000
IRsend irsend(IR_SEND_PIN);

//Static IP address configuration
IPAddress staticIP(192, 168, 1, 178); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "Smart_Gorjaw";
const char* password = "gorjaw@!85";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "alondatv2";

ESP8266WebServer server(80);

const int led = BUILTIN_LED;


void handlePong(){
 server.send(200, "text/html", device_key);
}


void handleDevice(){
  String command = server.arg("command");

  command.trim();
  if (command.length() > 0){
    if (command == "down"){
      Serial.println("Sorround Sound Down");
      irsend.sendNEC(0x90FDDB24, 32);
      server.send(200, "text/plain", "Volume Down");
    }

    if (command == "up"){
      Serial.println("Surround Sound Up");
      irsend.sendNEC(0x90FD1BE4, 32);
      server.send(200, "text/plain", "Volume Up");
    }
    if (command == "satok"){
      Serial.println("Sat Ok");
      irsend.sendNEC(0xE0E06798, 32);
      server.send(200, "text/plain", "Sat OK");
    }
    if (command == "tvpower"){
      Serial.println("TV power");
      irsend.sendNEC(0x10EFEB14, 32);
      server.send(200, "text/plain", "TV Power");
    }
 if (command == "mute"){
      Serial.println("mute");
      irsend.sendNEC(0x10EFFB04, 32);
      server.send(200, "text/plain", " mute");
    }
    if (command == "volumedown"){
      Serial.println("volumedown");
      irsend.sendNEC(0x10EF619E, 32);
      server.send(200, "text/plain", "volumedown");
    }
 
   if (command == "upvolume"){
      Serial.println("volumedown");
      irsend.sendNEC(0x10EFC13E, 32);
      server.send(200, "text/plain", "volumedown");
    }

    if (command == "menu"){
      Serial.println("menu");
      irsend.sendNEC(0x10EF2BD4, 32);
      server.send(200, "text/plain", "menu");
    }

    if (command == "exit"){
      Serial.println("exit");
      irsend.sendNEC(0x10EF3BC4, 32);
      server.send(200, "text/plain", "exit");
    }

    if (command == "right"){
      Serial.println("Surround Sound Channel 3");
      irsend.sendNEC(0x10EFF906, 32);
      server.send(200, "text/plain", "Surround Sound Channel 3");
    }

    if (command == "left"){
      Serial.println("Surround Sound Channel 4");
      irsend.sendNEC(0x10EFE916, 32);
      server.send(200, "text/plain", "Surround Sound Channel 4");
    

   
     if (command == "iponoff"){
      Serial.println("iponoff");
      irsend.sendNEC(0x807F38C7, 32);
      server.send(200, "text/plain", "iponoff");
    }
    if (command == "iponoff1"){
      Serial.println("iponoff1");
      irsend.sendNEC(0xF111, 32);
      server.send(200, "text/plain", "iponoff");
    }

    if (command == "ipmute"){
      Serial.println("ipmute");
      irsend.sendNEC(0x807F42BD, 32);
      server.send(200, "text/plain", "ipmute");
    }

   

    if (command == "upip"){
      Serial.println("Sat Exit");
      irsend.sendNEC(0x807F58A7, 32);
      server.send(200, "text/plain", "Sat Exit");
    }

    if (command == "downip"){
      Serial.println("downip");
      irsend.sendNEC(0x807F12ED, 32);
      server.send(200, "text/plain", "downip");
    }

    if (command == "leftip"){
      Serial.println("leftip");
      irsend.sendNEC(0x807FE21D, 32);
      server.send(200, "text/plain", "leftip");
    }

    if (command == "rightip"){
      Serial.println("rightip");
      irsend.sendNEC(0x807FE01F, 32);
      server.send(200, "text/plain", "rightip");
    }
if (command == "volumeupip"){
      Serial.println("volumeupip");
      irsend.sendNEC(0x807FD22D, 32);
      server.send(200, "text/plain", "volumeupip");
    }
    if (command == "volumedownip"){
      Serial.println("volumedownip");
      irsend.sendNEC(0x807FF20D, 32);
      server.send(200, "text/plain", "volumedownip");
    }
    
  }
}

}
void setup(){
  irsend.begin();
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  Serial.begin(115200);
    
  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.disconnect();
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS Responder Started");
  }

  server.on("/ping/", handlePong);
  server.on("/control/", handleDevice);
  server.begin();
  Serial.println("HTTP Server Started");
}

void loop() {
  server.handleClient();
}
