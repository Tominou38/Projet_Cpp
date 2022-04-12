 
#include <Adafruit_BMP085.h>
using namespace std; 
Adafruit_BMP085 bmp;
#include <Wire.h>
#include "rgb_lcd.h"
#include <Servo.h>

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
const int colorR = 135;
const int colorG = 143;
const int colorB = 255;

   //-------------------------------
   // DES CLASSES CAPTEUR 
   //-------------------------------

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

class Affichage {
   protected : 
    String nom; 
  public :
    Affichage();
    Affichage(String n){
      nom=n;
    }
};

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
   // INITIALISATION OBJETS 
   //-------------------------------

BHP Pression;
LCD Ecran;
Servomoteur Servo1;
Servomoteur Servo2;
DHTCapt Humidity;



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
   lcd.print("Il fait : ");
   lcd.setCursor(9, 1);
   lcd.print("degre C");
  
   //-------------------------------
   // INITIALISATION Servo
   //-------------------------------
   myservo.attach(servoPin);
   myservo2.attach(servoPin2);

   dht.begin();

   Servo1.setAngle(0);
}

void loop(){
  angle=190;
  Pression.setPress();
  Pression.setTemp();
  angle = PresstoAngle(Pression.getPress());
  Serial.println("Angle :"+String(angle));
  Ecran.setTemp(Pression.getTemp());
  Serial.println(Pression.getPress());


  Servo1.setAngle(angle);

  Humidity.setHumidity();
  Humidity.setTemp();
  Serial.println("Temperature = " + String(Humidity.getTemp())+" °C");
  Serial.println("Humidite = " + String(Humidity.getHumidity())+" %");
  TemptoAngle(Pression.getTemp());
  
  delay(1000);

}
