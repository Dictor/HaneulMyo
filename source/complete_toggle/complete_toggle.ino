#include <SoftReset.h>
#include <MyoBridge.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define HM_RST_PIN A4
#define HM_RETRY_TIME 30000

#define LM_COUNT 5
#define LM_POSE_COUNT 4
#define LM_POSE_RELEASE 0
#define LM_POSE_GRAB 1
#define LM_POSE_GOOD 2
#define LM_POSE_OK 3

#define GREEN_LED 5
#define RED_LED 6
#define sLED_BLINKDURATION 700
#define sLED_OFF 0
#define sLED_ON 1
#define sLED_BLINK 2

SoftwareSerial bridgeSerial(SCK, MISO);
MyoBridge bridge(bridgeSerial);
bool isfirstpc = false;
long myostarttime = 0;

void connCallback(MyoConnectionStatus status) {
  Serial1.print("CONN STATUS : ");
  String connmsg = bridge.connectionStatusToString(status);
  Serial1.println(connmsg);
  if (connmsg == "CONN_STATUS_LOST"){
    Serial1.println("MYO CONNECTION LOST! DEVICE WILL RESET");
    soft_restart();
  } else if (connmsg == "CONN_STATUS_INIT" || connmsg == "CONN_STATUS_SCANNING"){
    if (millis() - myostarttime > HM_RETRY_TIME){
      Serial1.println("MYO NOT RESPONSE!");
      HMreset();
      myostarttime = millis();
    }
  }
}

void poseCallback(MyoPoseData& data) {
  MyoPose pose;
  pose = (MyoPose)data.pose;
  if (isfirstpc == false){
    isfirstpc = true;
    sLedModeSet(RED_LED, sLED_OFF);
    sLedModeSet(GREEN_LED, sLED_BLINK);
  }
  Serial1.print("POSE : ");
  Serial1.println(altPosttoString(pose));
  switch(pose){
    case 0: //MYO_POSE_REST
      break;
    case 1: //MYO_POSE_FIST
      LmPoseSet(LM_POSE_GRAB);
      break;
    case 2: //MYO_POSE_WAVE_IN
      LmPoseSet(LM_POSE_OK);
      break;
    case 3: //MYO_POSE_WAVE_OUT
      LmPoseSet(LM_POSE_GOOD);
      break;
    case 4: //MYO_POSE_FINGERS_SPREAD
      LmPoseSet(LM_POSE_RELEASE);
      break;
  }
}

void HMreset(){
  Serial1.println("HM RESET ACTIVATED");
  digitalWrite(HM_RST_PIN, LOW);
  delay(200);
  digitalWrite(HM_RST_PIN, HIGH);
}

void setup() {
  Serial1.begin(115200);
  bridgeSerial.begin(115200);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(HM_RST_PIN, OUTPUT);
  digitalWrite(HM_RST_PIN, HIGH);
  sLedModeSet(RED_LED, sLED_OFF);
  sLedModeSet(GREEN_LED, sLED_OFF);
  HMreset();
  LmInit();
  Serial1.println("INIT COMPLETE");
  Serial1.println("SEARCHING START");
  sLedModeSet(RED_LED, sLED_ON);
  LmPoseSet(LM_POSE_RELEASE);
  myostarttime = millis();
  bridge.begin(connCallback);
  Serial1.println("CONNECTED");
  sLedModeSet(RED_LED, sLED_OFF);
  sLedModeSet(RED_LED, sLED_BLINK);
  printMyoInfo();
  bridge.setPoseEventCallBack(poseCallback);
  bridge.enablePoseData();
  bridge.unlockMyo();
}

void loop() {
  bridge.update();
  sLedUpdate();
  if (millis() % 30000 == 0){
    if (bridge.getBatteryLevel() <= 20){
       Serial1.println("MYO BATTERY LOW!");
       sLedModeSet(GREEN_LED, sLED_ON);
    } else {
       sLedModeSet(GREEN_LED, sLED_BLINK);
    }
  }
}
