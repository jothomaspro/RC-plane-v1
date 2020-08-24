#include "LoRaRadio.h"
#include "Packet.h"

LoRaRadio lora(PB12, PA9, PA8, 0b0110, 0b0100);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lora.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}
