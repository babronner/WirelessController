// by b. a.  bronner
// receiving code for 433 MHz transmitter, max 1kHz data

#include <VirtualWire.h> // Author: Mike McCauley (mikem@airspayce.com)

char armedCode[7] = {'a','r','m','e','d','1'}; // armed code
char launchCode[7] = {'l','a','u','n','c','h'}; // launch code
char disarmCode[7] = {'d','i','s','a','r','m'}; // disarmed code
const int armedLight = 8; // pin for light indicating armed status
const int dataIn = 3; // data in pin
const int ignitor = 7; // pin out to igniter

void setup(){
   Serial.begin(9600); // used in debugging
   pinMode(armedLight, OUTPUT); //set pin to either in or out
   pinMode(ignitor, OUTPUT); // "
   digitalWrite(ignitor, LOW); // initialize the ignitor to low or off
   vw_set_rx_pin(dataIn); // VirtualWire package--data pin from the receiver
   vw_setup(2000); // sets bitrate
   vw_rx_start(); // starts receiver PLL
}

void loop(){
   // uint8_t is the variable type: stands for "unsigned integer of length 8 bits"
   uint8_t buflen = VW_MAX_MESSAGE_LEN; // max message length (in bytes?)
   uint8_t buf[buflen]; // creates space for the largest amount of data that could be sent
   if(vw_get_message(buf, &buflen)){ // Non-blocking, always looking for data coming in
      // next three "ifs" check to see if the data being received matches any of the pre-determined codes
      // might be a better way to do this, but this way works
      if(buf[0] == armedCode[0] &&
         buf[1] == armedCode[1] &&
         buf[2] == armedCode[2] &&
         buf[3] == armedCode[3] &&
         buf[4] == armedCode[4] &&
         buf[5] == armedCode[5] &&
         buf[6] == armedCode[6]){
         digitalWrite(armedLight, HIGH); // turns on the 555 timer for the lamp blink
      }
      if(buf[0] == launchCode[0] &&
         buf[1] == launchCode[1] &&
         buf[2] == launchCode[2] &&
         buf[3] == launchCode[3] &&
         buf[4] == launchCode[4] &&
         buf[5] == launchCode[5] &&
         buf[6] == launchCode[6]){
         digitalWrite(ignitor, HIGH); // turns ingitor on for 5 seconds, then back off
         delay(5000); // milliseconds
         digitalWrite(ignitor, LOW);
      }
      if(buf[0] == disarmCode[0] &&
         buf[1] == disarmCode[1] &&
         buf[2] == disarmCode[2] &&
         buf[3] == disarmCode[3] &&
         buf[4] == disarmCode[4] &&
         buf[5] == disarmCode[5] &&
         buf[6] == disarmCode[6]){
         digitalWrite(armedLight, LOW); // turns off lamp blink when system disarmed
      }   
   }
}
