#include <ESP8266WiFi.h>
#include "Adafruit_MQTT_Client.h"

#define ldr A0
#define wifi "<WiFi Name>"                  // Enter WiFi Name here.
#define password "<Password>"               // Enter WiFi Password here.
#define server "io.adafruit.com"
#define port 1883
#define username "Username"                       // Enter Adafruit IO account Username here.
#define key "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"    // Enter Adafruit IO account Active Key here.

WiFiClient esp;
Adafruit_MQTT_Client mqtt(&esp,server,port,username,key);
Adafruit_MQTT_Publish feed = Adafruit_MQTT_Publish(&mqtt,username"/feeds/xxx");   // Replace "xxx" with your Feed Name (e.g. ldr)


void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("Adafruit MQTT Demonstration");
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

  while(mqtt.connect()){
    Serial.print(".");
  }
}


void loop() {
  if(mqtt.connected()){
    int data = analogRead(ldr);
    Serial.print("\nSending LDR Data");
    Serial.print(data);
    Serial.print("...");

    if(feed.publish(data)){
      Serial.println("Success!");
    }
    else{
      Serial.println("Failure!");
    }
    delay(1250);
  }
}
