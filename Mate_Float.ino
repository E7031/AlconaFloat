#include "arduino_secrets.h"
/* 
Controller for MATE Float device. 
  
This controller class runs an autonomous float.

This float functions autonomously to collect data underwater. It will go down 3 meters and stay between 2.5 and 3 meters recording 100 data points. Once 100 data points are collected the float will return to the surface. 
  
Arduino IoT Cloud Variables description
The class contains the following variables:

  String displayText;
  float altitude;
  float depth;
  float pressure;
  float temp;
  bool deployFloat;
  bool led;
  bool readFloatData;
  bool recordData;
*/

#include <MS5837.h>
#include <Wire.h>
#include "thingProperties.h"
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include <SPI.h>
#include <SD.h>
#include "RTC.h"
#include <TimeLib.h>
#include <string>

ArduinoLEDMatrix matrix;
MS5837 sensor;
File myFile;
int RPWM = 10;  //connect Arduino pin 10 to IBT-2 pin RPWM
int LPWM = 9;  //connect Arduino pin 9 to IBT-2 pin LPWM
int recordCount = 0;


void setup() {
  // Initialize serial and wait for port to open:
  //Serial Monitor is used for debuging and testing. Serial Monitor is only available 
  //when using a usb cable. It is not available over wifi. 
  Serial.begin(9600);
  
  //Initialize control variables and properties
  initProperties(); // defined in thingProperties.h

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
   /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(4);
  ArduinoCloud.printDebugInfo();
  pinMode(LED_BUILTIN, OUTPUT);

  //Initialize time
  setupTime();
  
  //Setup LED display located on the UNO R4 wifi board. The LED display is used for testing  
  //and debugging.
  setupTextDisplay();
  
  //Initialize sensors
  setupSensor();

  //Initialize SD card read/write
  setupSDReader();

  //Initialize motors 
  setupMotor();
}

void loop() {
  ArduinoCloud.update();
  //write the LED value to the ardunio. The true false/value is toggled on the dashboard.
  digitalWrite(LED_BUILTIN, led);

  //If float has been deployed write timestamp data to SD card. Wifi connection will be lost when the float goes under water. 
  if(deployFloat)
  {
    RTCTime currenttime;
    RTC.getTime(currenttime);
    Serial.print("Time: ");
    Serial.print(currenttime.getHour());
    Serial.print(":");
    Serial.print(currenttime.getMinutes());
    Serial.print(":");
    Serial.println(currenttime.getSeconds());

    //Read data from sensor
    sensor.read();
    depth = sensor.depth();
    temp = sensor.temperature();
    String record = "Site: Harrisville Harbor, Temp: " temp + ", Depth:  " + depth;
    record to SD card
    writeToFile(record);
    recordCount = recordCount + 1; 
   
    if (depth <= 2.5 && (recordCount < 100 ))
    {   
      Serial.println("Do I get Here? depth <= 2.5"); 
      retractActuatorFullSpeed();
    }
    else if ((depth > 2.5) && (depth <= 3) && (recordCount < 100 ))
    {
      Serial.println("Do I get Here?  depth > 2.5 && depth <= 3"); 
      byte speed = 127; //half speed 
      retractActuator(speed);
    }
    else if ((depth > 3) && (recordCount < 100 ))
    {
      Serial.println("Do I get Here?  depth > 3"); 
      byte speed = 127; //half speed 
      extendActuator(speed);
    }
    else // send to the surface
    {
      Serial.println("Do I get Here?  send to the surface"); 
      extendActuatorFullSpeed();
    }
  }
  // if float has not been deployed send live data to dashboard. This requires ardunio wifi connection. 
  else
  {
    // Read values from float pressure bar sensor.
    sensor.read();
    //set IoT Variables to sensor values. This will allow us to create a live feed of the sensor 
    //values while the MATE float device is connected to the IoT. 
    pressure = sensor.pressure();
    temp = sensor.temperature();
    depth = sensor.depth();
    altitude = sensor.altitude();
  }  
}

/*
  Since Led is READ_WRITE variable, onLedChange() is
  executed every time a new value is received from IoT Cloud (Mate Float Dashboard).

  Use this method for debugging. When device is connected by usb this method will write out to the 
  Serial Monitor when Led value is toggled on the Dashboard. 
*/
void onLedChange()  {
  Serial.print("Led status changed:");
  Serial.println(led);
}

/*
  Since DeployFloat is READ_WRITE variable, onDeployFloatChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onDeployFloatChange()  {
  //Change the display on the Adrunio Uno R4 wifi board to indicate deploy 
  
  if(deployFloat)
    {
      showScrollingText("    Float Deployed!    ");
      recordCount = 0;
    }
    else
    {
      showScrollingText("    MATE 2025    ");
    }
}

/*
  Since ReadFloatData is READ_WRITE variable, onReadFloatDataChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onReadFloatDataChange()  {
  if(readFloatData)
  {
    displayText = readFromFile ();
    Serial.print("Fetch data from file:");
    Serial.println(displayText);   
  }  
  else
  {
    displayText = "no data";
  }
}

/*
  Since DisplayText is READ_WRITE variable, onDisplayTextChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onDisplayTextChange()  {
  // Add your code here to act upon DisplayText change
}

/*
  Since RecordData is READ_WRITE variable, onRecordDataChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onRecordDataChange()  {
  // Add your code here to act upon RecordData change
}