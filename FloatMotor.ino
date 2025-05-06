/*
This class contains the functions that control the linear actuator and by extension the buoyancy engine. It tells the linear actuator to stay not extended while traveling down the water column, and extend enough to make it neutrally buoyant once it have hit 2.5 meters. After it hovers for 45 seconds, it will extend the actuator to make it positively buoyant and begin its ascent.

*/
void setupMotor()
{
  pinMode(10, OUTPUT); // Configure pin 10 as an Output
  pinMode(9, OUTPUT); // Configure pin 9 as an Output
  Serial.println("setupMotor()"); 
}

void extendActuatorFullSpeed ()// Extend Actuator at Full Speed
{  
  //Variable for the speed of the motor (0-255);
  byte speed = 255; 
  analogWrite(RPWM, 0);
  analogWrite(LPWM, speed);
  Serial.println("extendActuatorFullSpeed ()"); 
}

void extendActuator (byte speed)// Extend actuator based on passed in speed
{  
  //Variable for the speed of the motor (0-255);
  analogWrite(RPWM, 0);
  analogWrite(LPWM, speed);
  Serial.println("extendActuator (byte speed)"); 
}
 void retractActuatorFullSpeed() //Retract actuator at full speed
{
  //Variable for the speed of the motor (0-255);
  byte speed = 255;
  analogWrite(RPWM, speed);
  analogWrite(LPWM, 0);
  Serial.println("retractActuatorFullSpeed()"); 
}
 void retractActuator(byte speed) // Extend actuator based on passed in speed
{
  //Variable for the speed of the motor (0-255);
  analogWrite(RPWM, speed);
  analogWrite(LPWM, 0);
  Serial.println("retractActuator(byte speed) "); 
}
void stopActuator ()  // Stop Actuator
{
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
  Serial.println("stopActuator ()  "); 
}


 