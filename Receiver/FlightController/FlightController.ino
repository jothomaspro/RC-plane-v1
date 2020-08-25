#include "LoRaRadio.h"
#include "Packet.h"

LoRaRadio lora(PB12, PA9, PA8, 0b0110, 0b0100);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lora.begin();
  
  LoRa.onReceive(receiveCommand);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void receiveCommand(int i){
  uint8_t header = LoRa.read();
  uint8_t sender = header & 0b00001111;
  uint8_t target = header >> 4;
  Serial.print("Sender: ");
  Serial.print(sender);
  Serial.print(" -- Destination:");
  Serial.print(0b0100);
  Serial.print("Target: ");
  Serial.print(target);
  Serial.print(" -- Local Address:");
  Serial.print(0b0110);

  Packet p;
  p.motorSpeed = LoRa.read();
  p.aeleronR = LoRa.read();
  p.aeleronL = LoRa.read();
  //return p;
}
