/*
 * Signal sending with the NRF24L01 module.
 * With help from/inspired by @How to Mechatronics.
 * 
 * By: Michael Spivak
 * 8/10/2021 
 */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

int CE = 4;
int CSN = 2;
int potValue;

RF24 radio(CE, CSN);
const byte address[6] = "00001";
struct Data_Pack{
  byte throttle;
};
Data_Pack data;

void setup() {

  //Begin radio communication
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_LOW);

  Serial.begin(9600);
  Serial.print("Starting engines!");
  data.throttle = 0;
  
}

void loop() {

  potValue = map(analogRead(A1), 0, 1023, 0, 180);
  if(potValue < 20){
    potValue = 0;
  } else if(potValue > 160){
    potValue = 180;
  }

  Serial.print("Motor speed: ");
  Serial.print(potValue);
  Serial.println();
  
  data.throttle = potValue; //assigns the potValue to throttle data packet
  radio.write(&data, sizeof(Data_Pack)); //sends the data
}
