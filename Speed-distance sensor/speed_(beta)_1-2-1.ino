#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment object
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance1=0;
int distance2=0;
double Speed=0;
int distance=0;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {2,3,4,5,6,7,8,9};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = true; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode( 7 , OUTPUT);
Serial.begin(9600); // Starts the serial communication
}

float ultrasonicRead ()
{
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

//calculating distance
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance in cm : ");
Serial.println(distance);
return distance;
}

float speed ()
{

//calculating Speed
   distance1 = ultrasonicRead(); //calls ultrasoninicRead() function below
   
   delay(1000);//giving a time gap of 1 sec
   
   distance2 = ultrasonicRead(); //calls ultrasoninicRead() function below
   
   //formula change in distance divided by change in time
   Speed = (distance2 - distance1)/1.0; //as the time gap is 1 sec we divide it by 1.
}

float printSeg () 
{
//Displaying Speed
Serial.print("Speed in cm/s  :"); 
Serial.println(Speed);
sevseg.setNumber(Speed);
sevseg.refreshDisplay();
}

void loop() 
{
speed();
printSeg();
}

