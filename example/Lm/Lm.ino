#include <Servo.h>
Servo Lm1;

void LmSet(Servo *lm, float strokePercentage) {
  if ( strokePercentage >= 1.0 && strokePercentage <= 99.0 )
  {
    int usec = 1000 + strokePercentage * ( 2000 - 1000 ) / 100.0 ;
    lm -> writeMicroseconds( usec );
  }
}

float dp = 10, p = 1.0;
void setup() {
  Lm1.attach(9);
  Serial.begin(9600);
}

void loop() {
  p += dp;
  LmSet(&Lm1, p);
  if(p >= 99 || p <= 1) {
    dp = -dp;
    delay(2000);
  }
  delay(100);
}
