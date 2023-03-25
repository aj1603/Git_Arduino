#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

IPAddress staticIP(192, 168, 1, 134);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);

const int ledPin = 15;
int brightness1 = 62;
int brightness2 = 124;
int brightness3 = 186;
int brightness4 = 254;

const char* ssid = "Akylly_Ahal_1";
const char* password = "akylly_ahal_1";
const char* deviceName = "Dimmer_control";
String payload;
String device_key = "dimmer_control_esp";
String command = "dimmer_control";
String validation_key = "key";

ESP8266WebServer server(80);

String dimmer_input = "<input style=\"height: 200px;width: 600px;font-size: 50px;\" type=\"text\" name=\"dimmer_input\" placeholder=\"ID Key\"></br>";
String submit_input = "<input type=\"submit\" style=\"border-radius: 50px 50px 50px 50px;text-align:center;height:150px;font-size:50px;width:400px;color:white;background-color: #00A8A9\" value=\"OK\">";


String div_view = "<div>";
String form_view = "<form style=\"margin-top: 180px;display:flex;flex-direction: column;align-items: center;\" action=\"/ulanyjy\" method=\"POST\">";
String form_end_view = "</form></div>";
String html_view = div_view + form_view + dimmer_input + submit_input + form_end_view;


void handlePong() {
  server.send(200, "text/html", device_key);
}

void handleDevice() {
  String dimmerstate1 = server.arg("dimmer_state_1");
  String dimmerstate2 = server.arg("dimmer_state_2");
  String dimmerstate3 = server.arg("dimmer_state_3");
  String dimmerstate4 = server.arg("dimmer_state_4");

  dimmerstate1.trim();
  dimmerstate2.trim();
  dimmerstate3.trim();
  dimmerstate4.trim();

  if(dimmerstate1 == "1"){
    Serial.print("Dimmer is set 1");
    analogWrite(ledPin, brightness1);     
  }
  else if(dimmerstate1 == "0"){
    Serial.print("Dimmer is set 0");
    digitalWrite(ledPin, 0);    
  }
  if(dimmerstate2 == "1"){
    Serial.print("Dimmer is set 2");
    analogWrite(ledPin, brightness2);     
  }
  else if(dimmerstate2 == "0"){
    Serial.print("Dimmer is set 2");
    digitalWrite(ledPin, 0);    
  }
  if(dimmerstate3 == "1"){
    Serial.print("Dimmer is set 3");
    analogWrite(ledPin, brightness3);    
  }
  else if(dimmerstate3 == "0"){
    Serial.print("Dimmer is set 3");
    digitalWrite(ledPin, 0);    
  }
  if(dimmerstate4 == "1"){
    Serial.print("Dimmer is set 4");
    analogWrite(ledPin, brightness4);    
  }
  else if(dimmerstate4 == "0"){
    Serial.print("Dimmer is set 4");
    digitalWrite(ledPin, 0);  
  }
 server.send(200, "text/html", "OK");
}

void handleRoot(){
  server.send(200, "text/html", html_view);
}

void handleFormSubmit(){
  if( !server.hasArg("dimmer_input") || server.arg("dimmer_input") == NULL) {
    server.send(200, "text/html", html_view);
    return;
  }
  if (server.arg("dimmer_input") == "0") {
    Serial.println("Dimmer is set 0");
    digitalWrite(ledPin, 0);
    server.send(200, "text/html", html_view);
  }
  else if (server.arg("dimmer_input") == "1") {
    Serial.println("Dimmer is set 1");
    analogWrite(ledPin, brightness1);
    server.send(200, "text/html", html_view);
  }
  else if (server.arg("dimmer_input") == "2") {
    Serial.println("Dimmer is set 2");
    analogWrite(ledPin, brightness2);
    server.send(200, "text/html", html_view);
  }
  else if (server.arg("dimmer_input") == "3") {
    Serial.println("Dimmer is set 3");
    analogWrite(ledPin, brightness3);
    server.send(200, "text/html", html_view);
  }
  else if (server.arg("dimmer_input") == "4") {
    Serial.println("Dimmer is set 4");
    analogWrite(ledPin, brightness4);
    server.send(200, "text/html", html_view);
  }
  else {
    server.send(200, "text/html", html_view);
  }
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WiFi.disconnect();
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  delay(500);
  Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT);
  
  server.on("/ping/", handlePong);
  server.on("/control/", handleDevice);
  server.on("/validation/", handleRoot);
  server.on("/ulanyjy", handleFormSubmit);
  server.begin();
}

void loop() {
  server.handleClient();
}
