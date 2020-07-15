#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#define FIREBASE_HOST "ultracar-7a145.firebaseio.com"

//Your Firebase Project URL goes here without "http:" , "\" and "/"
#defineFIREBASE_AUTH "2Gb58vG6V6VOFIGySR2yo4ZLG04p4xCFUJRn6w8X"

//Your Firebase Database Secret goes here
#define WIFI_SSID "Vishal"

//your WiFi SSID for which your NodeMCU connects
#define WIFI_PASSWORD "22111999"

#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>

const int LED1red=5;     //D1          const int LED1green=4;   //D2
const int LED2red=0;     //D3          const int LED2green=2;   //D4
const int LED3red=13;    //D7          const int LED3green=15;  //D8

int avail=3;
int occ=0;
int count1=0, count2=0, count3=0;

void setup()
{

  // Connect to Wi-Fi
  Serial.print("Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting..”);
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print(".");
      delay (500);
  }
  
  Serial.println();
  Serial.print("Connected to: “);
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  pinMode(LED1green,OUTPUT);
  pinMode(LED1red,OUTPUT);
  
  pinMode(LED2green,OUTPUT);
  pinMode(LED2red,OUTPUT);
  
  pinMode(LED3green,OUTPUT);
  pinMode(LED3red,OUTPUT);
  
  // Initialize Serial port
  Serial.begin(9600);
  s.begin(9600);
  while (!Serial) continue;
  
}

void firebasereconnect()
{
  
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop()
{
  if (Firebase.failed())
  {
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
  }
  
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid()) return;
  
  int dist1=root["data1"];
  int dist2=root["data2"];
  int dist3=root["data3"];
  
  Serial.println("-----------------------");
  Serial.println(" PARKING");
  Serial.println("spaces available");
  Serial.println("-----------------------");
  
  //Distance1
  if (dist1<=20)
  {
      digitalWrite(LED1red,HIGH);
      digitalWrite(LED1green,LOW);
      Serial.println("\t Slot 1 is occupied");
      if(LED1green,HIGH)
      {
          count1=1;
      }
  }
  else
  {
      Serial.println("\t Slot 1 free to occupy");
      digitalWrite(LED1green,HIGH);
      digitalWrite(LED1red,LOW);
      if(LED1red,HIGH)
      {
          count1=0;
      }
  }
  
  //Distance2
  if (dist2<=20)
  {
      digitalWrite(LED2red,HIGH);
      digitalWrite(LED2green,LOW);
      Serial.println("\t Slot 2 is occupied");
      if(LED2green,HIGH)
      {
          count2=1;
      }
  }
  else
  {
      Serial.println("\t Slot 2 free to occupy");
      digitalWrite(LED2green,HIGH);
      digitalWrite(LED2red,LOW);
      if(LED2red,HIGH)
      {
          count2=0;
      }
   }

  //Distance3
  if (dist3 <=20)
  {
      digitalWrite(LED3red,HIGH);
      digitalWrite(LED3green,LOW);
      Serial.println("\t Slot 3 is occupied");
      if(LED3green,HIGH)
      {
          count3=1;
      }
  }
  else
  {
      Serial.println("\t Slot 3 free to occupy");
      digitalWrite(LED3green,HIGH);
      digitalWrite(LED3red,LOW);
      if(LED3red,HIGH)
      {
          count3=0;
      }
  }

  if(count1==1 && count2==1 && count3==1)
  {
      Serial.println("\n \t \t \t \t --PARKING FULL--");
      occ=count1+count2+count3;
  }
  else
  {
  occ=count1+count2+count3;
  }
  
  Serial.print("\n No.of slots occupied:");
  Serial.println(occ);
  Serial.print("\n Available Slots: ");
  
  avail=avail-occ;
  Serial.println(avail);
  
  Firebase.setInt("Occupied_slots",occ);
  Firebase.setInt("Available_slots",avail);
  delay(3000);
  
  avail=3;
  occ=0;
  count1=0;
  count2=0;
  count3=0;

}
