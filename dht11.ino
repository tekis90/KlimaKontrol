
#include <dht11.h>
#define DHT11PIN D1
#define role D2

#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"



#define FIREBASE_HOST "***************" 
#define FIREBASE_AUTH "************"
#define WIFI_SSID "***********"
#define WIFI_PASSWORD "*********"
String gelen;


FirebaseData Data;

dht11 DHT11;

void DHT11_Okuma()
{
  Serial.println("\n");
  int chk = DHT11.read(DHT11PIN);


}


void setup()
{
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Ağ Bağlantısı Oluşturuluyor");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP adresine bağlanıldı: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  
  Firebase.reconnectWiFi(true);
  pinMode(role, OUTPUT);
  digitalWrite(role, LOW);



}

void loop()
{

  DHT11_Okuma();

  Firebase.setDouble(Data, "deger", (float)DHT11.temperature);
  delay(50);
  //Firebase.getString(Data, "/kontrol");
  Serial.println(gelen);


  if (Firebase.getString(Data, "/kontrol")) 
  {
    
    if (Data.stringData() == "1") {
      digitalWrite(role, HIGH);
      Serial.println("Klima Açık");
    }
    else {
      digitalWrite(role, LOW);
      Serial.println("Klima Kapalı");

    }



  }





}
