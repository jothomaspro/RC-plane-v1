#include "LoRaRadio.h"
#include "Packet.h"
#include <Servo.h>
LoRaRadio lora(PB8, PB7, PB6, 0b0110, 0b0100);

Servo motor;
Servo aeleronR;
//Servo aeleronL;
Packet command;
uint32_t oldTime = 0;
uint32_t newTime = 0;
uint32_t avgTime = 0;
uint32_t nbRecu = 0;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  delay(3000);
  while(!Serial);
  Serial.println("nbMsg:,Motor_Speed:,AeleronR:,AeleronL:,TimeDiff:");
  motor.attach(PA9);
  aeleronR.attach(PA10);
  lora.begin();
  //LoRa.receive();
  //LoRa.onReceive(receiveCommand);
  
  while(LoRa.parsePacket() <= 0);
  receiveCommand(1);
  oldTime = command.t;
}


void loop() {
  if(LoRa.parsePacket() > 0){
    receiveCommand(1);
    writeMappedPacket(command);
  }
}

void receiveCommand(int packetSize){
  command = lora.receiveCommand();
  //Serial.println((String)command.t + " - " + (String)oldTime);
  //Serial.println(toDataString(command));
  if(oldTime > 0) appendAverage(command.t - oldTime);
  oldTime = command.t;
}

void writeMappedPacket(Packet p){
  motor.write(map(command.motorSpeed, 0, 1023, 0, 180));
  aeleronR.write(map(command.aeleronR, 0, 1023, 0, 180));
  //aeleronL.write(map(command.aeleronL, 0, 1023, 0, 180));
}

uint32_t timeDiff(uint32_t t1, uint32_t t2){
  return t2 - t1;
}

void appendAverage(uint32_t t){
  nbRecu++;
  if(nbRecu > 0) avgTime = (avgTime*(nbRecu-1) + t)/(nbRecu);
}
