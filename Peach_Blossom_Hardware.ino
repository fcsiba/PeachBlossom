
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


#define WIFI_SSID "ZONG MBB-E8372-6952"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "86241381"                                    //password of wifi ssid
 int motorPin = D0; // pin that turns on the motor
int Sensorvalue=0;
int sensorPin=A0;
int sensorValuePercent=0;

char auth[] = "5049007b2b964f8693b0bf6ca530878c";
//const int sensorPin = 0; 

int blinkPin = 13; // pin that turns on the LED


void setup()
{ Serial.begin(9600);
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
 
  Blynk.begin(auth, WIFI_SSID, WIFI_PASSWORD);
  pinMode(sensorPin, INPUT);
  pinMode(motorPin, OUTPUT); // set A0 to an output so we can use it to turn on the transistor
  pinMode(blinkPin, OUTPUT); // set pin 13 to an output so we can use it to turn on the LED
  //Start reading dht sensor
}
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
   if(pinValue == 1) {     // if Button sends 1
    digitalWrite(motorPin, HIGH);  // turn on the motor
  }
  else{
     digitalWrite(motorPin, LOW); // turn off the motor
  }
}
void loop()
{ 
   Sensorvalue = analogRead (A0); 
       Serial.print("Sensor value= ");
  Serial.println(Sensorvalue);
  
 Sensorvalue = map(Sensorvalue, 1010,1100,1023,0);
 sensorValuePercent = (Sensorvalue)*10; // In Prozent﻿
      Serial.print("Sensor map= ");
  Serial.println(Sensorvalue);
  Blynk.run();

  Blynk.virtualWrite(V5, sensorValuePercent);

    delay(1000);
}
  
  
