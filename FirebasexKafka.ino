#include <ESP8266HTTPClient.h>
#include <b64.h>
#include <HttpClient.h>
#include <HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
WiFiClient wifiClient;

#include "FirebaseESP8266.h"

String wifiSSID = "przival";
String wifiPassword = "rahasia123";

const int infrared1 = D3; //pin sensor infrared
const int infrared2 = D4;
const int infrared3 = D5;
const int infrared4 = D6;

//Deklarasi fungsi
void connectWifi();
void postHttp();
#define FIREBASE_HOST "nodemcudht11-14d34-default-rtdb.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "nxrTlBv5ETOgBCRhEBcnLcPBlKPfUEXmrXWgnpwc"

FirebaseData firebaseData;
FirebaseJson json;

void setup() {
  Serial.begin(9600);
  pinMode(infrared1, INPUT);
  pinMode(infrared2, INPUT);
  pinMode(infrared3, INPUT);
  pinMode(infrared4, INPUT);
  connectWifi();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {
  firebaseUpdate();
  delay(1000);
  postSensorID1();
  postSensorID2();
  postSensorID3();
  postSensorID4();
  delay(3000);
}

void connectWifi(){
  Serial.println("Connecting to WiFi");
  WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("Wifi Connected");
  Serial.println(WiFi.SSID());
  Serial.println(WiFi.RSSI());
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
}

void firebaseUpdate(){ // Pengiriman data sensor ke firebase
  String ir1, ir2, ir3, ir4 ;
  ir1 = digitalRead(infrared1);
  ir2 = digitalRead(infrared2);
  ir3 = digitalRead(infrared3);
  ir4 = digitalRead(infrared4);

  // kirim data slot parkir (1)
    if (Firebase.setString(firebaseData, "/IOT/slotparkir1", ir1))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  // kirim data slot parkir (2)

    if (Firebase.setString(firebaseData, "/IOT/slotparkir2", ir2))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  // kirim data slot parkir(3)

  if (Firebase.setString(firebaseData, "/IOT/slotparkir3", ir3))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  } 

  // kirim data slot parkir(4)

  if (Firebase.setString(firebaseData, "/IOT/slotparkir4", ir4))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  } 
}

void postSensorID1(){ // pengiriman data ke kafka
  String ir1; //deklarasi tipe variabel
  ir1 = digitalRead(infrared1);
  
  Serial.println("SENDING..");
  String url = "http://cluster.yacanet.com:8080/api/sensor"; //url kafka 
  HTTPClient http ;
  String response ;

  StaticJsonDocument<200> buff;
  String jsonParams ;
  buff["sensorId"]="1";
  
  if (ir1 == "1" ){
    buff["data"]= "{\"status\":\"0\"}"; 
  }
  else {
    buff["data"]= "{\"status\":\"1\"}"; 
  }
  serializeJson(buff, jsonParams);
  Serial.println(jsonParams);

  http.begin(wifiClient, url);
  http.addHeader("Content-Type", "application/json");
  http.POST(jsonParams); // METHOD POST 
  response = http.getString();
  Serial.println(response);
  Serial.println("------------------------------------");
  Serial.println();
}

void postSensorID2(){ // pengiriman data ke kafka
  String ir2; //deklarasi tipe variabel
  ir2 = digitalRead(infrared2);
  
  Serial.println("SENDING..");
  String url = "http://cluster.yacanet.com:8080/api/sensor"; //url kafka 
  HTTPClient http ;
  String response ;

  StaticJsonDocument<200> buff;
  String jsonParams ;
  buff["sensorId"]="2"; // sensor id 2
  
  if (ir2 == "1" ){
    buff["data"]= "{\"status\":\"0\"}"; 
  }
  else {
    buff["data"]= "{\"status\":\"1\"}"; 
  }

  serializeJson(buff, jsonParams);
  Serial.println(jsonParams);

  http.begin(wifiClient, url);
  http.addHeader("Content-Type", "application/json");
  http.POST(jsonParams); // METHOD POST 
  response = http.getString();
  Serial.println(response);
  Serial.println("------------------------------------");
  Serial.println();
}

void postSensorID3(){ // pengiriman data ke kafka
  String ir3; //deklarasi tipe variabel
  ir3 = digitalRead(infrared3);
  
  Serial.println("SENDING..");
  String url = "http://cluster.yacanet.com:8080/api/sensor"; //url kafka 
  HTTPClient http ;
  String response ;

  StaticJsonDocument<200> buff;
  String jsonParams ;
  buff["sensorId"]="3"; // sensor id 3

  if (ir3 == "1" ){
    buff["data"]= "{\"status\":\"0\"}"; 
  }
  else {
    buff["data"]= "{\"status\":\"1\"}"; 
  }
  
  serializeJson(buff, jsonParams);
  Serial.println(jsonParams);

  http.begin(wifiClient, url);
  http.addHeader("Content-Type", "application/json");
  http.POST(jsonParams); // METHOD POST 
  response = http.getString();
  Serial.println(response);
  Serial.println("------------------------------------");
  Serial.println();
}

void postSensorID4(){ // pengiriman data ke kafka
  String ir4; //deklarasi tipe variabel
  ir4 = digitalRead(infrared4);
  
  Serial.println("SENDING..");
  String url = "http://cluster.yacanet.com:8080/api/sensor"; //url kafka 
  HTTPClient http ;
  String response ;

  StaticJsonDocument<200> buff;
  String jsonParams ;
  
  buff["sensorId"]="4"; // sensor id 4
  if (ir4 == "1" ){
    buff["data"]= "{\"status\":\"0\"}"; 
  }
  else {
    buff["data"]= "{\"status\":\"1\"}"; 
  }

  serializeJson(buff, jsonParams);
  Serial.println(jsonParams);

  http.begin(wifiClient, url);
  http.addHeader("Content-Type", "application/json");
  http.POST(jsonParams); // METHOD POST 
  response = http.getString();
  Serial.println(response);
  Serial.println("------------------------------------");
  Serial.println();
}
