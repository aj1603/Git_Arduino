#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#define ServoPin 14
Servo myservo;

#define pin1 0
#define pin2 2

//curtain sketch
long curtain_delay = 2000; // seconds of curtain spin
long curtain_time = millis();
long curtainTime;
int curtain_direction = 0; // curtain up if = 1, down if = 2

IPAddress staticIP(192, 168, 1, 50); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway) 
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS

const char* ssid = "Akylly_Ahal_1";
const char* password = "akylly_ahal_1";
const char* deviceName = "curtain_control";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "curtain_control_esp";


ESP8266WebServer server(80); //Server on port 80

void handle0on() { 
  Serial.println("LED on page");
  digitalWrite(pin1,LOW); //LED is connected in reverse
  digitalWrite(pin2,HIGH);
  delay(3000);
  digitalWrite(pin1,LOW); //LED is connected in reverse
  digitalWrite(pin2,LOW);
  server.send(200, "text/html", "one"); //Send ADC value only to client ajax request
}

void handle0off() { 
  Serial.println("LED off page");
  digitalWrite(pin1,HIGH); //LED off
  digitalWrite(pin2,LOW);
  delay(3000);
  digitalWrite(pin1,LOW); //LED is connected in reverse
  digitalWrite(pin2,LOW);
  server.send(200, "text/html", "yza"); //Send ADC value only to client ajax request
 }

void handlePong() {
  server.send(200, "text/html", device_key);
}

void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  pinMode(pin1,OUTPUT); 
  pinMode(pin2,OUTPUT); 
  digitalWrite(pin1,LOW); 
  digitalWrite(pin2,LOW);   
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  
  server.on("/curtain_up", handle0on); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/cutain_down", handle0off);    
  server.on("/ping/", handlePong);


  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();  
}
