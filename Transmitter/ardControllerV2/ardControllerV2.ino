#include "Potentiometer.h"
#include "Joystick.h"
#include "LoRaRadio.h"
#include "Packet.h"
#define FILTER 40
#define THRESHOLD 9

Potentiometer throttle(A0);
Joystick aeleron(A2, A3, 2);
LoRaRadio lora(7, 6, 3, 0b0100, 0b0110);
Packet oldPacket;
Packet currentPacket;
byte nbMsg;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lora.begin(433E6);
  //attachInterrupt(digitalPinToInterrupt(aeleron.getButton()), buttonIrq, CHANGE);
  oldPacket.motorSpeed = throttle.getVoltage();
  oldPacket.aeleronR = aeleron.getX();
  oldPacket.aeleronL = aeleron.getY();
  while(!Serial);
  Serial.println("nbMsg:,Motor:,Alereonr:,AeleronL:,Time:");
}

void loop() {
  // put your main code here, to run repeatedly:
  currentPacket.motorSpeed = throttle.getVoltage();
  currentPacket.aeleronR = aeleron.getX();
  currentPacket.aeleronL = aeleron.getY();
  for(int i(1); i < FILTER; i++){
    currentPacket.motorSpeed += throttle.getVoltage();
    currentPacket.aeleronR += aeleron.getX();
    currentPacket.aeleronL += aeleron.getY();
  }
  currentPacket.motorSpeed /= FILTER;
  currentPacket.aeleronR /= FILTER;
  currentPacket.aeleronL /= FILTER;
  
  if(difference(oldPacket, currentPacket) > THRESHOLD){
    currentPacket.t = millis();
    currentPacket.nbMsg = nbMsg;
    Serial.println(toDataString(currentPacket));
    lora.sendCommand(currentPacket);
    oldPacket = currentPacket;
    nbMsg++;
  }
}

/*void buttonIrq(){
  Serial.println("INT button");  
}*/

uint16_t difference(Packet p1, Packet p2){
  return abs(p1.motorSpeed - p2.motorSpeed) + abs(p1.aeleronR - p2.aeleronR) + abs(p1.aeleronL - p2.aeleronL);
}

uint16_t difference(uint16_t x, uint16_t y){
  return abs(x-y);
}

void printTimeDiff(uint16_t t1, uint16_t t2){
  Serial.println((String)(t2 - t1));
}
