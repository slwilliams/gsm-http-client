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
		virtual int sendPacket(String server, int port, String packet) = 0;
		virtual int sendPacketChunked(String server, int port, String path, String content, String contentType) = 0;
};
#endif
