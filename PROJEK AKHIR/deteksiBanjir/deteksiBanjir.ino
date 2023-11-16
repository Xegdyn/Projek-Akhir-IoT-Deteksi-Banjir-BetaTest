#include <ESP8266WiFi.h>

const char* ssid = "WiFiBang";
const char* password = "wfim6136";

const int rainPin = D0;  // Pin untuk sensor hujan
const int waterLevelPin = A0;  // Pin untuk sensor ketinggian air
const int thresholdWaterLevel = 500;  // Ubah nilai ini sesuai dengan tinggi air yang diinginkan
const int delayInterval = 10000;  // Jeda pemberitahuan dalam milidetik (10 detik)

bool isRaining = false;

void setup() {
  Serial.begin(115200);

  // Hubungkan ke WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  pinMode(rainPin, INPUT);
}

void loop() {
  int rainValue = digitalRead(rainPin);

  if (rainValue == HIGH) {
    isRaining = true;
    Serial.println("Hujan terdeteksi. Sistem diaktifkan.");
  } else {
    isRaining = false;
    Serial.println("Tidak ada hujan. Sistem menunggu...");
  }

  while (isRaining) {
    int waterLevel = analogRead(waterLevelPin);

    Serial.print("Tinggi Air: ");
    Serial.println(waterLevel);

    if (waterLevel > thresholdWaterLevel) {
      Serial.println("Banjir terdeteksi!");
    } else {
      Serial.println("Tidak Ada Banjir");
    }

    delay(delayInterval);  // Jeda sebelum membaca ulang
  }
}
