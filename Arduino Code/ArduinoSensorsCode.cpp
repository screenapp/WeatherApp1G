// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
#include <Wire.h>
#include "rgb_lcd.h"
#include "DHT.h"

 

int sensorValue;//
long sum = 0;//
int vout = 0;//
int uv = 0;//

 

#define DHTPIN 2     // what digital pin we're connected to

 

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

 

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

 

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

 

rgb_lcd lcd;
void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 test!");

 

  dht.begin();

 

  lcd.begin(16, 2);
    
 
   
}

 

   void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

 

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

 


  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

 

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

 

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");

 

sensorValue = 0;
  sum = 0;
  for(int i = 0 ; i < 1024 ; i++ )//filter calculation 
  {  
      sensorValue = analogRead(A0);
      sum = sensorValue + sum;
      delay(2);
  }
  vout = sum >> 10;//deal with data 
  vout = vout * 4980.0 / 1024;
  Serial.print("The Photocurrent value : ");
  Serial.print(vout);
  Serial.println("mV");
  if(vout < 50){  //check and change the voltage value to uv level 
    uv = 0;
  }
  else if(vout < 227){
    uv = 1;
  }
  else if(vout < 318){
    uv = 2;
  }    
  else if(vout < 408){
    uv = 3;
  }
  else if(vout < 503){
    uv = 4;
  }
  else if(vout < 606){
    uv = 5;
  }
  else if(vout < 696){
    uv = 6;
  }
  else if(vout < 795){ 
    uv = 7;
  }
  else if(vout < 881){
    uv = 8;
  }
  else if(vout < 976){
    uv = 9;
  }
  else if(vout < 1079){
    uv = 10;
  }
  else{
    uv = 11;
  }
  delay(20);
  

 

 

 

 

 

 

 


  
 

 

 

 

 


  

 

lcd.setCursor(0,0);
lcd.print("Humid:");//show"Humidity(%)"
lcd.print (dht.readHumidity());
lcd.print("%");

 

lcd.setCursor(0,1);
lcd.print("Temp:");//show"Temperature(C)"
lcd.print(dht.readTemperature());
lcd.print("C");

 


lcd.setCursor(12,15);
lcd.print("UV:");//show"UV" IMPORTANT: REARRANGE THE SCREEN 
lcd.print(uv);
lcd.print(".");

 }
