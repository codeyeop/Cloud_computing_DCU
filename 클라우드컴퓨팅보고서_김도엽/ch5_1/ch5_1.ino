#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define FIREBASE_HOST "fir-led-control-e94e3-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "tHMCe691rQuiqJXfPY5CqixSVIE1JrLzNd0sIAih"
const char* SSID = "chang2";
const char* PASSWORD = "chchchch";

void setup() {
  Serial.begin(9600);
  WiFi.begin(SSID, PASSWORD);
  dht.begin();

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
 
void loop() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Humidity = ");
  Serial.println(humi);
  
  // 온도를 Firebase에 저장 ("/temperature" 경로에 추가)
  Firebase.pushFloat("/temperature", temp);

  // 습도를 Firebase에 저장 ("/humidity" 경로에 추가)
  Firebase.pushFloat("/humidity", humi);

  // 오류 처리
  if (Firebase.failed()) {
    Serial.print("Failed to update Firebase:");
    Serial.println(Firebase.error());
  } else {
    Serial.println("Data sent successfully!");
  }
  
  delay(5000);
}