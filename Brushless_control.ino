/*
 * How I controlled the brushless motors for testing purposes.
 * Code modified from @How To Mechatronics 
 * 
 * By: Michael Spivak
 * 8/10/2021
*/
#include <Servo.h>
Servo ESC;     // create servo object to control the ESC
int potValue;  // value from the analog pin
void setup() {
  // Attach the ESC on pin 9
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  Serial.begin(9600);    //Setting the serial output for picking up data
  delay(100);           
  pinMode(5, OUTPUT);    //Set the pins connected to the joystick button to an output
  digitalWrite(5, HIGH); //Set the pins to HIGH (5V). When the button is pressed it will pull the pin to ground (0V)
  delay(100);
 
}
void loop() {
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)

  // This here to actually be able to give 0 thrust for testing purposes
  if(potValue < 20){
    potValue = 0;
  } else if(potValue > 160){
    potValue = 180;
  }

  ESC.write(potValue);   // Send the signal to the ESC

  Serial.print("Motor speed: ");
  Serial.print(potValue);
  Serial.println();
}
