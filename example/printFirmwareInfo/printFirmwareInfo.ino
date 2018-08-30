/**
 * @file   printFirmwareInfo.ino
 * @author Valentin Roland (webmaster at vroland.de)
 * @date   September-October 2015
 * @brief  Example file demonstrating connecting to and reading data from the Myo.
 *
 * This file is part of the MyoBridge Project. For more information, visit https://github.com/vroland/MyoBridge.
 *
 * @include printFirmwareInfo.ino
 */

#include <MyoBridge.h>
#include <SoftwareSerial.h>

//SoftwareSerial connection to MyoBridge
SoftwareSerial bridgeSerial(SCK, MISO);

//initialize MyoBridge object with software serial connection
MyoBridge bridge(bridgeSerial);

//a function to inform us about the current state and the progess of the connection to the Myo.
void printConnectionStatus(MyoConnectionStatus status) {
	
	//print the status constant as string
	Serial.println(bridge.connectionStatusToString(status));
}

void setup() {
  //initialize both serial connections
  Serial1.begin(115200);
  bridgeSerial.begin(115200);
  //wait until MyoBridge has found Myo and is connected. Make sure Myo is not connected to anything else and not in standby!
  Serial1.println("Searching for Myo...");
  
  //initiate the connection with the status callback function
  bridge.begin(printConnectionStatus);
  
  Serial1.println("connected!");

  Serial1.print("Firmware Version: ");
  Serial1.print(bridge.getFirmwareMajor());
  Serial1.print(".");
  Serial1.print(bridge.getFirmwareMinor());
  Serial1.print(".");
  Serial1.println(bridge.getFirmwarePatch());
  Serial1.print("Hardware Revision: ");
  Serial1.println(bridge.getHardwareRevision());

  //declare a storage array for the hardware address
  byte address[6];

  //get the address and store it in our array
  bridge.getHardwareAddress(address);

  //print the hardware address in HEX format
  Serial1.print("Hardware Address: 0x");
  for (int i=0;i<6;i++) {
    Serial1.print(address[i], HEX);
  }
  Serial1.println();

  //get the unlock pose
  MyoPose unlockPose;
  unlockPose = bridge.getUnlockPose();

  //print the name of the unlock pose as string
  Serial1.print("Unlock Pose: ");
  Serial1.println(bridge.poseToString(unlockPose));
  
  //get the current battery level and print it
  byte batteryLevel = bridge.getBatteryLevel();
  Serial1.print("Battery Level: ");
  Serial1.println(batteryLevel);
  
  //short vibration to show we are ready
  bridge.vibrate(1);
}

void loop() {
  //update the connection to MyoBridge
  bridge.update();
}
