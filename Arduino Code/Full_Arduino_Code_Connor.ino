// Combination of the two sensor codes
// can upload temp/humid/UV/Knock to the thingspeak
//Code compiled by Connor Judd
//Contributions by Alina Jacobson and Alex Merkulov 
#include <WiFiNINA.h>
#include <ThingSpeak.h>
#include <Arduino_LSM6DS3.h>
#include <DHT.h>
#include <time.h> 
#define DHTPIN 2 
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);
const char* ntpServer = "pool.ntp.org";
unsigned long myChannelNumber = 1292014;
const char * myWriteAPIKey = "8JM99WUHS6RF1FD6";
const char* ssid = "";
const char* password = "";

WiFiClient  client;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);
  dht.begin(); //Starts the Tempurature and Humidity Sensor 

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);// Connect to WiFi network
  
  while (WiFi.status() != WL_CONNECTED) {// checks the wifi connection 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  

  
  // Start the server
  // server.begin();
  // Serial.println("Server started");   
  // Print the IP address
  Serial.println(WiFi.localIP());
  Serial.println();
  ThingSpeak.begin(client);
    
  IMU.begin(); // Starts the Boards IMU unit
  while (!Serial);
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!"); // tests to see if the IMU is working
    while (1);
  }
  float XI, YI, ZI;
  IMU.readAcceleration(XI, YI, ZI); // sets the initial values for the board position 
  Serial.println("Initial XYZ Board Directions");
  Serial.println("X\tY\tZ");
  Serial.print(XI);
  Serial.print("\t");
  Serial.print(YI);
  Serial.print("\t");
  Serial.println(ZI);
  Serial.println();
  Serial.println("Sensor Data");

  
  
}

void loop() {
  
  int uv =0;
  int sensorValue = 0;
  //reads the input at analog pin 0 of the arduino rev 2 wifi board
  sensorValue = analogRead(A0);

  //converting the input analog reading to a milliVolt value output
  int sensorVoltage = (sensorValue*(5.0/1023.0))*1000; // Change 3.3 to 5 if the power supply of the VMA328 is 5V.

      //conditional statements to determine the UV Index output value, based on the reference UV index in milliVolts
      if(sensorVoltage < 50){
      uv =0;  
      }else if(sensorVoltage>=50 && sensorVoltage<318){
      uv=1;    
      }else if(sensorVoltage>=318 && sensorVoltage<408){
      uv=2;    
      }else if(sensorVoltage>=408 && sensorVoltage<503){
      uv=3;  
      }else if(sensorVoltage>=503 && sensorVoltage<606){
      uv=4; 
      }else if(sensorVoltage>=606 && sensorVoltage<696){
      uv=5;  
      }else if(sensorVoltage>=696 && sensorVoltage<795){
      uv=6;  
      }else if(sensorVoltage>=795 && sensorVoltage<881){
      uv=7;
      }else if(sensorVoltage>=881 && sensorVoltage<976){
      uv=8;      
      }else if(sensorVoltage>=976 && sensorVoltage<1079){
      uv=9;      
      }else if(sensorVoltage>=1079 && sensorVoltage<1170){
      uv=10;     
      }else{
      uv=11;      
      }
           
  // write to the ThingSpeak channel
  ThingSpeak.writeField(myChannelNumber, 1, uv, myWriteAPIKey);
  delay(1000); // Wait 1 seconds to update the channel again

  float x, y, z, XI, YI, ZI , t, h;
  
  
    t = dht.readTemperature(); //Sensor Reading of Tempurature 
    Serial.print("Temp:\t");
    Serial.println(t);
    ThingSpeak.writeField(myChannelNumber, 2, t, myWriteAPIKey);// upload tempuraure data to thingspeak 
    delay(1000); 
  
    h = dht.readHumidity(); //Sensor Reading of Humidity
    Serial.print("Humi:\t"); 
    Serial.println(h);
    ThingSpeak.writeField(myChannelNumber, 3, h, myWriteAPIKey);// upload humidity data to thingspeak 
    delay(1000);
  int knock = 0;
    IMU.readAcceleration(x, y, z); // Sensor reading of board acceleration
    if ((ZI-0.02) > z > (ZI+0.02) or (XI-0.02) > x > (XI+0.02) or (YI-0.02) > y > (YI+0.02)){
        knock = 1; 
        Serial.print("Knock:\t");
        Serial.println(knock);
        ThingSpeak.writeField(myChannelNumber, 5, knock, myWriteAPIKey);// upload knock data to thingspeak 
        delay(1000);
        }

    Serial.println();
  
   
}
