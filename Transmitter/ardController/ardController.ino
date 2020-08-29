#include "Potentiometer.h"
#include "Joystick.h"
#include "LoRaRadio.h"
#include "Packet.h"

Potentiometer throttle(A0);
Joystick aeleron(A2, A3, 2);
LoRaRadio lora(7, 6, 3, 0b0100, 0b0110);
Packet oldPacket;
Packet currentPacket;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lora.begin(433E6);
  //attachInterrupt(digitalPinToInterrupt(aeleron.getButton()), buttonIrq, CHANGE);
  oldPacket.motorSpeed = throttle.getPwmValue();
  oldPacket.aeleronR = aeleron.getPwmValueX();
  oldPacket.aeleronL = aeleron.getPwmValueY();
}

void loop() {
  // put your main code here, to run repeatedly:
  currentPacket.motorSpeed = throttle.getPwmValue();
  currentPacket.aeleronR = aeleron.getPwmValueX();
  currentPacket.aeleronL = aeleron.getPwmValueY();
  
  if(difference(oldPacket, currentPacket) > 2){
    Serial.println(toString(currentPacket));
    lora.sendCommand(currentPacket);
    oldPacket = currentPacket;
  }
  delay(500);
}

/*void buttonIrq(){
  Serial.println("INT button");  
}*/

String toString(Packet p){
  return "Motor Speed: " + (String)p.motorSpeed + " Aeleron R: " + (String)p.aeleronR + " Aeleron L: " + (String)p.aeleronL; 
}
