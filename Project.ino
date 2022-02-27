#include <Wire.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

//LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//GPS
int RXPin = 6;
int TXPin = 7;
int GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial gpsSerial(7,6);

//Haversine
double Radius=6371e3;
double lat1, lat2;
double long1, long2;
double latitude1, latitude2;
double longitude1, longitude2;
double rad;
double del_lat,del_long; 
double var_a;
double var_c;
double var_d;

double c_dist1,t_dist1=0;
double c_dist2,t_dist2=0;

double lat_conv1,lat_conv2,long_conv1,long_conv2;

double curr_speed,avg_speed,pre_speed=0,speed_counter=1;

int count = 1;
void setup()
{
  Serial.begin(9600);
  delay(10);
  gpsSerial.begin(GPSBaud);
  lcd.begin(20, 4);
  lcd.clear();
  pinMode(2,INPUT_PULLUP); // Trip 1 Reset Button
  pinMode(3,INPUT_PULLUP); // Trip 2 Reset Button
  
}

void loop()
{
  
  while (gpsSerial.available())
  { 
    if (gps.encode(gpsSerial.read()))
    { 
      //code here
    if (gps.location.isValid()&& gps.speed.isValid())
      { delay(10);
        Serial.print("count :");
        Serial.println(count);
       
       if (count==1)
       { delay(10);
          lat1=gps.location.lat();
          long1=gps.location.lng();
          Serial.println(lat1);
          Serial.println(long1);
          count++;
       }
       if(digitalRead(2)==0)
       {delay(10);
        t_dist1=0;
       }
       if(digitalRead(3)==0)
       {delay(10);
        t_dist2=0;
       }

        delay(10);
        
        curr_speed = gps.speed.kmph();
        
        delay(10);
        lat2=gps.location.lat();
        long2=gps.location.lng();
        
        Serial.print("lat2: ");  
        Serial.println(lat2);
        Serial.print("long2: ");  
        Serial.println(long2);
        delay(10);
        haversine();

        Serial.println(var_d);
        delay(10);
        c_dist1=var_d;
        c_dist2=var_d;
        
        if (c_dist1<=3.0)
        {delay(10);
          c_dist1=0;
        }
        if(c_dist1>3.0)
        {delay(10);
        c_dist1=var_d;
        }

        if (c_dist2<=3.0)
        {delay(10);
          c_dist2=0;
        }
        if(c_dist2>3.0)
        {delay(10);
        c_dist2=var_d;
        }

        if (curr_speed<=3.0)
        {delay(10);
          curr_speed=0; 
        }
        if(curr_speed>3.0)
        {delay(10);
        avg_speed = (pre_speed+curr_speed)/speed_counter;
        pre_speed  = (pre_speed+curr_speed);
        speed_counter++;
        } 

        delay(10);
        lat1=lat2;
        long1=long2;
        
        t_dist1=t_dist1+c_dist1;
        t_dist2=t_dist2+c_dist2;
        delay(10);
        lcd.setCursor(0, 0);
        lcd.print("Trip 1: "); 
        lcd.print(t_dist1,6);
        delay(10);
        lcd.setCursor(0, 1);
        lcd.print("Trip 2: ");
        lcd.print(t_dist2,6);
        delay(10);
        lcd.setCursor(0, 2);
        lcd.print("Speed : ");
        lcd.print(gps.speed.kmph(),6);
        delay(10);
        lcd.setCursor(0, 3);
        lcd.print("AVG_Speed : ");
        lcd.print(avg_speed,3);
        delay(10);
        Serial.print("Distance 1:");
        Serial.println(t_dist1);
        Serial.print("Distance 2:");
        Serial.println(t_dist2);
        
        delay(10);
      }    
    }
  }      
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }
}
