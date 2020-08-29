#include "LoRaRadio.h"
#include "Packet.h"

LoRaRadio lora(7, 6, 3, 0b0110, 0b0100);

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  
  lora.begin();
  LoRa.receive();
  LoRa.onReceive(receiveCommand);
}


void loop() {
  // put your main code here, to run repeatedly:
}

void receiveCommand(int i){
  Packet p = lora.receiveCommand();
  Serial.println(toString(p));
}

String toString(Packet p){
  return " Motor Speed: " + (String)p.motorSpeed + " Aeleron R: " + (String)p.aeleronR + " Aeleron L: " + (String)p.aeleronL; 
}
