#include <Nextion.h>
#include "Adafruit_Thermal.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);  
static const int RXPin = 4, TXPin = 3;// Pass addr to printer constructor
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
NexButton b0 = NexButton(1,3,"b0");
NexButton b1= NexButton(1,4,"b1");
NexButton b2 = NexButton(0,2,"b0");
NexButton b3 = NexButton(0,3,"b1");
NexButton b4 = NexButton(0,4,"b2");
NexButton b5 = NexButton(1,5,"b2");
NexButton b6 = NexButton(1,7,"b3");
NexButton b7 = NexButton(1,3,"b1");
int AMOUNT;
int TOT_AMT;
int COUNT=0;
int COUNT_OF_T=1;
String CH_P,a;
String FROM;
String CHECK;
float LAT;
float LON;
NexTouch *nex_listen_list[] = {
  &b0,
  &b1,
  &b2,
  &b3,
  &b4,
  &b5,
  &b6,
  &b7,
  NULL
};
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
  ss.begin(GPSBaud);
 
  
 nexInit();
 b0.attachPop(b0PopCallback,&b0);
 b1.attachPop(b1PopCallback,&b1);
 b2.attachPop(b2PopCallback,&b2);
 b3.attachPop(b3PopCallback,&b3);
 b4.attachPop(b4PopCallback,&b4);
 b5.attachPop(b5PopCallback,&b5);
 b6.attachPop(b6PopCallback,&b6);
 b7.attachPop(b7PopCallback,&b5);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  LAT=gps.location.lat();
  LON=gps.location.lng();
  while (ss.available() > 0){
 int c=ss.read();
    if(gps.encode(c)){
     
     Serial.println("Latitude= ");
     Serial.println(LAT);
    
      
      Serial.println(" Longitude= ");
    
     // Serial.println(gps.location.lng(), 6);
      delay(1000);

    
  
  //LAT=11.035466;

 if(LAT>=10.03 ){
  Serial.println("hai");
  START_P_1();
 }
  
   else if(LAT== 1 && LON==1  ){
     START_P_2();
  
 }
    }
 }
}

    

void b0PopCallback(void *ptr){
  COUNT=COUNT+1;
 
}
void b1PopCallback(void *ptr){
 COUNT=COUNT-1;
 
}
void b2PopCallback(void *ptr){
  CH_P="EEE";
  
 
}
void b3PopCallback(void *ptr){
  CH_P="main block";
  
}
void b4PopCallback(void *ptr){
  CH_P="boys hostel";
}
void b5PopCallback(void *ptr){
  CHECK="ok";
}
void b6PopCallback(void *ptr){
  CHECK="ok";
}
void b7PopCallback(void *ptr){
  CHECK="okk";
}
void START_P_1(){
while(1){
  Serial.println("set point 1");
  LAT=gps.location.lat();
  LON=gps.location.lng();
  if(LAT>=10.03){
    Serial.println("from eee");
    FROM="EEE";
    while(1){
      Serial.println("enter destination");
      nexLoop(nex_listen_list); 
      if(CH_P=="main block"){
        AMOUNT=10;
        a=CH_P;
        Serial.println("to main block");
        while(1){
         CH_P="";
        nexLoop(nex_listen_list);
        if(CHECK=="ok"){
          
          TOT_AMT=10*COUNT;
        RFID();
        }
        else if(CHECK=="okk"){
          START_P_1();
        }
        }
      }
      if(CH_P=="boys hostel"){
        AMOUNT=20;
        a=CH_P;
        Serial.println("boys hostel");
        while(1){
          CH_P="";
        nexLoop(nex_listen_list); 
        if(CHECK=="ok"){
          TOT_AMT=10*COUNT;
          
        RFID();
        }
         else if(CHECK=="okk"){
          START_P_1();
        }
        }
        
      }
    }
  }
  if(LAT=1){
    Serial.println("from eee");
    FROM="MAIN BLOCK";
    while(1){
      nexLoop(nex_listen_list); 
      if(CH_P=="boys hostel"){
        AMOUNT=10;
        a=CH_P;
        Serial.println("to main block");
        while(1){
         CH_P="";
        nexLoop(nex_listen_list);
        if(CHECK=="ok"){
          
          TOT_AMT=10*COUNT;
        RFID();
        }
        }
      }
     
    }
  }
}
}
void PRINTER(){
  Serial.println("printing");
  mySerial.begin(9600);
  // Initialize SoftwareSerial
 printer.begin(); 
  delay(1000);
   printer.setSize('S');
  printer.justify('C');
  printer.print("ticket no :");
 
 // printer.println("date:");
 // printer.justify('R');
 // printer.println("TIME:");
 // printer.justify('L');
  printer.println(COUNT_OF_T);
  printer.justify('L');
  printer.print("FROM :");
  printer.println(FROM);
  printer.justify('R');
  printer.print("TO:");
  printer.println(a);
  printer.justify('C');
  printer.print("NO_OF_TICKET:");
  printer.println(COUNT);
  printer.justify('C');
  printer.print("TOTAL AMOUNT");
  printer.println(TOT_AMT);
  printer.println(" ");
  COUNT_OF_T=COUNT_OF_T+1;
  delay(1000);
   COUNT=0;
   CHECK="";
  
  
 
}
void RFID(){
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin(); 
  mfrc522.PCD_Init();
 while(1){
  nexLoop(nex_listen_list);
  if(CHECK=="okkk"){
    AMOUNT=0;
    TOT_AMT=0;
    COUNT=0;
    loop();
  }
     Serial.println("show rf id");
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  
  content.toUpperCase();
  if (content.substring(1) == "E5 91 5D 21") //change here the UID of the card/cards that you want to give access
  {
   PRINTER();
   START_P_1();
  }
 }
}
void START_P_2(){
  while(1){
  Serial.println("set point 1");
  LAT=gps.location.lat();
  LON=gps.location.lng();
  
  if(LAT>=11.03){
    Serial.println("from eee");
    FROM="BOYS HOSTEL";
    while(1){
      nexLoop(nex_listen_list); 
      if(CH_P=="main block"){
        AMOUNT=10;
        a=CH_P;
        Serial.println("to main block");
        while(1){
         CH_P="";
        nexLoop(nex_listen_list);
        if(CHECK=="ok"){
          
          TOT_AMT=10*COUNT;
        RFID();
        }
        }
      }
      if(CH_P=="EEE"){
        AMOUNT=20;
        a=CH_P;
        Serial.println("boys hostel");
        while(1){
          CH_P="";
        nexLoop(nex_listen_list); 
        if(CHECK=="ok"){
          TOT_AMT=10*COUNT;
          
        RFID();
        }
        }
        
      }
    }
  }
  if(LAT>=11.03){
    Serial.println("from eee");
    FROM="MAIN BLOCK";
    while(1){
      nexLoop(nex_listen_list); 
      if(CH_P=="EEE"){
        AMOUNT=10;
        a=CH_P;
        Serial.println("to main block");
        while(1){
         CH_P="";
        nexLoop(nex_listen_list);
        if(CHECK=="ok"){
          
          TOT_AMT=10*COUNT;
        RFID();
        }
        }
      }
      
    }
  }
}
}
