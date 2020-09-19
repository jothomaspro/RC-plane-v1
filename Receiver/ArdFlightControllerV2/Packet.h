/*
 * Packet.h
 *
 *  Created on: 23 ao�t 2020
 *      Author: jthom
 */

#ifndef PACKET
#define PACKET

struct Packet{
  byte nbMsg;
  uint32_t t;
	uint16_t motorSpeed;
	uint16_t aeleronR;
	uint16_t aeleronL;
};

inline bool operator!=(Packet p1, Packet p2){
  if((p1.motorSpeed == p2.motorSpeed) && (p1.aeleronR == p2.aeleronR) && (p1.aeleronL == p2.aeleronL)) return false;
  return true;
}

inline String toString(volatile Packet& p){
  return (String)p.nbMsg + "," + (String)p.motorSpeed + "," + (String)p.aeleronR + "," + (String)p.aeleronL + "," + (String)p.t; 
}

inline String toDataString(volatile Packet& p){
  return (String)p.nbMsg + "," + (String)p.motorSpeed + "," + (String)p.aeleronR + "," + (String)p.aeleronL;
}

#endif
