#include "LoRaRadio.h"
#include "Packet.h"

LoRaRadio lora(PA3, PA2, PA1, 0b0110, 0b0100);

void setup() {
  // put your setup code here, to run once
  pinMode(PC13, OUTPUT);
  digitalWrite(PC13, LOW);
  delay(3000);
  digitalWrite(PC13, HIGH);
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

String toString(Packet p){
  return "Motor Speed: " + (String)p.motorSpeed + " Aeleron R: " + (String)p.aeleronR + " Aeleron L:" + (String)p.aeleronL; 
}
