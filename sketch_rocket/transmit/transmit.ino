// by b. a.  bronner
// transmitting code for 433 MHz transmitter, max 1kHz data

#include <VirtualWire.h> // Author: Mike McCauley (mikem@airspayce.com)

const int transmit = 12; // data output, constant pin
const int launchSwitch = 7; // trigger to send launch command, constant pin
const int armedLight = 9; // LED output, to a 555 timer, constant pin
const int armedSwitch = 11; // trigger disarmed until this goes low, constant pin
char disarmCode[7] = {'d','i','s','a','r','m'}; // disarmed code
char armedCode[7] = {'a','r','m','e','d','1'}; // armed code
char launchCode[7] = {'l','a','u','n','c','h'}; // launch code


void setup(){
   pinMode(armedLight, OUTPUT); // led displaying armed state, seting pin out
   pinMode(armedSwitch, INPUT); // switch to arm, input
   pinMode(launchSwitch, INPUT); // switch to launch, input
   vw_set_tx_pin(transmit); // sets the transmit pin
   vw_setup(2000); // bps
}

void loop(){
   if(digitalRead(armedSwitch) == LOW){ // check if armed
      digitalWrite(armedLight, HIGH); // make light flash if armed 
      vw_send((uint8_t *)armedCode, 7); // send code telling receiver to arm
      vw_wait_tx(); // waits until message is sent
      delay(500); // delay to make sure everything is OK
      // only while armed, will this look to see if trigger pressed
      if(digitalRead(launchSwitch) == LOW){ // if trigger pressed
         vw_send((uint8_t *)launchCode, 7); // send launch code
         vw_wait_tx();
         delay(500);
      }
   }
   if(digitalRead(armedSwitch) == HIGH){
      digitalWrite(armedLight, LOW); // if armed switch turned off, turn off armed light
      vw_send((uint8_t *)disarmCode, 7);; // tell receiver to disarm
      vw_wait_tx();
      delay(500);
   }
}
