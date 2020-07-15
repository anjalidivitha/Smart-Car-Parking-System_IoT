#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial s(5,6);

const int trigPin1 = 13, echoPin1 = 12;
const int trigPin2= 3, echoPin2= 2;
const int trigPin3 =9, echoPin3 =8;

long duration1, duration2, duration3;
int distance1, distance2, distance3;

void setup()
{

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  
  Serial.begin(9600);
  s.begin(9600);
  
}
void loop()
{

  //Distance1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1= duration1 *0.034/2;
  
  //Distance2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2= duration2 *0.034/2;
  
  //Distance3
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3= duration3 *0.034/2;
  
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  
  root["data1"] = distance1;
  root["data2"] = distance2;
  root["data3"] = distance3;
  if(s.available()>0)
  {
      root.printTo(s);
  } 
}
