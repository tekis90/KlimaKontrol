
#include <dht11.h>
#define DHT11PIN D1
#define role D2

#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"


//1. Firebase veritabanı adresini, Token bilgisini ve ağ adresi bilgilerinizi giriniz.
#define FIREBASE_HOST "dht11klimakontrol-default-rtdb.firebaseio.com" // http:// veya https:// olmadan yazın
#define FIREBASE_AUTH "aYkxqLkDUHPF5aXkP6eQO7tf3IVe7aFIZ6huetoh"
#define WIFI_SSID "TEKIS"
#define WIFI_PASSWORD "Tekis2022Mestan"
String gelen;


//2. veritabanim adında bir firebase veritabanı nesnesi oluşturuyoruz
FirebaseData Data;

dht11 DHT11;

void DHT11_Okuma()
{
  Serial.println("\n");
  int chk = DHT11.read(DHT11PIN);
  /*
    Serial.print("Nem (%): ");
    Serial.println((float)DHT11.humidity, 2);

    Serial.print("Sicaklik (Celcius): ");
    Serial.println((float)DHT11.temperature, 2);

    delay(2000);*/

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


  //3. Firebase bağlantısı başlatılıyor

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //4. Ağ bağlantısı kesilirse tekrar bağlanmasına izin veriyoruz
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


  if (Firebase.getString(Data, "/kontrol")) //Alınacak veri tipine göre getInt, getBool, getFloat, getDouble, getString olarak kullanılabilir.
  {
    //bağlantı başarılı ve veri geliyor ise
    //Serial.print("String tipinde veri alımı başarılı, veri = ");
    //Serial.println(veritabanim.stringData());
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
