#include "Potentiometer.h"
#include "Joystick.h"
#include "LoRaRadio.h"
#include "Packet.h"

Potentiometer throttle(PB0);
Joystick aeleron(PA2, PA1, PC14);
LoRaRadio lora(PB1, PA12, PA11, 0b0100, 0b0110);
Packet oldPacket;
Packet currentPacket;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lora.begin(433E6);
  attachInterrupt(digitalPinToInterrupt(aeleron.getButton()), buttonIrq, CHANGE);
  
  oldPacket.motorSpeed = throttle.getPwmValue();
  oldPacket.aeleronR = aeleron.getPwmValueX();
  oldPacket.aeleronL = aeleron.getPwmValueY();
}

void loop() {
  // put your main code here, to run repeatedly:
  currentPacket.motorSpeed = throttle.getPwmValue();
  currentPacket.aeleronR = aeleron.getPwmValueX();
  currentPacket.aeleronL = aeleron.getPwmValueY();
  
  if(oldPacket != currentPacket){
    Serial.println(toString(currentPacket));
    lora.sendCommand(currentPacket);
    oldPacket = currentPacket;
  }
}

void buttonIrq(){
  Serial.println("INT button");  
}

String toString(Packet p){
  return "Motor Speed: " + (String)p.motorSpeed + " Aeleron R: " + (String)p.aeleronR + " Aeleron L:" + (String)p.aeleronL; 
}
