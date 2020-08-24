#include "Potentiometer.h"
#include "Joystick.h"
#include "LoRaRadio.h"
#include "Packet.h"

Potentiometer throttle(PA3);
Joystick aeleron(PB0, PB1, PA5);
LoRaRadio lora(PB12, PA12, PA11, 0b0100, 0b0110);
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
    lora.sendCommand(currentPacket);
    oldPacket = currentPacket;
  }
}

void buttonIrq(){}
