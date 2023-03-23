#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h> 

 
Servo myservo;
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>WiFi LED on off demo: 1</h1><br>
Ciclk to turn <a href="ledOn" target="myIframe">LED ON</a><br>
Ciclk to turn <a href="ledOff" target="myIframe">LED OFF</a><br>
LED State:<iframe name="myIframe" width="100" height="25" frameBorder="0"><br>
<hr>
<a href="https://circuits4you.com">circuits4you.com</a>
</center>

</body>
</html>
)=====";


#define LED1 0
#define LED2 2
//#define bt1 1 


IPAddress staticIP(192, 168, 1, 21); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway) 
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "Smart_Gorjaw";
const char* password = "gorjaw@!85";
const char* deviceName = "Smart Door of Tirkesh";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "tirkesh_gapy";


ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handle2() { 
 digitalWrite(LED1,1);
 digitalWrite(LED2,0);
 //digitalWrite(bt1,0);
 delay(250);
  digitalWrite(LED1,0); 
 digitalWrite(LED2,0);
 delay(5000);
 digitalWrite(LED1,0); 
 digitalWrite(LED2,1);
 delay(250);
 digitalWrite(LED1,0); 
 digitalWrite(LED2,0);
 //digitalWrite(bt1,0);
 server.send(200, "text/html", "one"); 
}
void handle0() { 
 digitalWrite(LED1,1);
 digitalWrite(LED2,0);
 //digitalWrite(bt1,0);
 delay(250);
  digitalWrite(LED1,0); 
 digitalWrite(LED2,0);
 server.send(200, "text/html", "one"); 
}
void handle1() { 
 digitalWrite(LED1,0);
 digitalWrite(LED2,1);
 //digitalWrite(bt1,0);
 delay(250);
  digitalWrite(LED1,0); 
 digitalWrite(LED2,0);
 server.send(200, "text/html", "one"); 
}
/*void handle0off() { 
 digitalWrite(LED1,0);
 digitalWrite(LED2,0);
 digitalWrite(bt1,1);
 delay(3000);
  digitalWrite(LED1,0); 
 digitalWrite(LED2,0);
 digitalWrite(bt1,0);
 server.send(200, "text/html", "one"); 
}*/


//==============================================================
//                  SETUP
//==============================================================
void handlePong() {
  server.send(200, "text/html", device_key);
}

void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  //Onboard LED port Direction output
  pinMode(LED1,OUTPUT); 
   pinMode(LED2,OUTPUT);
  //  pinMode(bt1,OUTPUT);
    digitalWrite(LED1,0); 
    digitalWrite(LED2,0); 
  //  digitalWrite(bt1,0); 
    
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
   server.on("/control/2", handle2); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/control/0", handle0);
   server.on("/control/1", handle1);
  server.on("/ping/", handlePong);
  

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient(); 
  
}
