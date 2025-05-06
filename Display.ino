/*
  This class contians methods for setting up and displaying information to the Ardunio R4 wifi LED display.
  LED display example code can be found here https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix/
 These functions and display are utilized for debugging purposes or to ensure that there is proper connectivity between the arduino and controller.

 This class also tells the arduino to retrieve the timestamp and include it in the data being sent to the SD card.
*
/*
  This method will setup the Ardunio text display. 
*/
void setupTextDisplay()
{
  matrix.begin();
  showText("ROV");
  Serial.println("setupTextDisplay()"); 
}

/*
  This method will update the text display.
*/
void showText(String t)  {
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(t);
  matrix.endText();
  matrix.endDraw();
}

/*
  This method will add scrolling text to the display. 
*/
void showScrollingText(String t)  {
  // Make it scroll!
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(90);
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(t);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
}