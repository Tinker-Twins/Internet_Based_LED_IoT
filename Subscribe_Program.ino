#include <ESP8266WiFi.h>
#include "Adafruit_MQTT_Client.h"

#define led 16
#define wifi "<WiFi Name>"                  // Enter WiFi Name here.
#define password "<Password>"               // Enter WiFi Password here.
#define server "io.adafruit.com"
#define port 1883
#define username "Username"                       // Enter Adafruit IO account Username here.
#define key "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"    // Enter Adafruit IO account Active Key here.

WiFiClient esp;
Adafruit_MQTT_Client mqtt(&esp,server,port,username,key);
Adafruit_MQTT_Subscribe feed = Adafruit_MQTT_Subscribe(&mqtt,username"/feeds/xxx");      // Replace "xxx" with your Feed Name (e.g. led)


void setup() {
  pinMode(led,OUTPUT);
  
  Serial.begin(115200);
  delay(10);
  Serial.println("Adafruit MQTT");
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi);

  WiFi.begin(wifi,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Connecting to MQTT");

  mqtt.subscribe(&feed);

  while(mqtt.connect()){
    delay(500);
    Serial.print(".");
  }
}


void loop() {
  while(mqtt.readSubscription(5000)){
    Serial.print("Got: ");
    Serial.print((char*)feed.lastread);
    int a = atoi((char*)feed.lastread);
    Serial.print(" ");
    Serial.println(a);

    if(a==0){
      digitalWrite(led,0);
    }
    else{
      digitalWrite(led,1);
    }
  }
}
