#include <Servo.h>

// HCSR04
#define trigPin 12
#define echoPin 13
long duration;
float distanceCm;

//Joystick
int servoVal;
#define joyX 27
#define joyY 26
#define sw 25

//Button
#define button 15
bool statButton;

//Tambahan
#define SOUND_SPEED 0.034
#define buzzer 23

Servo servo1;
Servo servo2;

void setup() {
    Serial.begin(115200);

    //Ultrasonik
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(buzzer, OUTPUT);

    //Servo
    servo1.attach(4); //Bawah
    servo2.attach(5); //Atas
    servo2.write(170);

    //Joy
    pinMode(sw, INPUT_PULLUP);
    pinMode(joyX, INPUT);
    pinMode(joyY, INPUT);

    //Button
    pinMode(button, INPUT_PULLUP); //0 = True dan 1 = False
}

void loop() {
    statButton = digitalRead(button);
    if(statButton == 1){
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
      }else{
        joystick();
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

void joystick(){
  Serial.println("Penggunaan Joystick");
  servoVal = analogRead(joyX);
  servoVal = map(servoVal, 0, 1023, 0, 180);
  Serial.print("Sumbu X (Kiri-Kanan) : ");
  Serial.println(servoVal);
  servo1.write(servoVal);

  servoVal = analogRead(joyY);
  servoVal = map(servoVal, 0, 1023, 100, 180);
  Serial.print("Sumbu Y (Atas-Bawah) : ");
  Serial.println(servoVal);
  servo2.write(servoVal);
  delay(50);  
  }
