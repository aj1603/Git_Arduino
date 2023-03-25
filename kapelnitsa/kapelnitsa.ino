// Author : Mudassar Tamboli
// Date   : 6/8/2018

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer server(80);
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

const char* mqttServer   = "192.168.43.1";
const int   mqttPort     = 1883;
const char* mqttUser     = "";
const char* mqttPassword = "";

#define PUB_GPIO_STATUS "status"
#define SUB_GPIO_ACTION "action"

String received_payload, ipAddress;
int relay_state;
unsigned long previousMillis = 0;
unsigned long interval = 30000;

boolean ldr, ldr2, ldr3, ldr4 = false;

//LDR sensor pins
const int ldr_sensor_1 = 16;
const int ldr_sensor_2 = 5;
const int ldr_sensor_3 = 4;
const int ldr_sensor_4 = 0;
const int led_pin_1 = 14;
const int led_pin_2 = 15;
const int led_pin_3 = 2;
const int led_pin_4 = 13;

//LDR sensor value
int ldr_1_value = 0;
int ldr_2_value = 0;
int ldr_3_value = 0;
int ldr_4_value = 0;


void setup() {
    Serial.begin(115200);

  pinMode(ldr_sensor_1, INPUT);
  pinMode(ldr_sensor_2, INPUT);
  pinMode(ldr_sensor_3, INPUT);
  pinMode(ldr_sensor_4, INPUT);
  pinMode(led_pin_1, OUTPUT);
  pinMode(led_pin_2, OUTPUT);
  pinMode(led_pin_3, OUTPUT);
  pinMode(led_pin_4, OUTPUT);
  digitalWrite(led_pin_1, HIGH);
  digitalWrite(led_pin_2, HIGH);
  digitalWrite(led_pin_3, HIGH);
  digitalWrite(led_pin_4, HIGH);
  
    initWifiStation();
    initMQTTClient();

    server.on("/version/", catchVersion);
} 

void loop() {
    mqttClient.loop();
    server.handleClient();

    unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    initWifiStation();
    previousMillis = currentMillis;
  }


  ldr_1_value = digitalRead(ldr_sensor_1);
  ldr_2_value = digitalRead(ldr_sensor_2);
  ldr_3_value = digitalRead(ldr_sensor_3);
  ldr_4_value = digitalRead(ldr_sensor_4);
  
  if (ldr_1_value == 1 && ldr == false) {
    digitalWrite(led_pin_1, LOW);
    mqttClient.publish(PUB_GPIO_STATUS, "101");
    ldr = true;
  }
  else if(ldr_1_value == 0 && ldr == true) {
    digitalWrite(led_pin_1, HIGH);
    mqttClient.publish(PUB_GPIO_STATUS, "100");
    ldr = false;
  }
  if (ldr_2_value == 1 && ldr2 == false) {
    digitalWrite(led_pin_2, LOW);
    mqttClient.publish(PUB_GPIO_STATUS, "201");
    ldr2 = true;
  }
  else if(ldr_2_value == 0 && ldr2 == true) {
    digitalWrite(led_pin_2, HIGH);
    mqttClient.publish(PUB_GPIO_STATUS, "200");
    ldr2 = false;
  }
  if (ldr_3_value == 1 && ldr3 == false) {
    digitalWrite(led_pin_3, LOW);
    mqttClient.publish(PUB_GPIO_STATUS, "301");
    ldr3 = true;
  }
  else if(ldr_3_value == 0 && ldr3 == true) {
    digitalWrite(led_pin_3, HIGH);
    mqttClient.publish(PUB_GPIO_STATUS, "300");
    ldr3 = false;
  }
  if (ldr_4_value == 1 && ldr4 == false) {
    digitalWrite(led_pin_4, LOW);
    mqttClient.publish(PUB_GPIO_STATUS, "401");
    ldr4 = true;
  }
  else if(ldr_4_value == 0 && ldr4 == true) {
    digitalWrite(led_pin_4, HIGH);
    mqttClient.publish(PUB_GPIO_STATUS, "400");
    ldr4 = false;
  }
  
  Serial.println(ldr_1_value);
  Serial.print(ldr_2_value);
  Serial.print(ldr_3_value);
  Serial.print(ldr_4_value);
  
}



//############### GETTING DATA FROM DEVICE WITH LOCALHOST #####################//
void catchVersion() {
  server.send(200, "text/html", "catch it");
}

 
void PubSubCallback(const MQTT::Publish& pub) {

  Serial.print(pub.topic());   // выводим в сериал порт название топика
  Serial.print(":");
  Serial.println(pub.payload_string()); // выводим в сериал порт значение полученных данных
  
  received_payload = pub.payload_string(); // сохраняем полученные данные
  
  if (String(pub.topic()) == SUB_GPIO_ACTION) { // если топик на который пришли данные, равен топику на который приходит состояние реле, то
    relay_state = received_payload.toInt(); // преобразуем полученные данные в тип integer

    if(relay_state == 1) {
        mqttClient.publish(PUB_GPIO_STATUS, "LDR 01");
        
    } else if(relay_state == 2){
        mqttClient.publish(PUB_GPIO_STATUS, "LDR 02");
        
    } else if(relay_state == 3){
        mqttClient.publish(PUB_GPIO_STATUS, "LDR 03");
        
    } else if(relay_state == 4){
        mqttClient.publish(PUB_GPIO_STATUS, "LDR 04");
        
    } else if(relay_state == 9) {
        delay(5000);
        initWifiStation();       
    } 
  }
}



//############### INIT WIFI STATION #####################//
void initWifiStation() {
    delay(10);
    Serial.println('\n');
    wifiMulti.addAP("Pip", "bionics123");   // add Wi-Fi networks you want to connect to
    wifiMulti.addAP("LDR", "12345678");
    Serial.println("Connecting ...");
    int i = 0;
    while (wifiMulti.run() != WL_CONNECTED) {
       delay(1000);        
       Serial.print(".");
    }
  WiFi.hostname("Kapelnitsa");
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer
  ipAddress = WiFi.localIP().toString();
  server.begin();
  Serial.println("HTTP server started");
}

//############### INIT MQTT CLIENT #####################//
void initMQTTClient() {
    mqttClient.set_server(mqttServer, mqttPort);
    mqttClient.set_callback(PubSubCallback);
    while (!mqttClient.connected()) {
        Serial.println(String("Connecting to MQTT (") + mqttServer + ")...");
        if (mqttClient.connect(MQTT::Connect("arduinoClient2")
         .set_auth(mqttUser, mqttPassword))) {
            Serial.println("MQTT client connected");    
        } else {
            Serial.print("\nFailed with state ");
//            Serial.println(mqttClient.state()); 
            if (WiFi.status() != WL_CONNECTED) {
               initWifiStation();
            }
            delay(5000);
        }
    }
    // Declare Pub/Sub topics
    mqttClient.publish(PUB_GPIO_STATUS, "active");
    mqttClient.subscribe(SUB_GPIO_ACTION);
}
