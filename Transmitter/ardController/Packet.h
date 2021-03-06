/*
 * Packet.h
 *
 *  Created on: 23 ao�t 2020
 *      Author: jthom
 */

#ifndef PACKET
#define PACKET

struct Packet{
	uint16_t motorSpeed;
	uint16_t aeleronR;
	uint16_t aeleronL;
};

inline bool operator!=(Packet p1, Packet p2){
  if((p1.motorSpeed == p2.motorSpeed) && (p1.aeleronR == p2.aeleronR) && (p1.aeleronL == p2.aeleronL)) return false;
  return true;
}

inline uint16_t difference(Packet p1, Packet p2){
  return abs(p1.motorSpeed - p2.motorSpeed) + abs(p1.aeleronR - p2.aeleronR) + abs(p1.aeleronL - p2.aeleronL);
}

#endif
