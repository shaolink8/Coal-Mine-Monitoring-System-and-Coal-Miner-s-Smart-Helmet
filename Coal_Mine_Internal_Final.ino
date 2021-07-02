#include <dht.h>
#define SHOCK_PIN 5
dht DHT;

const int AOUTpin=5;   // The AOUT pin of the CO Sensor goes into Analog Pin D5 of the Arduino
const int DOUTpin=8;  // The DOUT pin of the CO Sensor goes into Digital Pin D8 of the Arduino
const int ledPin=13; // The Anode of the LED connects to Digital Pin D13 of the Arduino

int limit;
int value;

const int trigPin=12;
const int echoPin=10;

int ledpir = 13;                  // The pin that the ledpir is attached to
int sensorpir = 11;              // The pin that the sensorpir is attached to
int state = LOW;                // By default, no motion detected
int valpir = 0;                // Variable to store the sensorpir status 

int buzzerf = 7;

int flame_sensor = 3;
int flame_detected;
int smokeA0 = A4;

int sensorThres = 400; // The threshold value

#define DHT11_PIN A0

long microsecondsToInches(long microseconds){
  
  return microseconds/74/2;

}

long microsecondsToCentimeters(long microseconds){
  
  return microseconds/29/2;
  
}

void setup(){

  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);        // On-board LED, usually pin 13
  pinMode(SHOCK_PIN, INPUT);          // Shock sensor pin set to input
  pinMode(DOUTpin, INPUT);           // Sets the pin as an input to the Arduino
  pinMode(ledPin, OUTPUT);          // Sets the pin as an output of the Arduino
  pinMode(trigPin,OUTPUT);         // Sends the ultrasonic waves
  pinMode(echoPin,INPUT);         // Receives the wave after it is reflected
  pinMode(ledpir, OUTPUT);       // Initializes ledpir as an output
  pinMode(sensorpir, INPUT);    // Initializes sensorpir as an input
  pinMode(buzzerf, OUTPUT);
  pinMode(flame_sensor, INPUT);
  pinMode(smokeA0, INPUT);

}

void loop(){

  int chk = DHT.read11(DHT11_PIN);

  Serial.print("Temperature: ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity: ");
  Serial.println(DHT.humidity);

  delay(1000);

  value= analogRead(AOUTpin);   // Reads the analog value from the CO sensor's AOUT pin
  limit= digitalRead(DOUTpin); // Reads the digital value from the CO sensor's DOUT pin

  Serial.print("CO value: ");
  Serial.println(value); // Prints the CO value
  Serial.print("Limit: ");
  Serial.println(limit); // Prints the limit reached as either LOW or HIGH 

  delay(100);

  if (limit == HIGH){

  digitalWrite(ledPin, HIGH); // If limit has been reached, LED turns on as status indicator

}

  else{

  digitalWrite(ledPin, LOW); // If threshold not reached, LED remains off

}

  long duration,inches,cm;

  digitalWrite(trigPin,LOW);

  delayMicroseconds(2);
 
  digitalWrite(trigPin,HIGH);
 
  delayMicroseconds(10);
  
  digitalWrite(trigPin,LOW);

  duration=pulseIn(echoPin,HIGH);

  inches=microsecondsToInches(duration);
  cm=microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("Distance in inches: ");
  Serial.print(cm);
  Serial.print("Distance in cms: ");
  Serial.println();

  delay(2000);

  int value = analogRead(A2);

  Serial.print (value);

  Serial.print("   ");

  delay(1000);     


  if (value>660){

  Serial.println("HIGH");

}

  else if ((value>600) && (value<=660)){

  Serial.println("AVERAGE");

}

  else{

  Serial.println("LOW");

}

  if (digitalRead(SHOCK_PIN)){       // Shock detected?

  digitalWrite(LED_BUILTIN, HIGH);  // Switch LED on
  
  Serial.println("SHOCK!");
  
  delay(2000);                      // Leave LED on for 2 this time period

}

  else{
  
  digitalWrite(LED_BUILTIN, LOW);   // Switch LED off

  Serial.println("Calm");

}

  valpir = digitalRead(sensorpir);   // Read sensorpir as valpir
 
  if (valpir == HIGH){           // Check if the sensorpir is HIGH

  digitalWrite(ledpir, HIGH);   // Turn ledpir ON
    
  if (state == LOW){

  Serial.println("Motion detected!"); 
  state = HIGH;       // Update variable state to HIGH

}
}
 
  else{

  digitalWrite(ledpir, LOW); // Turn ledpir OFF
       
  if (state == HIGH){
  
  Serial.println("Motion stopped!");
  
  state = LOW;       // Update variable state to LOW

}
}
  
  flame_detected = digitalRead(flame_sensor);

  if (flame_detected == 1){

  Serial.println("Flame detected! Take action immediately!");

  digitalWrite(buzzerf, HIGH);

  delay(200);

  }
  
  else{

  Serial.println("No flame detected. Stay cool");

  digitalWrite(buzzerf, LOW);

}

  delay(1000);

  int smk = analogRead(smokeA0);

  Serial.print("Smoke level: ");
  Serial.println(smk);

  if (smk > sensorThres){   // Checks if it has reached the threshold value


  Serial.println("Unsafe air quality");

}

  else{

  Serial.println("Safe air quality");

}

  delay(100);

}
