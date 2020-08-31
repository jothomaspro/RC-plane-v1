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
  oldPacket.motorSpeed = throttle.getVoltage();
  oldPacket.aeleronR = aeleron.getX();
  oldPacket.aeleronL = aeleron.getY();
}

void loop() {
  // put your main code here, to run repeatedly:
  currentPacket.motorSpeed = throttle.getVoltage();
  currentPacket.aeleronR = aeleron.getX();
  currentPacket.aeleronL = 300;
  
  if(difference(oldPacket, currentPacket) > 5){
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
  return "Motor : " + (String)p.motorSpeed + " Aeleronr: " + (String)p.aeleronR + " Aeleronl: " + (String)p.aeleronL; 
}
