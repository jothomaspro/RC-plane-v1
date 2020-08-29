/*
 * LoRaRadio.cpp
 *
 *  Created on: 23 ao�t 2020
 *      Author: jthom
 */

#include "LoRaRadio.h"

LoRaRadio::LoRaRadio(uint8_t csPin, uint8_t rstPin, uint8_t irqPin, byte destination, byte localAddress)
: _csPin(csPin), _rstPin(rstPin), _irqPin(irqPin), _localAddress(localAddress), _destination(destination) {}

bool LoRaRadio::begin(long freq){
  LoRa.setPins(_csPin, _rstPin, _irqPin);
  
	if (!LoRa.begin(freq)) {             // initialize ratio at 915 MHz
	Serial.println("LoRa init failed. Check your connections.");
	return false;
	}
  //Serial.println("LoRa Rx online.");
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
	byte header = (_destination << 4) + _localAddress;
	LoRa.beginPacket();
	LoRa.write(header);
	LoRa.write(p.motorSpeed);
	LoRa.write(p.aeleronR);
	LoRa.write(p.aeleronL);
	return LoRa.endPacket();
}

Packet LoRaRadio::receiveCommand(){
  uint8_t header = LoRa.read();
  uint8_t sender = header & 0b00001111;
  uint8_t target = header >> 4;
  Serial.print("RSSI: ");
  Serial.print(LoRa.packetRssi());
  Serial.print(" Sender: ");
  Serial.print(sender, HEX);
  Serial.print(" Destination: ");
  Serial.print(this->_destination, HEX);
  Serial.print(" Target: ");
  Serial.print(target, HEX);
  Serial.print(" Local Address: ");
  Serial.print(this->_localAddress, HEX);

  Packet p;
  p.motorSpeed = LoRa.read();
  p.aeleronR = LoRa.read();
  p.aeleronL = LoRa.read();
  return p;
}

void LoRaRadio::onReceive(void(*callback)(int)){
}

#ifdef LORAINT
//LoRa::LoRa.onReceive(receiveCommand); What to do?
#endif
