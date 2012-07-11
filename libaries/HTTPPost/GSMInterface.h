/*
	GSMInterface.h - Library for interfacing with the gsm module
	Created by Scott Williams, 05/07/2012
*/
#ifndef GSMInterface_h
#define GSMInterface_h

#include "Arduino.h"
#include "string.h"
#include "Sender.h"
#include "SerialInterface.h"

class GSMInterface:public Sender
{
	public:
		GSMInterface();	
		int initialise(SerialInterface *_serialInterface, String pdpContext, String userPassword, byte _gsmResetPin);
		int sendPacket(String server, int port, String packet);
		bool openTCPSocket(String server, int port);
		bool sendRawPacket(String packet);
		void closeTCPSocket();
	private:	
		bool registerGPRS_GSM();
		bool setUpPDP(String pdpContext, String userPassword);
		void resetGSM();
		SerialInterface *interface;
		String pdpContext;
		String userPassword;
		byte gsmResetPin;
};
#endif
