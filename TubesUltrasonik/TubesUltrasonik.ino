#include <Servo.h>

static const int servoPin = 4;
const int trigPin = 12;
const int echoPin = 13;
long duration;
float distanceCm;

#define SOUND_SPEED 0.034
#define buzzer 23

Servo servo1;

void setup() {
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(buzzer, OUTPUT);
    servo1.attach(servoPin);
}

void loop() {
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        ultrasonik();
        delay(50);
    }

    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        ultrasonik();
        delay(50);
    }
}

void ultrasonik(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  if(distanceCm <= 20){
      digitalWrite(buzzer, HIGH);
      Serial.println("Status : Objek Dekat!");
      Serial.print("Distance (cm): ");
      Serial.println(distanceCm);
    }else{
      digitalWrite(buzzer, LOW);
      Serial.print("Distance (cm): ");
      Serial.println(distanceCm); 
    }
}
