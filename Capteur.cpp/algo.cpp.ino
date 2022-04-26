//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------

//   PROJET DE C++, Tom JULLIEN & Thomas Boursac 

//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------

/* 
 Fichier de calcul de l'angle du servo moteur en tenant compte de la pression atmosphérique 
 */


int PresstoAngle(float pression){
  long pre = (long)pression;

  long min = 97000;
  long max = 103000;
  int angle = 0;

  long pression_tar = (pre - min)/100;

  
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

int TemptoAngle(float temp){
  float ajust = temp*100.0;
  Serial.println("LOG");
  Serial.println(ajust);
  long tem = (long)ajust;
  Serial.println(tem);
  long min = -2000;
  long max = 4000;
  int angle = 0;

  

  
  if (tem <=-2000){
    angle =0;
  }
  else if (tem >= 4000){
    angle = 180;
  }
  else{
    angle = 0.06*((float)tem+2000);  
    
  }
  Serial.println(angle);
  Serial.println(angle/2);
  return angle/2;
  
  
};
