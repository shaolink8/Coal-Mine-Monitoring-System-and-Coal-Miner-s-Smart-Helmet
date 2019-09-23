#include <dht.h>
#define SHOCK_PIN 5
dht DHT;
const int AOUTpin=5;//the AOUT pin of the CO sensor goes into analog pin A0 of the arduino
const int DOUTpin=8;//the DOUT pin of the CO sensor goes into digital pin D8 of the arduino
const int ledPin=13;//the anode of the LED connects to digital pin D13 of the arduino
int limit;
int value;
const int trigPin=12;
const int echoPin=10;
int ledpir = 13;                // the pin that the ledpir is atteched to
int sensorpir = 11;              // the pin that the sensorpir is atteched to
int state = LOW;             // by default, no motion detected
int valpir = 0;                 // variable to store the sensorpir status (valpirue)
int buzzerf = 7;
int flame_sensor = 3;
int flame_detected;
int smokeA0 = A4;
// Your threshold value
int sensorThres = 400;
#define DHT11_PIN A0
 long microsecondsToInches(long microseconds)
  {
    return microseconds/74/2;
  }
  long microsecondsToCentimeters(long microseconds)
  {
    return microseconds/29/2;
  }
void setup(){
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);       // on-board LED, usually pin 13
  pinMode(SHOCK_PIN, INPUT);          // shock sensor pin set to input
  pinMode(DOUTpin, INPUT);//sets the pin as an input to the arduino
pinMode(ledPin, OUTPUT);//sets the pin as an output of the arduino
 pinMode(trigPin,OUTPUT); // sends the ultrasonic waves
 pinMode(echoPin,INPUT); // recieves the sound wave after it is reflected
pinMode(ledpir, OUTPUT);      // initalize ledpir as an output
  pinMode(sensorpir, INPUT);    // initialize sensorpir as an input
  pinMode(buzzerf, OUTPUT);
  pinMode(flame_sensor, INPUT);
pinMode(smokeA0, INPUT);
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);
  value= analogRead(AOUTpin);//reads the analaog value from the CO sensor's AOUT pin
limit= digitalRead(DOUTpin);//reads the digital value from the CO sensor's DOUT pin
Serial.print("CO value: ");
Serial.println(value);//prints the CO value
Serial.print("Limit: ");
Serial.println(limit);//prints the limit reached as either LOW or HIGH (above or underneath)
delay(100);
if (limit == HIGH){
digitalWrite(ledPin, HIGH);//if limit has been reached, LED turns on as status indicator
}
else{
digitalWrite(ledPin, LOW);//if threshold not reached, LED remains off
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
  Serial.print("in,");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(2000);

  // read the input on analog pin 0:

  int value = analogRead(A2);

  // print out the value you read:

  Serial.print (value);

  Serial.print("   ");

  delay(1000);     


if (value>660)

{

   Serial.println("HIGH");

}

else if ((value>600) && (value<=660))

{

Serial.println("AVERAGE");

}


else

{

  Serial.println("LOW");


}
 if (digitalRead(SHOCK_PIN)) {       // shock detected?
    // shock detected with pull-down resistor
    digitalWrite(LED_BUILTIN, HIGH);  // switch LED on
    Serial.println("SHOCK!");
    delay(2000);                      // leave LED on for period
    
  }
  else {
    // shock not detected with pull-down resistor
    digitalWrite(LED_BUILTIN, LOW);   // switch LED off
    Serial.println("calm");
  }
    valpir = digitalRead(sensorpir);   // read sensorpir valpirue
  if (valpir == HIGH) {           // check if the sensorpir is HIGH
    digitalWrite(ledpir, HIGH);   // turn ledpir ON
                    // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(ledpir, LOW); // turn ledpir OFF
              // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }
  
  flame_detected = digitalRead(flame_sensor);
  if (flame_detected == 1)
  {
    Serial.println("Flame detected...! take action immediately.");
    digitalWrite(buzzerf, HIGH);
    delay(200);
  }
  else
  {
    Serial.println("No flame detected. stay cool");
    digitalWrite(buzzerf, LOW);
  }
  delay(1000);
int smk = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(smk);
  // Checks if it has reached the threshold value
  if (smk > sensorThres)
  {
    Serial.println("Unsafe air quality");
  }
  else
  {
    Serial.println("Safe air quality");
  }
  delay(100);

}
