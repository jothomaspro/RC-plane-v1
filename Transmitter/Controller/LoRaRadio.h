/*
 * LoRaRadio.h
 *
 *  Created on: 23 ao�t 2020
 *      Author: jthom
 */

#ifndef LORARADIO
#define LORARADIO

#include <LoRa.h>
#include "packet.h"

class LoRaRadio{
public:
	LoRaRadio(uint8_t csPin, uint8_t rstPin, uint8_t irqPin, byte destination, byte localAddress);
	bool begin(long freq = 433E6);
	bool sendMessage(String message);
	bool sendCommand(uint8_t motorSpeed, uint8_t aeleronR, uint8_t aeleronL, byte destination = _destination);
  bool receiveCommand();
private:
	byte _localAddress;
	byte _destination;
};



#endif
