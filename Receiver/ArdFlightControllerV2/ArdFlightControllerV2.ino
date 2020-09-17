#include "LoRaRadio.h"
#include "Packet.h"
#include <Servo.h>
LoRaRadio lora(7, 6, 3, 0b0110, 0b0100);

Servo motor;
Servo aeleronR;
//Servo aeleronL;
volatile Packet command;
volatile bool packetReceived = false;
volatile uint16_t timeSinceLast = 0;
uint16_t oldTime;
uint16_t newTime;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  motor.attach(3);
  aeleronR.attach(5);
  lora.begin();
  LoRa.receive();
  //LoRa.onReceive(receiveCommand);
  while(!Serial);
  Serial.println("Motor_Speed:,AeleronR:,AeleronL:"); //,ReceiveTime:");
}


void loop() {
  int len = LoRa.parsePacket();
  if(len != 0){
    Serial.println("Packet size: " + (String)len);
    receiveCommand(1);
    writeMappedPacket(command);
  }
}

void receiveCommand(int packetSize){
  oldTime = millis();
  command = lora.receiveCommand();
  newTime = millis();
  //Serial.print(toString(command));
  //printTimeDiff(oldTime, newTime);
}

void writeMappedPacket(volatile Packet& p){
  motor.write(map(command.motorSpeed, 0, 1023, 0, 180));
  aeleronR.write(map(command.aeleronR, 0, 1023, 0, 180));
  //aeleronL.write(map(command.aeleronL, 0, 1023, 0, 180));
}

void printTimeDiff(uint16_t t1, uint16_t t2){
  Serial.println("," +(String)(t2 - t1));
}
