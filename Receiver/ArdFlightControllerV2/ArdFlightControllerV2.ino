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
uint32_t oldTime = 0;
uint32_t newTime;
uint32_t avgTime = 0;
uint16_t nbRecu =0;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  motor.attach(3);
  aeleronR.attach(5);
  lora.begin();
  LoRa.receive();
  //LoRa.onReceive(receiveCommand);
  while(!Serial);
  Serial.println("TimeDiff:,nbMsg:,Motor_Speed:,AeleronR:,AeleronL:");
  while(LoRa.parsePacket() <= 0);
  receiveCommand(1);
  oldTime = command.t;
}


void loop() {
  if(LoRa.parsePacket() > 0){
    //Serial.print("len = " + (String)len + " ");
    receiveCommand(1);
    writeMappedPacket(command);
  }
}

void receiveCommand(int packetSize){
  command = lora.receiveCommand();
  Serial.println((String)command.t + " - " + (String)oldTime);
 // Serial.println(toDataString(command));
  appendAverage(command.t - oldTime);
  oldTime = command.t;
}

void writeMappedPacket(volatile Packet& p){
  //motor.write(map(command.motorSpeed, 0, 1023, 0, 180));
  aeleronR.write(map(command.aeleronR, 0, 870, 0, 180));
  //aeleronL.write(map(command.aeleronL, 0, 1023, 0, 180));
}

uint32_t timeDiff(uint32_t t1, uint32_t t2){
  return t2 - t1;
}

void appendAverage(uint32_t t){
  avgTime = (avgTime*nbRecu + t)/(++nbRecu);
}
