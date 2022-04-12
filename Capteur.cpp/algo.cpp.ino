



int PresstoAngle(float pression){
  long pre = (long)pression;

  long min = 97000;
  long max = 103000;
  int angle = 0;

  long pression_tar = (pre - min)/100;
  Serial.print("lala");
  Serial.println(pression_tar);
  
  if (pression_tar <=0){
    angle =0;
  }
  else if (pression_tar >= 60){
    angle = 360;
  }
  else{
    angle = 6*pression_tar;  
  }
  return angle;
  
  
};
