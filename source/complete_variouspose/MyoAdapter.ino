String altPosttoString(int pose){
  if (pose >= 5){return "ILLEGAL POSE";}
  return bridge.poseToString(pose);
}

void printMyoInfo(){
  Serial1.println("------MYO INFO");
  Serial1.print("Firmware Version: ");
  Serial1.print(bridge.getFirmwareMajor());
  Serial1.print(".");
  Serial1.print(bridge.getFirmwareMinor());
  Serial1.print(".");
  Serial1.println(bridge.getFirmwarePatch());
  Serial1.print("Hardware Revision: ");
  Serial1.println(bridge.getHardwareRevision());
  byte address[6];
  bridge.getHardwareAddress(address);
  Serial1.print("Hardware Address: 0x");
  for (int i=0;i<6;i++) {
    Serial1.print(address[i], HEX);
  }
  Serial1.println();
  MyoPose unlockPose;
  unlockPose = bridge.getUnlockPose();
  Serial1.print("Unlock Pose: ");
  Serial1.println(bridge.poseToString(unlockPose));
  byte batteryLevel = bridge.getBatteryLevel();
  Serial1.print("Battery Level: ");
  Serial1.println(batteryLevel);
  Serial1.println("------------------");
}
