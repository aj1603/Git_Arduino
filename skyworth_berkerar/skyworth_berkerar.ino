// oscar tv un
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
IPAddress staticIP(192, 168, 0, 186); //ESP static ip
IPAddress gateway(192, 168, 0, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS

const char* ssid = "TP-LINK_BF4C";
const char* password = "1020304050";
String serverUrl = "192.168.0.252";
String payload;
String device_key = "some_magic_word_3";

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
      Serial.println("down");
      irsend.sendNEC(0xE0E08679, 32);
      server.send(200, "text/plain", "Volume Down");
    }

    if (command == "up") {
      Serial.println("Up");
      irsend.sendNEC(0xE0E006F9, 32);
      server.send(200, "text/plain", "Up");
    }

    if (command == "sspower") {
      Serial.println("sspower");
      irsend.sendNEC(0xE0E040BF, 32);
      server.send(200, "text/plain", "sspower");
    }

    if (command == "volumeup") {
      Serial.println("Volumeup");
      irsend.sendNEC(0xE0E046B9, 32);
      server.send(200, "text/plain", "Volumeup");
    }

    if (command == "volumedown") {
      Serial.println("Volumedown");
      irsend.sendNEC(0xE0E0A659, 32);
      server.send(200, "text/plain", "Volumedown");
    }

    if (command == "source") {
      Serial.println("Source");
      irsend.sendNEC(0xE0E0807F, 32);
      server.send(200, "text/plain", "Source");
    }

    if (command == "ok") {
      Serial.println("Ok");
      irsend.sendNEC(0xE0E016E9, 32);
      server.send(200, "text/plain", "Ok");
    }
    if (command == "0") {
      Serial.println("Reklama_gec");
      irsend.sendNEC(0x7070F00F, 32);
      delay(600);
      irsend.sendNEC(0x7070C23D, 32);
      delay(600);
      irsend.sendNEC(0x7070C23D, 32);
      delay(600);
      irsend.sendNEC(0x7070629D, 32);
      delay(1500);
      irsend.sendNEC(0x7070629D, 32);
      delay(1500);
      irsend.sendNEC(0x7070629D, 32);
      delay(1500);
      irsend.sendNEC(0x7070C23D, 32);
      delay(600);
      irsend.sendNEC(0x7070926D, 32);
      server.send(200, "text/plain", "Reklama");
    }
    if (command == "1") {
      Serial.println("Oyuna_gec");
      irsend.sendNEC(0x7070F00F, 32);
      delay(600);
      irsend.sendNEC(0x707042BD, 32);
      delay(600);
      irsend.sendNEC(0x707042BD, 32);
      delay(600);
      irsend.sendNEC(0x7070629D, 32);
      server.send(200, "text/plain", "Reklama_gecdi");
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
  Serial.println("HTTP Server Started");
}

void loop() {
  server.handleClient();
}
