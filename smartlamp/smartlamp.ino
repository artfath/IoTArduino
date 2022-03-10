#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <FirebaseESP32.h>

/* Wifi SSID and password */
#define WIFI_SSID "YOUR WIFI SSID"
#define WIFI_PASSWORD "YOUR WIFI PASSWORD"

/* Firebase host and authkey */
#define FIREBASE_HOST "YOUR FIREBASE HOST"
#define FIREBASE_Authorization_key "YOUR AUTHKEY"

#define pwmPin 4
#define zeroCross 16

WiFiClientSecure secured_client;
FirebaseData fbdo;
hw_timer_t * timer = NULL;

int led1pin = 2;
int dimVal = 0;
int zcstate = 0;
int counter = 0;
int val = 0;

/* External interrupt function */
void IRAM_ATTR zcDetect() {

  zcstate = 1;  // For 60Hz =>65
  counter = 0;
  digitalWrite(pwmPin, LOW);
}

/* Timer interrupt function */
void IRAM_ATTR onTimer() {
  /* at 50Hz, every 1 cycle (0.02 s) is 2 interrupt, 1 interupt 10ms or 10000uS.
    dimming 1-100, every 1 counter is 100us */
  counter++;
  if ((zcstate == 1) && (counter == val)) {
    digitalWrite(pwmPin, HIGH);
    counter = 0;
    zcstate = 0;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  /* initialization GPIO */
  pinMode(led1pin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(zeroCross, INPUT);
  /* attach function when external interrupt triggered */
  attachInterrupt(zeroCross, zcDetect, RISING);
  /* connect internet with acces point */
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
  /* connect to realtime database in firebase */
  Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);
  Firebase.reconnectWiFi(true);
  /* Use 1st timer of 4 (counted from zero)*/
  /* to  make 1 tick = 1 us, set prescaler 80. 1/(80MHZ/80) = 1us */
  timer = timerBegin(0, 80, true);
  /* Attach onTimer function to our timer */
  timerAttachInterrupt(timer, &onTimer, true);
  /* 1 tick is 1 us, call on timer every 100us */
  /* Repeat the alarm (third parameter) */
  timerAlarmWrite(timer, 100, true);
  /* Start an alarm */
  timerAlarmEnable(timer);
}

void loop() {
  // currentTime=millis();

  /* Retrieve data from firebase */
  if (Firebase.getString(fbdo, "/data/switch")) {
    if (fbdo.stringData() == "on") {
      digitalWrite(led1pin, HIGH);
      if (Firebase.getString(fbdo, "/data/brightness")) {
        dimVal = fbdo.stringData().toInt();
        if (dimVal <= 100) {
          /* set dimmer value */
          val = map(dimVal, 0, 100, 100, 1);
        }
      }
    } else {
      digitalWrite(led1pin, LOW);
      val = 100;
    }
  }
  Serial.println(val);
  Serial.print("zc:");
  Serial.println(zcstate);
  Serial.print("counter:");
  Serial.println(counter);
}
