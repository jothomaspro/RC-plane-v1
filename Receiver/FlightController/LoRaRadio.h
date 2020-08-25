/*
 * LoRaRadio.h
 *
 *  Created on: 23 ao�t 2020
 *      Author: jthom
 */

#ifndef LORARADIO
#define LORARADIO
#define LORAINT

#include <LoRa.h>
#include "Packet.h"

class LoRaRadio{
public:
	LoRaRadio(uint8_t csPin, uint8_t rstPin, uint8_t irqPin, byte destination, byte localAddress);
	bool begin(long freq = 433E6);
	bool sendMessage(String message);
	bool sendCommand(Packet p);
  void receiveCommand(int i);
  void onReceive(void(*callback)(int));
private:
	byte _localAddress;
	byte _destination;
};

#endif
