int sLedMode[2] = {sLED_OFF, sLED_OFF};
int sLedPins[2] = {GREEN_LED, RED_LED};
bool sLedStatus[2] = {false, false};
long sLedLastblinktime = 0;

void sLedSet(int kind, int level){
  digitalWrite(kind, level);
}

void sLedModeSet(int kind, int mode){
  if (kind == GREEN_LED){
    sLedMode[0] = mode;
  } else {
    sLedMode[1] = mode;
  }
  sLedUpdate();
}

void sLedUpdate() {
  for (int i = 0; i < 2; i++){
    if (sLedMode[i] == sLED_BLINK && millis() - sLedLastblinktime > sLED_BLINKDURATION){
      sLedStatus[i] = !sLedStatus[i];
      sLedLastblinktime = millis();
    } else if (sLedMode[i] == sLED_ON) {
      sLedStatus[i] = true;
    } else if (sLedMode[i] == sLED_OFF){
      sLedStatus[i] = false;
    }
    if (sLedStatus[i]){
      sLedSet(sLedPins[i], LOW);
    } else {
      sLedSet(sLedPins[i], HIGH);
    }
  }
}
