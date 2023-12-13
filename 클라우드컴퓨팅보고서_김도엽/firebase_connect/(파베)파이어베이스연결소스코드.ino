// 아두이노 Firebase 라이브러리
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// 데이터 베이스 호스트 이름
#define FIREBASE_HOST "fir-led-control-e94e3-default-rtdb.firebaseio.com"
// 데이터 베이스 비밀번호
#define FIREBASE_AUTH "tHMCe691rQuiqJXfPY5CqixSVIE1JrLzNd0sIAih"
// Wi-Fi 설정
const char* SSID ="chang2";
const char* PASSWORD ="chchchch";

String fireStatus = ""; //firebase DB로 부터 받은 값 저장
int led = D4; // NodeMCU LED pin

void setup() 
{
Serial.begin(9600);
delay(1000);
pinMode(led, OUTPUT);
WiFi.begin(SSID, PASSWORD); 
Serial.print("Connecting to ");
Serial.print(SSID);

while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println();
Serial.print("WiFi Connected to ");
Serial.println(WiFi.localIP());

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // firebase에 연결
Firebase.setString("ledStatus", "OFF");
}

void loop() 
{
  fireStatus = Firebase.getString("ledStatus");

  if(fireStatus == "ON"){
    Serial.println("LED Turned ON");
    digitalWrite(led, HIGH);
  }
  else if(fireStatus =="OFF"){
    Serial.println("Led Turned OFF");
    digitalWrite(led, LOW);
  } 
  else {
    Serial.println("Command Error! Please send ON/OFF");
  }
  

}
