
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
    BHP():capteur("pression"){}; 
    BHP(float T, float P):capteur("pression"){
      Temp=T;
      Press=P;
    };

    void setPress(){
      Press=bmp.readPressure(); 
    }

    float getPress(){
      return Press; 
    }

    void setTemp(){
      Temp=bmp.readTemperature(); 
    }

    float getTemp(){
      return Temp; 
    }
};

class DHT : public capteur{
  protected : 
    float Temp;
    float Hum;
  public :
    DHT():capteur("humidite"){};
    DHT(float T, float H):capteur("humidite"){
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




BHP Pression;



void setup(){
  Serial.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }


  
  
  
  
  
}

void loop(){
 
  Pression.setPress();
  Serial.println(Pression.getPress());
  Pression.setTemp();
  Serial.println(Pression.getTemp());
}
