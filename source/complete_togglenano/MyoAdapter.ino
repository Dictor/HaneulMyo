String altPosttoString(int pose){
  if (pose >= 5){return "ILLEGAL POSE";}
  return bridge.poseToString(pose);
}

void printMyoInfo(){
  Serial.println("------MYO INFO");
  Serial.print("Firmware Version: ");
  Serial.print(bridge.getFirmwareMajor());
  Serial.print(".");
  Serial.print(bridge.getFirmwareMinor());
  Serial.print(".");
  Serial.println(bridge.getFirmwarePatch());
  Serial.print("Hardware Revision: ");
  Serial.println(bridge.getHardwareRevision());
  byte address[6];
  bridge.getHardwareAddress(address);
  Serial.print("Hardware Address: 0x");
  for (int i=0;i<6;i++) {
    Serial.print(address[i], HEX);
  }
  Serial.println();
  MyoPose unlockPose;
  unlockPose = bridge.getUnlockPose();
  Serial.print("Unlock Pose: ");
  Serial.println(bridge.poseToString(unlockPose));
  byte batteryLevel = bridge.getBatteryLevel();
  Serial.print("Battery Level: ");
  Serial.println(batteryLevel);
  Serial.println("------------------");
}
