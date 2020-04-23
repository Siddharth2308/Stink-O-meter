#include <ESP8266Wifi.h>
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

String apiKey = "API key from thingspeak";
const char *ssid = "wifi ssid";
const char *pass = "password wifi cha";
const char *server = "api.thingspeak.com";
WifiCLient client;

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup()
{
Serial.begin(115200);
  while (!Serial)
  delay(10);
Serial.println("Connecting To...");
Serial.println(ssid);
Wifi.begin(ssid, pass);
while (Wifi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
}
  Serial.println("");
  Serial.println("Wifi Connected");  
}
void loop(){
float t = sht31.readTemperature();
float h = sht31.readHumidity(); //pins d1 ani d2 repectively
float a = analogRead(A0); // he Mq135 sathi

if (client.connect(server,80))
{
  String postStr = apiKey;
  postStr +="&field1=";
  postStr += String(t);
  postStr +="&field2=";
  postStr += String(h);
  postStr += String(a/1023*100);

  client.print("POST /update HTTP/1.1\n");
  client.print("Host: api.thingspeak.com\n");
  client.print("Connection: close\n");
  client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
  client.print("Content-Type: application/x-www-form-urlencoded\n");
  client.print("Content-Length: ");
  client.print(sendData.length());
  client.print("\n\n");
  client.print(postStr);
}
if (! isnan(t)) // to check if it is a number
{
  Serial.print("Temp *c =");
  Serial.println(t);
}
else{
  Serial.println("Failed to read temperature");
}
if (! isnan(h)) //varchya sarkhach
{
  Serial.print("Hum. % =");
  Serial.println(h);
}
else{
  Serial.println("Failed to read Humidity");
}
if (! isnan(a)){
  Serial.print(" Air quality(in ppm) =");
  Serial.println(a/1023*100);
}
Serial.println("Data sent to Thingspeak");
delay(1000);
}

