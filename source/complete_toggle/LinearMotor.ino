int Lmpins[LM_COUNT] = {7, 8, 9, 10, 11};
Servo* Lms[LM_COUNT];
String posestr[LM_POSE_COUNT] = {"LM_POSE_RELEASE", "LM_POSE_GRAB", "LM_POSE_GOOD", "LM_POSE_OK"};
int LmPoseData[LM_POSE_COUNT][LM_COUNT] = {{1, 1, 1, 1, 1},
                                           {99, 99, 99, 99, 99},
                                           {99, 99, 99, 99, 1},
                                           {1, 1, 1, 70, 70}};

void LmInit(){
  for (int i = 0; i < LM_COUNT; i++){
    Lms[i] = (Servo*)malloc(sizeof(Servo));
    Lms[i] = new Servo();
    Lms[i] -> attach(Lmpins[i]);
  }
}

void LmSet(Servo *lm, float strokePercentage) {
  if ( strokePercentage >= 1.0 && strokePercentage <= 99.0 )
  {
    int usec = 1000 + strokePercentage * ( 2000 - 1000 ) / 100.0 ;
    lm -> writeMicroseconds( usec );
  }
}

void LmPoseSet(int pose){
  Serial1.print("LM POSE SET : ");
  Serial1.println(LmPoseToString(pose));
  for (int i = 0; i < LM_COUNT; i++){
    LmSet(Lms[i], LmPoseData[pose][i]);
  }
}

String LmPoseToString(int pose){
  if (pose >= LM_POSE_COUNT) {return "ERROR";}
  return posestr[pose];
}

