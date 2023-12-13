// 아두이노 Firebase 라이브러리
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


#define DHTPIN D4
#define DHTTYPE DHT11

#include <DHT.h>
DHT dht(DHTPIN, DHTTYPE);

// 데이터 베이스 호스트 이름
#define FIREBASE_HOST "fir-led-control-e94e3-default-rtdb.firebaseio.com"
// 데이터 베이스 비밀번호
#define FIREBASE_AUTH "tHMCe691rQuiqJXfPY5CqixSVIE1JrLzNd0sIAih"
// Wi-Fi 설정
const char* SSID = "chang2";
const char* PASSWORD = "chchchch";



void setup() {
  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(SSID, PASSWORD);
  dht.begin(9600);
  
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
 
void loop() {
float temp = dht.readTemperature();
float humi = dht.readHumidity();
Firebase.pushFloat("temperature"
, temp); 
Firebase.pushFloat("humidity"
, humi); 
if (Firebase.failed()) {
Serial.print("pushing /logs failed:");
Serial.println(Firebase.error()); 
return;
}
Serial.print("pushed: /logDHT/");
delay(5000);
}

