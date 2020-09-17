#include "LoRaRadio.h"
#include "Packet.h"
#include <Servo.h>
LoRaRadio lora(PA3, PA2, PA1, 0b0110, 0b0100);
volatile Packet p;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  Serial.println("Initialising...."); 
  lora.begin();
  LoRa.onReceive(receiveCommand);
}


void loop() {
  // put your main code here, to run repeatedly:
}

void receiveCommand(int i){
  Packet p = lora.receiveCommand();
  Serial.println(toString(p));
}

String toString(volatile Packet& p){
  return "Motor Speed: " + (String)p.motorSpeed + " Aeleron R: " + (String)p.aeleronR + " Aeleron L:" + (String)p.aeleronL; 
}

void writeMappedPacket(volatile Packet& p){
  //motor.write(map(command.motorSpeed, 0, 1023, 0, 180));
  //aeleronR.write(map(command.aeleronR, 0, 1023, 0, 180));
  //aeleronL.write(map(command.aeleronL, 0, 1023, 0, 180));
}
