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

void LoRaRadio::begin(long freq){
	if (!LoRa.begin(freq)) {             // initialize ratio at 915 MHz
	Serial.println("LoRa init failed. Check your connections.");
	return false
	}
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

bool LoRaRadio::sendCommand(uint8_t motorSpeed, uint8_t aeleronR, uint8_t aeleronL, byte destination){
	byte header = (destination << 4) + _localAddress;
	LoRa.beginPacket();
	LoRa.write(header);
	loRa.write(motorSpeed);
	loRa.write(aeleronR);
	LoRa.write(aeleronL);
	return LoRa.endPacket();
}

bool LoRaRadio::receiveCommand();
