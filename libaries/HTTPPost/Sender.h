/*
	Sender.h - Library for interfacing with serial ports
	Created by Scott Williams, 06/07/2012
*/
#ifndef Sender_h
#define Sender_h

#include "string.h"

class Sender 
{
	public:
		virtual bool sendPacket(String server, int port, String packet) = 0;
};
#endif
