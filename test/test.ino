#include <math.h>

int a;

float temperature;

int B=3975;                  //B value of the thermistor

float resistance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(5, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*digitalWrite(LED_BUILTIN, LOW);   
  delay(1000);                      
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(2000);*/  
  a=analogRead(A0);
  resistance=(float)(1023-a)*10000/a; //get the resistance of the sensor;
  temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;//convert to temperature via datasheet&nbsp;;
  delay(100);
  Serial.print("Current temperature is ");
  Serial.println(temperature);
  
  
}
