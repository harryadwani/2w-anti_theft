#include <Keypad.h>
#include <Servo.h>
#include<string.h>
const byte numRows = 4; //number of rows on the keypad
const byte numCols = 4; //number of columns on the keypad
Servo myservo;  
const int trigPin = 5;
const int echoPin = 6;
const int buzp=7;
const int ledpin =45;
float time_start=0, time_stop=0;
float duration;
int distance,c=0;// create servo object to control a servo
int pos = 0;


//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {14, 15, 16, 17}; //Rows 0 to 3
byte colPins[numCols] = {18, 19, 20, 21}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
//int i = 0;
int entry = 0 ;
int ctr = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(buzp, OUTPUT);
   pinMode(trigPin,OUTPUT);
 pinMode(echoPin,INPUT);
 pinMode(ledpin,OUTPUT);
  myservo.attach(9);
  pinMode(10,INPUT);
  digitalWrite(2,HIGH);

}
//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
//if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process
void loop()
{
  int key = 123;

  char keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY)
  {
    //  Serial.print(keypressed);
    //  Serial.println(entry-48);
    entry = (entry) * 10 + (keypressed - 48);
   Serial.println(entry);


    if (key == entry)
    {
      if (ctr % 2 != 0)
      {
        Serial.println("unlocked");
        for (pos = 0; pos <= 180; pos += 10) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
      
      }
      else
      {
        Serial.println("locked");
        for (pos = 180; pos >= 0; pos -= 10) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);
        }
      }
      ctr++;
      entry=0;
    }
  }


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

if(distance>=20 && distance<=40)
  {
    Serial.println(distance);
    tone(buzp,500);
    digitalWrite(ledpin,HIGH);
    delay(3000);
     
    noTone(buzp);
  
    delay(2000);
    digitalWrite(ledpin,LOW);
 
  }



if(digitalRead(10)==LOW)
{
  tone(buzp,500);
    digitalWrite(ledpin,HIGH);
    delay(3000);
     
    noTone(buzp);
  
    delay(2000);
    digitalWrite(ledpin,LOW);
}

  
}
