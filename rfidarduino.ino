#include <SPI.h>
#include<MFRC522.h>
#include <Ethernet.h>

#define SS_PIN 10 
#define RST_PIN 9
#define No_Of_Card 3


MFRC522 rfid(SS_PIN,RST_PIN);
MFRC522::MIFARE_Key key; 
byte id[No_Of_Card][4]={
  {147,232,113,12},                        
  {151,94,80,84},
  {199,124,138,98}              
};
byte id_temp[3][3];
byte i;
int j=0;
int red = 7;
int blue = 6;
int buzzer = 8;

void setup() {

 Serial.begin(9600);
pinMode(blue,OUTPUT);
pinMode(red,OUTPUT);
pinMode(buzzer,OUTPUT);

Serial.println("Connecting");
Serial.println(" ");
  SPI.begin();
  rfid.PCD_Init();
  for(byte i=0;i<6;i++)
  {
    key.keyByte[i]=0xFF;
  }
     Serial.println("Connect a Card - ");
     Serial.println(" ");
}

void loop()
{int m=0;
  
  if(!rfid.PICC_IsNewCardPresent())
  return;
  if(!rfid.PICC_ReadCardSerial())
  return;

  for(i=0;i<4;i++)
  {
   id_temp[0][i]=rfid.uid.uidByte[i]; 
             delay(50);
  }
  
   for(i=0;i<No_Of_Card;i++)
  {
          if(id[i][0]==id_temp[0][0])
          {
            if(id[i][1]==id_temp[0][1])
            {
              if(id[i][2]==id_temp[0][2])
              {
                if(id[i][3]==id_temp[0][3])
                {
                  Serial.println("Card detected:");
                  for(int s=0;s<4;s++)
                  {
                    Serial.print(rfid.uid.uidByte[s]);
                  }
  digitalWrite(red,HIGH);
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  digitalWrite(red,LOW);
  
                   Serial.print(" ");
                  Sending_To_db();
                  j=0;
                            
                            rfid.PICC_HaltA(); rfid.PCD_StopCrypto1();   return; 
                }
              }
            }
          }
   else
   {j++;
    if(j==No_Of_Card)
    {
      Serial.println("Card detected:");
      for(int s=0;s<4;s++)
        {
          Serial.print(rfid.uid.uidByte[s]);
        }
   digitalWrite(blue,HIGH);
   delay(2000);
   digitalWrite(blue,LOW);
  
      Serial.print(" ");
      Sending_To_db();
      j=0;
    }}}
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
 }
 void Sending_To_db()  
 {
    if(j!=No_Of_Card)
    {
      Serial.print("Stolen");
      Serial.println(" ");
    }
    else
    {
      Serial.print("Not_Stolen");
      Serial.println(" ");
    }
 }