// 아두이노 Firebase 라이브러리
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// 데이터 베이스 호스트 이름
#define FIREBASE_HOST "fir-led-control-e94e3-default-rtdb.firebaseio.com"
// 데이터 베이스 비밀번호
#define FIREBASE_AUTH "tHMCe691rQuiqJXfPY5CqixSVIE1JrLzNd0sIAih"
// Wi-Fi 설정
const char* SSID = "chang2";
const char* PASSWORD = "chchchch";

String red_fireStatus = "";               //firebase DB로 부터 받은 값 저장
String blue_fireStatus ="";
 int red_led = D3;  // NodeMCU LED pin
int blue_led = D4;

void setup() 
{
  Serial.begin(9600);
  delay(1000);    
  pinMode(red_led, OUTPUT);  
  pinMode(blue_led, OUTPUT);
                 
  WiFi.begin(SSID, PASSWORD);                               
  Serial.print("Connecting to ");
  Serial.print(SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // connect to firebase
  Firebase.setString("RED_LED_STATUS", "OFF"); //send initial string of led status
  Firebase.setString("BLUE_LED_STATUS", "OFF");
}
 
void loop() 
{
  red_fireStatus = Firebase.getString("RED_LED_STATUS");     // get ld status input from firebase
  if (red_fireStatus == "ON")   { // compare the input of led status received from firebase
    Serial.println("RED LED Turned ON");                                                        
    digitalWrite(red_led, HIGH);          // make external led ON
  } 
  else if (red_fireStatus == "OFF") {    // compare the input of led status received from firebase
    Serial.println("RED LED Turned OFF");
    digitalWrite(red_led, LOW);      // make external led OFF
  } else {
    Serial.println("Command Error! Please send ON/OFF");
  }

  delay(2000);

  blue_fireStatus = Firebase.getString("BLUE_LED_STATUS");     // get ld status input from firebase
  if (blue_fireStatus == "ON")   { // compare the input of led status received from firebase
    Serial.println("BLUE LED Turned ON");                                                        
    digitalWrite(blue_led, HIGH);          // make external led ON
  } 
  else if (blue_fireStatus == "OFF") {    // compare the input of led status received from firebase
    Serial.println("BlUE LED Turned OFF");
    digitalWrite(blue_led, LOW);      // make external led OFF
  } else {
    Serial.println("Command Error! Please send ON/OFF");
  }

  delay(2000);
}