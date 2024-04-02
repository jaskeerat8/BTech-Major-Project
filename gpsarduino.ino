#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 5;
static const uint32_t GPSBaud = 4800;

TinyGPSPlus gps; 

SoftwareSerial ss(TXPin,RXPin);

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop()
{
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}


//To show Location
void displayInfo()
{
  Serial.println("Current Location: "); 
  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
  }
  else
  {
    Serial.println(F("INVALID"));
  }


//To show Date
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("INVALID");
  }


//To show time
  Serial.print("Time: ");
if (gps.time.isValid())
  {
    if(gps.time.minute() <= 29)
    {
    Serial.print(gps.time.hour() + 5);
    Serial.print(":");
    Serial.print(gps.time.minute() + 30 );
    Serial.print(":");
    Serial.println(gps.time.second());
    }
    else
    {
    Serial.print(gps.time.hour() +6);
    Serial.print(":");
    Serial.print(gps.time.minute() - 30 );
    Serial.print(":");
    Serial.println(gps.time.second());
    }
  }
  else
  {
    Serial.println("INVALID");
  }
Serial.println("----------------------------------");
delay(5000);
}