/*
 * LoRaRadio.cpp
 *
 *  Created on: 23 ao�t 2020
 *      Author: jthom
 */

#include "LoRaRadio.h"

LoRaRadio::LoRaRadio(uint8_t csPin, uint8_t rstPin, uint8_t irqPin, byte destination, byte localAddress)
: _localAddress(localAddress), _destination(destination)
{
	LoRa.setPins(csPin, rstPin, irqPin);
}

bool LoRaRadio::begin(long freq){
	if (!LoRa.begin(freq)) {             
	Serial.println("LoRa init failed. Check your connections.");
	return false;
	}
  Serial.println("LoRa Tx online.");
	return true;
}

bool LoRaRadio::sendMessage(String message){
	LoRa.beginPacket();                   // start packet
	LoRa.write(_destination);             // add destination address
	LoRa.write(_localAddress);            // add sender address
	LoRa.write(message.length());        // add payload length
	LoRa.print(message);                 // add payload
	return LoRa.endPacket();              // finish packet and send it
}

bool LoRaRadio::sendCommand(Packet p){
  digitalWrite(PC13, LOW);
	byte header = (_destination << 4) + _localAddress;
	LoRa.beginPacket();
	LoRa.write(header);
	LoRa.write(p.motorSpeed);
	LoRa.write(p.aeleronR);
	LoRa.write(p.aeleronL);
  digitalWrite(PC13, HIGH);
	return LoRa.endPacket();
}

Packet LoRaRadio::receiveCommand(){
  uint8_t header = LoRa.read();
  uint8_t sender = header & 0b00001111;
  uint8_t target = header >> 4;
  Serial.print("Sender: ");
  Serial.print(sender);
  Serial.print(" -- Destination: ");
  Serial.print(this->_destination);
  Serial.print("Target: ");
  Serial.print(target);
  Serial.print(" -- Local Address: ");
  Serial.print(this->_localAddress);

  Packet p;
  p.motorSpeed = LoRa.read();
  p.aeleronR = LoRa.read();
  p.aeleronL = LoRa.read();
  return p;
}
