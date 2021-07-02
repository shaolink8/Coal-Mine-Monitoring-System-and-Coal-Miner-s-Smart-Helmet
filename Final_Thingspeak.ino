#include "ThingSpeak.h"
#include "secrets.h"
#include <ESP8266WiFi.h>

const int trigPin = 2;  // D4
const int echoPin = 0;  // D3

char ssid[] = "Shaolin's World";    //  network SSID ( name ) 
char pass[] = "sixtimes";          //  network password
int keyIndex = 0;                 //  network key index number ( needed only for WEP )

WiFiClient  client;

unsigned long myChannelNumber = 861433;
const char * myWriteAPIKey = "3SK5ZKX8PST9LIRN";

int val;
int LDRpin = A0; // LDR Pin Connected at A0 Pin

#include "DHT.h"        // Including the library of DHT11 ( Temperature and Humidity Sensor )

#define DHTTYPE DHT11   
#define dht_dpin 10

DHT dht(dht_dpin, DHTTYPE); 

// Initialize our values

int distance = random(0,100);
int h = random(0,100);
int t = random(0,100);
String myStatus = "";
long duration;

void setup(){

  Serial.begin(115200);      // Initialize serial
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  delay(10);

  Serial.println("Humidity and Temperature\n\n");

  delay(700);

  dht.begin();

  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak

}

void loop(){


  // Connect or reconnect to WiFi

  if(WiFi.status() != WL_CONNECTED){

  Serial.print("Attempting to connect to SSID: ");
  Serial.println(SECRET_SSID);

  while(WiFi.status() != WL_CONNECTED){

  WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network

  Serial.print(".");

  delay(5000);     

} 

  Serial.println("\nConnected.");
  
}

  float h = dht.readHumidity();
  float t = dht.readTemperature();         

  Serial.print("Current Humidity: ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("Current Temperature: ");
  Serial.print(t); 
  Serial.println("C  ");

  delay(800);

  val = analogRead(LDRpin); // Read analog values and store in val variable
 
  Serial.print(val); // Print on serial monitor
 
  delay(1000);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance= duration*0.034/2;

  // Prints the distance on the serial monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  delay(2000);

  ThingSpeak.setField(1, val);
  ThingSpeak.setField(2, distance);
  ThingSpeak.setField(3, h);
  ThingSpeak.setField(4, t);

  // Figure out the status message
  // Used just for implementation of status message, not of significance to the use case

  if(val > distance){

  myStatus = String("Field 1 is greater than Field 2"); 

}

  else if(val < distance){

  myStatus = String("Field 1 is less than Field 2");

}

  else{

  myStatus = String("Field 1 equals Field 2");

}
  
  // Set the status
  ThingSpeak.setStatus(myStatus);
  
  // Write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if(x == 200){

  Serial.println("Channel update successful");

}

  else{

  Serial.println("Problem updating channel. HTTP error code " + String(x));

}
  
  // Change the values
  val++;

  if(val > 99){

  val = 0;

}
  
  delay(20000); // Wait 20 seconds to update the channel again

}
