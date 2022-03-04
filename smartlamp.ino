#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <FirebaseESP32.h>
#include <RBDdimmer.h>


#define WIFI_SSID "your ssid"
#define WIFI_PASSWORD "your password"

#define FIREBASE_HOST "your realtime database url"
#define FIREBASE_Authorization_key "your authorization key"
//26(GPIO4)
//27(GPIO16)

#define outputPin  26 

#define zerocross  27 

WiFiClientSecure secured_client;
FirebaseData fbdo;

dimmerLamp dimmer(outputPin,zerocross);

int led1pin=2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  pinMode(led1pin, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);
  Firebase.reconnectWiFi(true);
  dimmer.begin(NORMAL_MODE, ON);

}

//void loop() {
//  // put your main code here, to run repeatedly:
//  Firebase.getString(fbdo,"/data/switch");
//  if(fbdo.stringData()=="on"){
//    digitalWrite(led1pin, HIGH);
//    
//   }else{
//    digitalWrite(led1pin, LOW);}
//    Serial.println(fbdo.stringData());
//  
//
//}
void loop() {
  // put your main code here, to run repeatedly:
  if(Firebase.getString(fbdo,"/data/switch")){
    if(fbdo.stringData()=="on"){
    digitalWrite(led1pin, HIGH);
    if(Firebase.getString(fbdo,"/data/brightness")){
  
  int dimVal=fbdo.stringData().toInt();

  if(dimVal<=100){
    dimmer.setPower(dimVal);
    Serial.println(dimVal);
  }
  
  }
    
   }else{
    digitalWrite(led1pin, LOW);}
    Serial.println(fbdo.stringData());
  }

  
  

}
