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
#define servo_pointer 3

Servo Pointer;
int pos = 0;

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
  
  pointer.write(0);                      //Reset the servo pointer

  if(distance_left){                     // A vehicle is detected on the left side
    time_left = millis();                // When a vehicle is detected, check time
    while(!get_distance_middle()){         // Wait until the sensor in the middle to give feeedback
      //Just wait
    }
    time_middle = millis();              // The same vehicle is detected in the middle, check the time again
    time_half_left = time_middle - time_left;   // The time difference is the time used by the vehicle to cover distance_half
    speed_one = distance_half/(10*time_half_left);   // v = s/t, v is in m/s
    
    while(!get_distance_right()){
      //Just wait
    }
    time_right = millis();
    time_half_right = time_right - time_middle;
    speed_two = distance_half/(10*time_half_right);   // Do the same thing again
  }else{
    speed_one = 0;                               // If no vehicle is detected, set the speed to 0
    speed_two = 0;
  }
  average_speed_m_s = (speed_one + speed_two)/2;     // Calculate the average speed to reduce error
  average_speed_km_h = average_speed_m_s*3.6;
  while(average_speed_km_h){
    pos = average_speed_km_h;                       //Need an algorithm to convert speed to the angle we want
    pointer.write(pos);
  }
}
