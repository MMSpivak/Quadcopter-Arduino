/*
 * Signal recieving with the NRF24L01 module.
 * Help/inspired by @How to Mechatronics.
 * 
 * By: Michael Spivak
 * 8/10/21
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo ESC;

int CE = 7;
int CSN = 8;
int throt;
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

RF24 radio(CE, CSN);
const byte address[6] = "00001";
struct Data_Pack{
  byte throttle;
};
Data_Pack data;

void setup() {

  ESC.attach(9,1000,2000);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver
  resetData();
  

}

void loop() {

  currentTime = millis();
  if ( currentTime - lastReceiveTime > 1000 ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
    resetData(); // If connection is lost, reset the data. It prevents unwanted behavior, for example if a drone jas a throttle up, if we lose connection it can keep flying away if we dont reset the function
  }

  if (radio.available()) {
    radio.read(&data, sizeof(Data_Pack)); // Read the whole data and store it into the 'data' structure
    lastReceiveTime = millis(); // At this moment we have received the data
  }

  throt = data.throttle;
  ESC.write(throt);

}

void resetData() {
  data.throttle = 0;
}
