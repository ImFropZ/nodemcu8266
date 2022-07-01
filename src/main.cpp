#include <Arduino.h>
#include <ESP8266WiFi.h>
const char* SSID = "SMART-WIFI-06R8";
const char* PASSWORD = "SMART06F8";

WiFiServer server(80);

const int outputPin = 2;

void setup() {
  Serial.begin(9600);

  pinMode(outputPin,OUTPUT);
  digitalWrite(outputPin,LOW);
  Serial.print("Connecting to SSID: ");
  Serial.println(SSID);

  WiFi.begin(SSID,PASSWORD);

  while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.println(".");
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if(!client) return;
  while(!client.available()) {}
  Serial.println(client.readStringUntil('\r'));
  client.flush();

  int value = LOW;
  if(client.readStringUntil('\r').indexOf("/led/1") != -1) {
    value = HIGH;
    digitalWrite(outputPin, value);
  }else if(client.readStringUntil('\r').indexOf("/led/0") != -1) {
    value = LOW;
    digitalWrite(outputPin, value);
  }

  client.println("<html>\n<head><head/>");
  client.println("<body>");
  client.println(value);
  client.println("<body/>\n<html/>");
}