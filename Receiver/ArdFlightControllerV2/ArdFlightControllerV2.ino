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
uint16_t oldTime = 0;
uint16_t newTime;
uint16_t avgTime = 0;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  motor.attach(3);
  aeleronR.attach(5);
  lora.begin();
  LoRa.receive();
  //LoRa.onReceive(receiveCommand);
  while(!Serial);
  Serial.println("nbMsg:,Motor_Speed:,AeleronR:,AeleronL:,ReceiveTime:");
}


void loop() {
  int len = LoRa.parsePacket();
  if(len != 0){
    receiveCommand(1);
    //writeMappedPacket(command);
  }
}

void receiveCommand(int packetSize){
  command = lora.receiveCommand();
  Serial.print(toString(command));
  Serial.println("," + command.t);
  oldTime = command.t;
}

void writeMappedPacket(volatile Packet& p){
  motor.write(map(command.motorSpeed, 0, 1023, 0, 180));
  aeleronR.write(map(command.aeleronR, 0, 1023, 0, 180));
  //aeleronL.write(map(command.aeleronL, 0, 1023, 0, 180));
}

uint16_t timeDiff(uint16_t t1, uint16_t t2){
  return abs(t2 - t1);
}
