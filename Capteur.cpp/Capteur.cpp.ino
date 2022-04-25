#include <ArduinoSTL.h>
#include <iostream>
 
#include <Adafruit_BMP085.h>
using namespace std; 
Adafruit_BMP085 bmp;
#include <Wire.h>
#include "rgb_lcd.h"
#include <Servo.h>
#include <list>

// Create a new servo object:
Servo myservo;
Servo myservo2;
// Define the servo pin:
#define servoPin 2
#define servoPin2 3
// Create a variable to store the servo position:
int angle = 0;

#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);



rgb_lcd lcd;
const int colorR = 255;
const int colorG = 194;
const int colorB = 0;

   //-------------------------------
   // DES CLASSES CAPTEUR 
   //-------------------------------


// CLASSE MERE 
class capteur {
  protected : 
    String nom; 
  public :
    capteur();
    capteur(String n){
      nom=n;
    }
};
// CLASSES FILLES 
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

class DHTCapt : public capteur{
  protected : 
    float Temp;
    float Hum;
  public :
    DHTCapt():capteur("humidite"){};
    DHTCapt(float T, float H):capteur("humidite"){
      Temp=T;
      Hum=H;
    }

    void setHumidity(){
      Hum=dht.readHumidity(); 
    }

    float getHumidity(){
      return Hum; 
    }

    void setTemp(){
      Temp=dht.readTemperature(); 
    }

    float getTemp(){
      return Temp; 
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

   //-------------------------------
   // INITIALISATION DES CLASSES AFFICHAGE 
   //-------------------------------
//CLASSE MERE 
class Affichage {
   protected : 
    String nom; 
  public :
    Affichage();
    Affichage(String n){
      nom=n;
    }
};

//CLASSE FILLE 
class LCD : public Affichage{
  protected :
    String Message;
  public : 
    LCD():Affichage("ecran"){};
    LCD(String m):Affichage("ecran"){
      Message=m;
    }

    void setTemp(float m){
      lcd.setCursor(0, 1);
      Message=(String)m;
      lcd.print(m); 
    }

};

class Servomoteur : public Affichage{
  protected :
    float angle;
  public : 
    Servomoteur():Affichage("ecran"){};
    Servomoteur(float a):Affichage("ecran"){
      angle=a;
    }
    void setAngle(float a){
      angle=a;
      myservo.write(a);
    }
};


   //-------------------------------
   // CLASSE TEMPERATURE
   //-------------------------------

class Temperature {
  protected :
    float temp;
  public :
    
    Temperature(){};
    Temperature(float t){
      temp=t;
    };
    float getTemp(){
      return(temp);
    }
    void setTemp(float t){
      temp=t;
    }
    Temperature & operator +=(const Temperature & autre){
      temp += autre.temp;
      return(*this);
    }
};
String chaleur(int t){
  if (t >= 30){
    t=40;
    throw t ;
  }
} ;
   //-------------------------------
   // INITIALISATION OBJETS 
   //-------------------------------

BHP Pression;
LCD Ecran;
Temperature T1;
Temperature T2;
Temperature T3;
Servomoteur Servo1;
Servomoteur Servo2;
DHTCapt Humidity;


//LISTE//
int i;
list<int>listeTemp;
list<int>::iterator it;
float moyenne;

int v=0;



void setup(){
  Serial.begin(9600);

   //-------------------------------
   // INITIALISATION CAPTEUR TEMP
   //-------------------------------
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }

   //-------------------------------
   // INITIALISATION LCD
   //-------------------------------
   lcd.begin(16, 2);
   lcd.setRGB(colorR, colorG, colorB);
   
   //lcd.setCursor(9, 1);
   //lcd.print("degre C");
  
   //-------------------------------
   // INITIALISATION Servo
   //-------------------------------
   myservo.attach(servoPin);
   myservo2.attach(servoPin2);

   dht.begin();

   //liste 
   i = 0;
   listeTemp.push_back(Pression.getTemp());
  i+=1;
}


void loop(){
  angle=190;
  Pression.setPress();
  Pression.setTemp();
  angle = PresstoAngle(Pression.getPress());
  Serial.println("Angle :"+String(angle));
  
  T1.setTemp(Pression.getTemp());
  
  Serial.println(Pression.getPress());

  
  //Servo1.setAngle(angle);
  

  Humidity.setHumidity();
  Humidity.setTemp();
  T2.setTemp(Humidity.getTemp());
  T2+=T1;
  if (v==0) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Il fait : ");
    Ecran.setTemp(T2.getTemp()/2);
    lcd.setCursor(9, 1);
    lcd.print("degre C");
    v=1;
  }else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("et l'humidite est");
    Ecran.setTemp(Humidity.getHumidity());
    lcd.setCursor(6, 1);
    lcd.print("% ");
    v=0;
  }
  try {
    String n=chaleur(T2.getTemp()/2);
  }catch(String mess){
    lcd.setRGB(255, 0, 0);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TROP CHAUD");
    lcd.setCursor(0,2);
    lcd.print("PLUS DE 30DEG");
  }
  Serial.println("Temperature = " + String(Humidity.getTemp())+" °C");
  Serial.println("Humidite = " + String(Humidity.getHumidity())+" %");
  TemptoAngle(Pression.getTemp());


  //gestion temp moyenne
  listeTemp.push_back(Humidity.getTemp());
  it= listeTemp.begin();
  moyenne = 0.0;
  for(it = listeTemp.begin();it !=listeTemp.end(); it++){
    moyenne = moyenne + *it;
  }
   Serial.println("MOYENNE = " + String(moyenne)+" deg");
  moyenne = moyenne/float(i);
  i = i+1;
    Serial.println("MOYENNE = " + String(moyenne)+" deg");
  
  
  Servo1.setAngle(angle);
  delay(1000);

  

}
