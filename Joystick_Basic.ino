
/*  Author: Michael Spivak
 *  Date: 8/4/2021
 *  
 *  This code reads the value of each joystick axis using the Analog Read function.
 *  
 *  Each value for the joystick range should from 0-1023.
 *  The push-buttons should read 0 when pushed and 1 when not pushed.
 *
 */

void setup() {

  Serial.begin(9600);    //Setting the serial output for picking up data
  delay(2000);           
  pinMode(5, OUTPUT);    //Set the pins connected to the joystick button to an output
  digitalWrite(5, HIGH); //Set the pins to HIGH (5V). When the button is pressed it will pull the pin to ground (0V)

}

void loop() {

 
 Serial.print("Joystick:   "); //Read the Joystick value
 Serial.print("X: ");
 Serial.print(analogRead(A0)); // Read the X value
 Serial.print("\t  ");
 Serial.print("Y: ");
 Serial.print(analogRead(A1)); //Read the Joystick value
 Serial.print("\t  ");
 Serial.print(digitalRead(5)); //Read the Button value
 Serial.print("\t");
 
 Serial.println();
 delay(10);
}
