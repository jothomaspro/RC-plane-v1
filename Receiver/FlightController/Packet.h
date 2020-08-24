/*
 * Packet.h
 *
 *  Created on: 23 ao�t 2020
 *      Author: jthom
 */

#ifndef PACKET
#define PACKET

struct Packet{
	uint8_t motorSpeed;
	uint8_t aeleronR;
	uint8_t aeleronL;
};

inline bool operator!=(Packet p1, Packet p2){
  if((p1.motorSpeed == p2.motorSpeed) && (p1.aeleronR == p2.aeleronR) && (p1.aeleronL == p2.aeleronL)) return false;
  return true;
}

#endif
