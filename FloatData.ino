/*
SD card read/write

These functions allow the data that is collected by the sensor to be transfered to the SD card in order to store the data   while the device cannot communicate with the controller. The data will then be retrieved by the controller once internet connectivity has been restored. 

It also contains the function that will allow the float to retrieve the real time clock from the arduino cloud library so that that data can be included in the readings.
 
This example shows how to read and write data to and from an SD card file
The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

*/

void setupSDReader() {
  if (!SD.begin(4)) {
    while (1);
  }
 
  // create the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("float.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    myFile.println("float data collected on");
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening float.txt");
  }
}

void writeToFile(String r){
   myFile = SD.open("float.txt", FILE_WRITE);
      // if the file opened okay, write to it:
      if (myFile) {
        myFile.println(r);
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error writing to file");
      }
}

String readFromFile(){
  String t = "file empty";
  // re-open the file for reading:
  myFile = SD.open("float.txt");
  if (myFile) {
    Serial.println("float.txt");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      
     // Serial.write(myFile.read());
      t = myFile.readString();
      
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening float.txt");
  }
  return t;
}

void setupTime(){
  //ArduinoCloud.adjustLocalTime(gmtOffset_sec, daylightOffset_sec);
  RTC.begin();
  //rtc.setEpoch(ArduinoCloud.getLocalTime());
  //RTC.setTime(ArduinoCloud.getEpochTime());

  long unsigned int local_time = ArduinoCloud.getLocalTime(); // Assuming ArduinoCloud is initialized
  unsigned int currentTime;
  int currentHour, currentMinute, currentSecond;
  setTime(currentTime);

  currentHour = hour();
  currentMinute = minute();
  currentSecond = second();

  // Extract time components (assuming local_time is a tm struct)
 // int year = local_time.tm_year + 1970;
 // int month = local_time.tm_mon;
 // int day = local_time.tm_mday;
 // int hour = local_time.tm_hour;
 // int minute = local_time.tm_min;
 // int second = local_time.tm_sec;

  // Create the epoch time
  tmElements_t tmSet;
  //tmSet.Year = year - 1970;
  //tmSet.Month = month;
  //tmSet.Day = day;
  tmSet.Hour = currentHour;
  tmSet.Minute = currentMinute;
  tmSet.Second = currentSecond;

  time_t epochTime = makeTime(tmSet);
  // Set RTC time
  RTCTime mytime(epochTime);
  RTC.setTime(mytime);
}



