/*
        Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/
#include <Servo.h>
Servo ESC;     // create servo object to control the ESC
int potValue;  // value from the analog pin
void setup() {
  // Attach the ESC on pin 9
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  Serial.begin(9600);    //Setting the serial output for picking up data
  delay(2000);           
  pinMode(5, OUTPUT);    //Set the pins connected to the joystick button to an output
  digitalWrite(5, HIGH); //Set the pins to HIGH (5V). When the button is pressed it will pull the pin to ground (0V)
  delay(2000);
  Serial.print("Servo test commencing! Starting with half throttle");
  delay(2000);
  ESC.write(20);
  delay(5000);
  ESC.write(0);
  Serial.print("Prepare for full throttle!");
  delay(2000);
  ESC.write(40);
  delay(2000);
}
void loop() {
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  ESC.write(potValue);    // Send the signal to the ESC
  Serial.print("Motor speed: " + potValue);
}
