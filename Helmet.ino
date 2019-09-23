#include <LiquidCrystal.h>
LiquidCrystal lcdbs(12, 11, 5, 4, 3, 2);
int laserPin = 7;
int Led = 13 ;// define LED Interface
int buttonpin = 4; // define the obstacle avoidance sensor interface
int val ;// define numeric variables val
int sensorPin = 0;
double alpha = 0.75;
int period = 100;
double change = 0.0;
double minval = 0.0;
int LedOutput = 12;// Define as LED Output Pin 12 you can change this to 13 if you dont use pin 12 as output indicator
int lbsp = 8; // Define as Sensor Pin Input
int Valuelbsp;// Define as variable 


void setup ()
{
   pinMode (laserPin, OUTPUT); // define the digital output interface 13 feet
  lcdbs.begin(16, 2);
  pinMode (Led, OUTPUT) ;// define LED as output interface
  pinMode (buttonpin, INPUT) ;// define the obstacle avoidance sensor output interface
   Serial.begin (9600);
   pinMode(LedOutput,OUTPUT);//Set as LedOutput
pinMode(lbsp,INPUT);//Set as photo interrupter sensor output interface
}
void loop ()
{
  val = digitalRead (buttonpin) ;// digital interface will be assigned a value of 3 to read val
  if (val == HIGH) // When the obstacle avoidance sensor detects a signal, LED flashes
  {
    digitalWrite (Led, LOW);
    Serial.println("OFF");
  }
  else
  {
    digitalWrite (Led, HIGH);
    Serial.println("ON");
  }
   static double oldValue = 0;
    static double oldChange = 0;
 
    int rawValue = analogRead (sensorPin);
    double value = alpha * oldValue + (1 - alpha) * rawValue;
 
    Serial.print (rawValue);
    Serial.print (",");
    Serial.println (value);
    oldValue = value;

    Valuelbsp=digitalRead(lbsp);// Set as sensor read SensorPin 
if(Valuelbsp==HIGH) //If value is equal to HIGH estate then turn LED output = high
{
digitalWrite(LedOutput,HIGH); // Set LedOutPut to HIGH or ON
Serial.println("Huaah!");
}
else
{
digitalWrite(LedOutput,LOW); // Set LedOutPut to LOW or OFF
Serial.println("No Light");
}
 int valbs;
      valbs=analogRead(5);   //connect mic sensor to Analog 0
      Serial.print("Sound=");
      Serial.println(valbs,DEC);//print the sound value to serial        
      lcdbs.setCursor(0, 0);
lcdbs.print("Sound=");
lcdbs.print(valbs);
lcdbs.print("   ");
digitalWrite (laserPin, HIGH); // Turn Laser On
   delay (1000); // On For Half a Second
   digitalWrite (laserPin, LOW); // Turn Laser Off
   delay (500); // Off for half a second
}
