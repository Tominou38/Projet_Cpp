
#include <Adafruit_BMP085.h>
using namespace std; 
Adafruit_BMP085 bmp;


class capteur {
  protected : 
    String nom; 
  public :
    capteur();
    capteur(String n){
      nom=n;
    }
};

class BHP: public capteur {
  protected : 
    float Temp;
    float Press; 
  public : 
    BHP(); 
    BHP(float T, float P){
      Temp=T;
      Press=P;
    }
};

class DHT : public capteur{
  protected : 
    float Temp;
    float Hum;
  public :
    DHT();
    DHT(float T, float H){
      Temp=T;
      Hum=H;
    }
};

class CaptCO2 : public capteur{
  protected : 
    float CO2;
  public :
    CaptCO2();
    CaptCO2(float C){
      CO2=C;
    }
};








void setup(){
  Serial.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }

  
  
  
}

void loop(){
  
}
