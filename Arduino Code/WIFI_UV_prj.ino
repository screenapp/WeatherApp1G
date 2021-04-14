/**WORKING COPY - ELEC 3907 Engineering Project***  /

/* This code implements both the UV sensor and the "knock" Gyro/Accell sensor.
   This code is written using the Arduino libraries for ThingSpeak and WifiNINA.
   Program for the Arduino Uno Rev2 Wifi board.

   UV sensor code  @author Alina Jacobson
   Knock sensor code @author Connor Judd
    
    @version 1.2v    @date 4 march 2021
    @version 1.3v    @date 18 march 2021

    Change log:     4 Macrch 2021 - Updated the knock sensor code with the correct initialized varaibles
                                  - Updated the UV ThingSpeak field writing function to match the knock sensor
                                  - Removed the thingSpeak status update output.
                                  - knock sensor code reviewed by Connor Judd
                    18 March 2021  -updated API key and Channel number in sercrets.h
                                  - group members decision to create a new channel in order to make it easier to 
                                    to upload the two sensor data to thingSpeak at the same time.  
                                    as it this cause issue to upload the sensor data to one channel 
                                   -updated field numbers (1, and 2) for the new channel (it was 3 and 4, orignal channel)
                                   -updated the UV conditional statement           
    
 **/

 

/*
  WriteMultipleFields
  
  Description: Writes values to fields 1,2,3,4 and status in a single ThingSpeak update every 20 seconds.
  
  Hardware: Arduino Uno WiFi Rev2
  
  !!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!
  
  Note:
  - Requires WiFiNINA library.
  - This example is written for a network using WPA encryption. For WEP or WPA, change the WiFi.begin() call accordingly.
  
  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and 
  analyze live data streams in the cloud. Visit https://www.thingspeak.com to sign up for a free account and create a channel.  
  
  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.
  
  For licensing information, see the accompanying license file.
  
  Copyright 2020, The MathWorks, Inc.
*/


/*THIS IS A TEST CODE - TO SEND RANDOM NUMBERS TO FIELD 5 to the thingspeak channel*/

#include "ThingSpeak.h"      // always include thingspeak header file after other header files and custom macros
#include <WiFiNINA.h>
#include "secrets.h"


/********knock sensor********/
#include <Arduino_LSM6DS3.h>
/****************************/

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
String myStatus = "";



void setup() {
  Serial.begin(9600);       // Initialize serial 
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only

  }
  IMU.begin(); // Starts the Boards IMU unit
  
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }
    
  ThingSpeak.begin(client);  //Initialize ThingSpeak 



  /*******Knock sensor code**************************/
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
  /****************************************************/
}


void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");

      //10000 = 10sec
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  

  //*******UV Sensor CODE - For project******//
  //using:  GUVA S12SD   UV sensor 
  //reference for UV index in milliVolts: http://arduinolearning.com/code/arduino-guva-s12sd-uv-sensor.php
  
  //initialize variables
  int uv =0;
  int sensorValue = 0;
  
  //reads the input at analog pin 0 of the arduino rev 2 wifi board
  sensorValue = analogRead(A0);

  //converting the input analog reading to a milliVolt value output
  int sensorVoltage = (sensorValue*(5.0/1023.0))*1000; // Change 3.3 to 5 if the power supply of the VMA328 is 5V.
  

      //conditional statements to determine the UV Index output value, based on the reference UV index in milliVolts
       if(sensorVoltage < 227){
      uv =0;
      
      }else if(sensorVoltage <=227 && sensorVoltage<318){
      uv=1;
      
      }else if(sensorVoltage <=318 && sensorVoltage<408){
      uv=2;
      
      }else if(sensorVoltage <=408 && sensorVoltage<503){
      uv=3;
      
      }else if(sensorVoltage <=503 && sensorVoltage<606){
      uv=4;
      
      }else if(sensorVoltage <=606 && sensorVoltage<696){
      uv=5;
      
      }else if(sensorVoltage <=696 && sensorVoltage<795){
      uv=6;
      
      }else if(sensorVoltage <=795 && sensorVoltage<881){
      uv=7;
      
      }else if(sensorVoltage <=881 && sensorVoltage<976){
      uv=8;
      
      }else if(sensorVoltage <=976 && sensorVoltage<1079){
      uv=9;
      
      }else if(sensorVoltage <=1079 && sensorVoltage<1170){
      uv=10;
      
      }else{
      uv=11;     //too extreme
      
      }

      Serial.print("Voltage reading = ");
      Serial.print(sensorVoltage);
      Serial.print("   |   ");
      Serial.print("UV index = ");
      Serial.println(uv);
      
    // set the fields For the UV Index Sensor data to thinkspeak website
    //ThingSpeak.setField(3, uv);               //UV data being sent to Field 3 Chart

    // write the UV Sensor Data to the ThingSpeak channel - field chart 1
    ThingSpeak.writeField(myChannelNumber, 1, uv, myWriteAPIKey);
    delay(1000); // Wait 1 seconds to update the channel again

  

   //*******KNOCK Sensor CODE - For project******************//   

  float x1, y, z, XI, YI, ZI , t, h;
  int knock = 0;
  IMU.readAcceleration(x1, y, z); // Sensor reading of board acceleration
   if ((ZI-0.02) > z > (ZI+0.02) or (XI-0.02) > x1 > (XI+0.02) or (YI-0.02) > y > (YI+0.02)){
   knock = 1;
   }
   Serial.print("Knock:\t");
   Serial.println(knock);

    // write the Knock Sensor Data to the ThingSpeak channel - field chart 2
   ThingSpeak.writeField(myChannelNumber, 2, knock, myWriteAPIKey);// upload knock data to thingspeak
   delay(1000);
   Serial.println();
 
  //********************************************************//   

  

  // set the status
  //ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  //int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  //if(x == 200){
  //  Serial.println("Channel update successful.");
  //}
  //else{
   // Serial.println("Problem updating channel. HTTP error code " + String(x));
  //}


  //delay(30000); // Wait 10 seconds to update the channel again

  
}//end of loop()
