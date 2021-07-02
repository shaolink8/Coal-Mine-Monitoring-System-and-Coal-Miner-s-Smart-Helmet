byte h=0,v=0;                              // Variables used in for loops
const int period=50;                      // A little delay to avoid errors
int kdelay=0;                            // Non Blocking Delay
const byte rows=4;                      // Rows in Keypad
const byte columns=4;                  // Columns in Keypad
const byte Output[rows]={9,8,7,6};    // Row connected to Arduino Pins
const byte Input[columns]={5,4,3,2}; // Columns connected to Arduino Pins
String pass;
String s;
int pswdc=0;
int c34=0;
String passc;

int c=0;

void setup(){

  Serial.begin(9600);

  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  
  
  for(byte i=0;i<rows;i++){      // Loop to declare output pins
 
  pinMode(Output[i],OUTPUT);
  
}

  for(byte s=0;s<columns;s++){  // Loop to declare input pins, Initial Pulledup

  pinMode(Input[s],INPUT_PULLUP);
  
}

  Serial.begin(9600);         // Initializing Serial communication

}

void loop(){

  if(millis()-kdelay>period){ // Used to make non-blocking delay

  kdelay=millis();  // Capture time from millis function

  if(pswdc==0){

  if(c34==0){

  Serial.println("Enter the password to be set:");

  c34++;

}

}

  else if(pswdc==1){

  if(c34==0){

  Serial.println("\nRe-enter the password for confirmation");

  c34++;

}

}

  else{

  if(c34==0){

  Serial.println("Enter the password: Or Press B for BELL");

  c34++;

} 

}

  switch (keypad()){     // Switch case to get which button is pressed

  case 0:

  s+='1';

  Serial.print('*');

  break;  


  case 1:

  s+='2';

  Serial.print('*');

  break;
       

  case 2:

  s+='3';

  Serial.print('*');

  break;


  case 3:           

  break;


  case 4:

  s+='4';

  Serial.print('*');

  break;


  case 5:

  s+='5';

  Serial.print('*');

  break;


  case 6:

  s+='6';

  Serial.print('*');

  break;


  case 7:

  Serial.println("BELL");

  Serial.println("Enter the password: Or Press B for BELL");

  tone(10,1000,2000);

  break;


  case 8:

  s+='7';Serial.print('*');

  break;


  case 9:

  s+='8';Serial.print('*');

  break;


  case 10:

  s+='9';Serial.print('*');

  break;


  case 11:

  break;


  case 12:

  s+='*';

  Serial.println("*");

  break;


  case 13:

  s+='0';Serial.print('*');

  break;


  case 14:

  s+='#';Serial.print('*');

  break;


  case 15:

  break;


  default:

  ;
            
}

  if(s.length()==4 && pswdc>1){

  if(s.equals(String(pass))){

  Serial.println("\nPassword matched");

  c=0;

  digitalWrite(11,HIGH);

  delay(5000);

  digitalWrite(11,LOW);

}

  else{

  if(c<=2){ 
 
  Serial.println("\nWrong password! Try again.");

  tone(10,8000,1000);

  digitalWrite(12,HIGH);

  delay(1000);

  digitalWrite(12,LOW);
  
  c++;

}

  if(c>=3){

  Serial.println("\nSystem locked. Try After 10s");

  c++;

  digitalWrite(12,HIGH);

  tone(10,5000,10000);

  delay(10000);

  digitalWrite(12,LOW);

}

}

  s=String();

  c34=0;

}

  if(s.length()==4 && pswdc==0){

  pass=s;
  pswdc++;
  s=String();
  c34=0;

}

  if(s.length()==4 && pswdc==1){

  passc=s;

  if(pass.equals(passc)){

  Serial.println("\nPASSWORD SET");

  pswdc++;

}

  else{

  Serial.println("\nPASSWORD DID NOT MATCH! TRY AGAIN");

  pswdc=0;

}

  c34=0;

}  

}

}

  // Below function is used to detect which button is pressed.

  byte keypad(){

  static bool no_press_flag=0;    

  for(byte x=0;x<columns;x++){

  if (digitalRead(Input[x])==HIGH);   

  else
  break;

  if(x==(columns-1)){

  no_press_flag=1;
  h=0;
  v=0;

}

}

  if(no_press_flag==1){

  for(byte r=0;r<rows;r++)  
  digitalWrite(Output[r],LOW);

  for(h=0;h<columns;h++){

  if(digitalRead(Input[h])==HIGH) 
  continue;
  
  else{

  for (v=0;v<rows;v++){

  digitalWrite(Output[v],HIGH);   

  if(digitalRead(Input[h])==HIGH){

  no_press_flag=0;               

  for(byte w=0;w<rows;w++)  
  digitalWrite(Output[w],LOW);
  return v*4+h;  

}

}

}

}

}

  return 50;

}
