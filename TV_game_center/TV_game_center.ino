// samsung tv un
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
IPAddress staticIP(192, 168, 43, 17); //ESP static ip
IPAddress gateway(192, 168, 43, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS

const char* ssid = "Pip1";
const char* password = "bionics123";
String serverUrl = "192.168.43.252";
String payload;
String device_key = "assfndgdsf4567)N$3zx4aqed2";

ESP8266WebServer server(80);

const int led = BUILTIN_LED;


void handlePong() {
  server.send(200, "text/html", device_key);
}


void handleDevice() {
  String command = server.arg("command");

  command.trim();
  if (command.length() > 0) {
    if (command == "down") {
      Serial.println("Sorround Sound Down");
      irsend.sendNEC(0xE0E08679, 32);
      server.send(200, "text/plain", "Volume Down");
    }

    if (command == "up") {
      Serial.println("Surround Sound Up");
      irsend.sendNEC(0xE0E006F9, 32);
      server.send(200, "text/plain", "Volume Up");
    }

    if (command == "sspower") {
      Serial.println("Surround Sound power");
      irsend.sendNEC(0xE0E06798, 32);
      server.send(200, "text/plain", "Surround Sound Power");
    }

    if (command == "volumeup") {
      Serial.println("Surround Sound Channel 1");
      irsend.sendNEC(0xE0E046B9, 32);
      server.send(200, "text/plain", "Surround Sound Channel 1");
    }

    if (command == "volumedown") {
      Serial.println("Surround Sound Channel 2");
      irsend.sendNEC(0xE0E0A659, 32);
      server.send(200, "text/plain", "Surround Sound Channel 2");
    }

    if (command == "source") {
      Serial.println("Surround Sound Channel 3");
      irsend.sendNEC(0xE0E0807F, 32);
      server.send(200, "text/plain", "Surround Sound Channel 3");
    }

    if (command == "ok") {
      Serial.println("Surround Sound Channel 4");
      irsend.sendNEC(0xE0E016E9, 32);
      server.send(200, "text/plain", "Surround Sound Channel 4");
    }


    if (command == "chromecast") {
      Serial.println("Chromecast");
      irsend.sendNEC(0x20DFD02F, 32);
      delay(DELAY_BETWEEN_COMMANDS);
      irsend.sendNEC(0x20DFD02F, 32);
      delay(DELAY_BETWEEN_COMMANDS);
      irsend.sendNEC(0x4BB6906F, 32);
      server.send(200, "text/plain", "Chromecast");
    }
  }
}


void setup() {
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
}

void loop() {
  server.handleClient();
}
