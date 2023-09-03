#include <Arduino.h>
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <SPI.h>

WebSocketsClient weClient;

const char* ssid = "ADMIN_2g"; //Enter SSID
const char* password = "4635410009"; //Enter Password
String ws_server = "192.168.1.33"; // Replace with your server address
int serverPort = 3333;
bool ws_connected = false;
long intervel = millis();

void setup() {
  Serial.begin(115200);

  WiFi.disconnect(true);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  unsigned long currentMillis = millis();
  unsigned long previousMillis = currentMillis;
  Serial.printf("Connecting to %s ", ssid);

  while (WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = millis();
      Serial.println("Failed connecting " + String(ssid));
    }
  }
  Serial.print("IP ");
  Serial.println(WiFi.localIP());

  weClient.begin(ws_server, serverPort, "/");

  weClient.setReconnectInterval(5000);
  weClient.enableHeartbeat(15000, 3000, 2);
  
  // ตัวแปรเก็บไฟล์ json
  String jxon = "{\"type\":\"login\",\"username\":\"admin\",\"password\":\"1234\"}";
  
}

void loop() {
  weClient.loop();
  weClient.sendTXT("Hello from ESP32");
}
