#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define waterPin A0
#define rainPin 5

const char* ssid = "Redmi";
const char* password = "123456789";
const char* serverName = "http://192.168.54.131/logging_iot/iot.php";
String apiKeyValue = "123456789";
String sensorName = "Water Level";

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Terhubung dengan jaringan WiFi dengan alamat IP:");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client;
  HTTPClient http;

  int waterValue = analogRead(waterPin);
  int rainValue = digitalRead(rainPin);
  Serial.print("Air = ");
  Serial.println(waterValue);
  Serial.print("Hujan = ");
  Serial.println(rainValue);

  String address;
  address = String(serverName);
  address += "?api_key=";
  address += String(apiKeyValue);
  address += "&sensor=water_level";
  address += "&ketinggian=";
  address += String(waterValue);
  address += "&status=";
  address += String(rainValue);

  http.begin(client, address);

  int statusCode = http.GET();
  if(statusCode > 0){
    Serial.print("HTTP Response Code: ");
    Serial.println(statusCode);
  }
  else{
    Serial.print("Error Code: ");
    Serial.println(statusCode);
  }
  http.end();
  delay(5000);
}