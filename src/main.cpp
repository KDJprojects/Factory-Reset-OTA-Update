#include <Arduino.h>
#include <HTTPUpdate.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "esp_https_ota.h"
#include <esp_partition.h>

#define NEW_FIRMWARE_URL "https://raw.githubusercontent.com/KDJprojects/OTA_WebUpdate_V0.1/main/src/firmware.bin"
#define SSID "Dlink"
#define PASSWORD ""

void Connect_To_Wifi(void){
  Serial.print("Connecting to WiFi");
  WiFi.begin(SSID, PASSWORD);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi Connected Sucessfully!");
}

void Update_Firmware(void){
  Serial.println("Attempting to update this device to the latest version...");
  HTTPUpdate Update;
  WiFiClientSecure client;
  client.setInsecure();
  t_httpUpdate_return ret = Update.update(client, NEW_FIRMWARE_URL);

  //t_httpUpdate_return ret = httpUpdate.update(client, NEW_FIRMWARE_URL);
  switch(ret){
    case HTTP_UPDATE_FAILED:
      Serial.println("Update Failed");
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("No Updates");
      break;
    case HTTP_UPDATE_OK:
      Serial.println("Update OK");
      break;
    break;
  }
}

void Find_Factory_Partition(void){
esp_partition_iterator_t pi = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_FACTORY, NULL);
  if (pi != NULL){
    Serial.print("Factory Partition has been found.");
  }
  if (pi == NULL){
    Serial.println("No factory partition found.");
  }
}

void setup() {
Serial.begin(115200);
delay(100);
Serial.println("Running New OTA Firmware, V0.2");
Find_Factory_Partition();
}

void loop() {
  
}