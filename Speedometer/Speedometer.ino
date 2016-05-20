#include <SoftwareSerial.h>
#include <Servo.h>

#define trigPin 
#define echoPin

long duration1 = 0, durantion2 = 0, distance1 = 0, distance2 = 0;

long getDuration(){
  long duration = 0;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH); //Emitting soundwave
  delayMicroseconds(10); 
 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //Receiving soundwave

  return duration;
}

long getDistance(long duration){
  //Calculate the distance (in m) based on the speed of sound.
  long distance = duration * 0.5 * 0.0343;
  return distance;
}

long getSpeed(long duration1, long duration2, long distance1, long distance2){
  long spd = (distance2 - distance1) / ((duration1 + duration2) * 0.5);
  return spd;
}

void setup() {
  
}

void loop() {
  if(!(duration1 && duration2)){
    duration1 = getDuration();
    duration2 = getDuration();
    //Assign speed of 0 to servo here
    return;
    //initialize data
  }
  else{
    duration1 = duration2;
    duration2 = getDuration();
    distance1 = getDistance(duration1);
    distance2 = getDistance(duration2);
    spd = getSpeed(duration1,duration2,distance1,distance2);
  }
}


