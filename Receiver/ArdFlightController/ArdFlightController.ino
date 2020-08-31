#include "LoRaRadio.h"
#include "Packet.h"
#include <Servo.h>
LoRaRadio lora(7, 6, 3, 0b0110, 0b0100);

//Servo motor;
volatile Servo aeleronR;
//Servo aeleronL;
volatile Packet command;
volatile bool packetReceived = false;
volatile uint16_t timeSinceLast = 0;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  //motor.attach(3);
  aeleronR.attach(5);
  lora.begin();
  LoRa.receive();
  //LoRa.onReceive(receiveCommand);
}


void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println((String)packetReceived);
  if(LoRa.parsePacket() != 0){
    receiveCommand(1);
    writeMappedPacket(command);
  }
  /*if(packetReceived){
    timeSinceLast = millis();
    //Serial.println(toString(command));
    writeMappedPacket(command);
    packetReceived = false;
  }
  Serial.println(packetReceived);*/
}

void receiveCommand(int i){
  command = lora.receiveCommand();
  Serial.println(toString(command));
  packetReceived = true;
}

String toString(volatile Packet& p){
  return " Motor Speed: " + (String)p.motorSpeed + " Aeleron R: " + (String)p.aeleronR + " Aeleron L: " + (String)p.aeleronL; 
}

void writeMappedPacket(volatile Packet& p){
  //motor.write(map(command.motorSpeed, 0, 1023, 0, 180));
  aeleronR.write(map(command.aeleronR, 0, 1023, 0, 180));
  //aeleronL.write(map(command.aeleronL, 0, 1023, 0, 180));
}
