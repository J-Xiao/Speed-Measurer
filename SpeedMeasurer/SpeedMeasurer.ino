#include <SoftwareSerial.h>
#include <Servo.h>

#define echoPin_left 8 // Echo Pin of the sensor on the left
#define trigPin_left 7 // Trigger Pin of the sensor on the left
#define echoPin_middle 2 // Echo Pin of the sensor in the middle
#define trigPin_middle 4 // Trigger Pin of the sensor in the middle
#define echoPin_right 12 // Echo Pin of the sensor on the right
#define trigPin_right 13 // Trigger Pin of the sensor on the right
#define LED_red 1
#define LED_green 2

long distance_left, distance_middle, distance_right;
long distance_half;
unsigned long time_left, time_middle, time_right;

long get_distance_left(){ //Function used to measure the distance in the front
 long duration;
 long distance;
 
 digitalWrite(trigPin_left, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin_left, HIGH); //Emitting soundwave
 delayMicroseconds(10); 
 
 digitalWrite(trigPin_left, LOW);
 duration = pulseIn(echoPin_left, HIGH); //Receiving soundwave
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;

 return distance;
}

long get_distance_middle(){ //Function used to measure the distance in the front
 long duration;
 long distance;
 
 digitalWrite(trigPin_middle, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin_middle, HIGH); //Emitting soundwave
 delayMicroseconds(10); 
 
 digitalWrite(trigPin_middle, LOW);
 duration = pulseIn(echoPin_middle, HIGH); //Receiving soundwave
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;

 return distance;
}

long get_distance_right(){ //Function used to measure the distance in the right
 long duration;
 long distance;
 
 digitalWrite(trigPin_right, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin_right, HIGH); //Emitting soundwave
 delayMicroseconds(10); 
 
 digitalWrite(trigPin_right, LOW);
 duration = pulseIn(echoPin_right, HIGH); //Receiving soundwave
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;

 return distance;
}

void setup() {
  Serial.begin (9600);
  pinMode(trigPin_left, OUTPUT);
  pinMode(echoPin_left, INPUT);
  pinMode(trigPin_middle, OUTPUT);
  pinMode(echoPin_middle, INPUT);
  pinMode(trigPin_right, OUTPUT);
  pinMode(echoPin_right, INPUT);

  pinMode(LED_green, OUTPUT);
  pinMode(LED_red, OUTPUT);
  pinMode(servo_pointer, OUTPUT);
} 

void loop() {
  unsigned long time_half;
  unsigned long time_full;
  long speed_one, speed_two;
  long average_speed_m_s, average_speed_km_h;
  
  distance_left = get_distance_left();
  distance_half = diatance_left/1.414;   // distance_left*sin(45) = half of the distance (in cm)
  

}
