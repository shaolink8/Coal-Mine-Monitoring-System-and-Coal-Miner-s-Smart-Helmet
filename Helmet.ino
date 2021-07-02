#include <LiquidCrystal.h>

LiquidCrystal lcdbs(12, 11, 5, 4, 3, 2);

int laserPin = 7;
int Led = 13 ;      // Define LED Interface
int buttonpin = 4; // Define the obstacle avoidance sensor interface
int val ;         // Define numeric variable val
int sensorPin = 0;
double alpha = 0.75;
int period = 100;
double change = 0.0;
double minval = 0.0;
int LedOutput = 12;      // Define as LED Output pin 12
int lbsp = 8;           // Define as sensor pin input
int Valuelbsp;         // Define as variable 


void setup (){

  pinMode (laserPin, OUTPUT); 

  lcdbs.begin(16, 2);

  pinMode (Led, OUTPUT) ;       // Define LED as output interface
  pinMode (buttonpin, INPUT) ; 

  Serial.begin (9600);

  pinMode(LedOutput,OUTPUT); 
  pinMode(lbsp,INPUT);      

}

void loop (){

  val = digitalRead (buttonpin); 

  if (val == HIGH){ // When the obstacle avoidance sensor detects a signal, LED flashes

  digitalWrite (Led, LOW);

  Serial.println("OFF");

}

  else{

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


  Valuelbsp=digitalRead(lbsp);  // Set as sensor read SensorPin 

  if(Valuelbsp==HIGH){          // If value is equal to HIGH state then change LED output to HIGH

  digitalWrite(LedOutput,HIGH); // Set LedOutput to HIGH or ON

  Serial.println("Huaah!");

}

  else{

  digitalWrite(LedOutput,LOW); // Set LedOutput to LOW or OFF

  Serial.println("No light");

}

  int valbs;
  valbs=analogRead(5);  

  Serial.print("Sound: ");
  Serial.println(valbs,DEC); // Print the sound value to serial monitor        

  lcdbs.setCursor(0, 0);
  lcdbs.print("Sound: ");
  lcdbs.print(valbs);
  lcdbs.print("   ");

  digitalWrite (laserPin, HIGH);      // Turn laser on

  delay (1000);                     // On for half a second

  digitalWrite (laserPin, LOW);   // Turn laser off

  delay (500);                  // Off for half a second

}

