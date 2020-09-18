/*
 * LoRaRadio.cpp
 *
 *  Created on: 23 ao�t 2020
 *      Author: jthom
 */

#include "LoRaRadio.h"
#include "Packet.h"

LoRaRadio::LoRaRadio(uint8_t csPin, uint8_t rstPin, uint8_t irqPin, byte destination, byte localAddress)
: _csPin(csPin), _rstPin(rstPin), _irqPin(irqPin), _localAddress(localAddress), _destination(destination) {}

bool LoRaRadio::begin(long freq){
  LoRa.setPins(_csPin, _rstPin, _irqPin);
  
	if (!LoRa.begin(freq)) {             // initialize ratio at 915 MHz
	Serial.println("LoRa init failed. Check your connections.");
	while(1); //here
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
	byte header = (_destination << 4) | _localAddress;
  LoRa.beginPacket();
  LoRa.write(header);
  LoRa.write(p.nbMsg);
  //LoRa.write(p.t);
  LoRa.write((uint8_t)(p.motorSpeed>>8));
  LoRa.write((uint8_t)(p.motorSpeed));
  LoRa.write((uint8_t)(p.aeleronR>>8));
  LoRa.write((uint8_t)(p.aeleronR));
  LoRa.write((uint8_t)(p.aeleronL>>8));
  LoRa.write((uint8_t)(p.aeleronL));
  return LoRa.endPacket();
}

Packet LoRaRadio::receiveCommand(){
  uint8_t header = LoRa.read();
  //printHeaderCompare(header);
  Packet p;
  p.nbMsg = LoRa.read();
  p.t = ((uint16_t)(LoRa.read()) << 8 | LoRa.read());
  p.motorSpeed = ((uint16_t)(LoRa.read()) << 8 | LoRa.read());
  p.aeleronR = ((uint16_t)(LoRa.read() << 8) | LoRa.read());
  p.aeleronL = ((uint16_t)(LoRa.read() << 8) | LoRa.read());
  return p;
}

void LoRaRadio::onReceive(void(*callback)(int)){
}

int LoRaRadio::parsePacket(){
  return LoRa.parsePacket();
}

void LoRaRadio::printHeaderCompare(uint8_t& header){
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
  Serial.print(" ");
}

#ifdef LORAINT
//LoRa::LoRa.onReceive(receiveCommand); What to do?
#endif
