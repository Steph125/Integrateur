#include <Servo.h>

Servo myServo;

const int myservoPin=8;
const int trigPin=2;
const int echoPin=3;
int Time;
long distance;
const int mindist = 20;
int runscanPosition[3] = {70, 80, 90};

int stopscanPosition[13] = {30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150};
int scanPosition;

int scanRunDistance[3];
int scanStopDistance[13];

int getDistance(){
  
  digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
   digitalWrite(trigPin, HIGH);
       delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
  Time=pulseIn(echoPin, HIGH);
  distance=0.0343*Time/2;
  Serial.print(distance);
  Serial.println(" cm");
  
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Capteur ultrasonic");
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  myServo.attach(myservoPin);
  Serial.println("Test");
  myServo.write(75);
  delay(500);
  myServo.write(150);
  delay(500);
  // myServo.write(90);
  // delay(500);
  // myServo.write(180);
  // delay(500);
  Serial.println("Servo fort");
  

}

void loop() {
  // put your main code here, to run repeatedly:
  for (scanPosition = 0; scanPosition<3; scanPosition++){
    myServo.write(runscanPosition[scanPosition]);
    delay(2000);
    scanRunDistance[scanPosition] = getDistance();
    Serial.println(scanRunDistance[scanPosition]);
    // if (scanRunDistance[scanPosition]>mindist){
    //  Serial.println("Passage ");}
    // else if (scanRunDistance[scanPosition]<mindist) {
    //   Serial.println("Chemin bloquer");
    // }     
    }
  
    
}
