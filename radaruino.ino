#include <Servo.h>


#define SONAR_ECHO 44 //Define pin for Echo of the Ultrasonic Sensor
#define SONAR_TRIG 42 //Define pin for Trig of the Ultrasonic Sensor
#define SERVO 50 //Define pin for Servo 

Servo myServo; //Creates a servo object for controlling the servo motor

// Variables for the duration,distance and radar azimuth
float timeToTgt;
float distToTgt;
int radarAzimuth;
int distance;

// Function for calculating the distance measured by the Ultrasonic sensor
int findDistance(){
  digitalWrite(SONAR_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(SONAR_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_TRIG, LOW);
  timeToTgt = pulseIn(SONAR_ECHO, HIGH);
  distToTgt = (timeToTgt*.0343)/2; // Multiply by 0.0343 to find distance in centimeters
  return distToTgt;
}

void setup() {
  pinMode(SONAR_TRIG, OUTPUT); // Sets the trig as an Output
  pinMode(SONAR_ECHO, INPUT); // Sets the echo as an Input
  myServo.attach(SERVO); // Defines on which pin is the servo motor attached
  Serial.begin(9600);
}

void loop() {
  // rotates the servo motor from 0 to 180 degrees
  for (radarAzimuth = 0; radarAzimuth <= 180; radarAzimuth++){
    myServo.write(radarAzimuth);
    delay(30);
    distance = findDistance();
    Serial.print(radarAzimuth);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }

   // Repeats the previous lines from 180 to 0 degrees
  for (radarAzimuth = 180; radarAzimuth >= 0; radarAzimuth--){
    myServo.write(radarAzimuth);
    delay(30);
    distance = findDistance();
    Serial.print(radarAzimuth);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}
