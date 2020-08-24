#include "Potentiometer.h"
#include "Joystick.h"
#include "LoRaRadio.h"

Potentiometer throttle(PA3);
Joystick aeleron(PB0, PB1, PA5, 0b0100, 0b0110);
LoRaRadio lora(PB12, PA12, PA11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lora.begin(433E6);
  attachInterrupt(digitalPinToInterrupt(aeleron.getButton()), buttonIrq, CHANGE);
  packet oldPacket;
  oldPacket.motorSpeed = throttle.getPwmValue();
  //oldPacket.aeleronR = aeleron.
}

void loop() {
  // put your main code here, to run repeatedly:
  packet currentPacket;
  
  if(oldPacket != currentPacket){
    lora.sendCommand(currentPacket);
    oldPacket = currentPacket;
  }
}

void buttonIrq(){}
