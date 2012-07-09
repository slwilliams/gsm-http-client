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
		void initialise(SerialInterface *_serialInterface, String pdpContext, String userPassword, byte _gsmResetPin);
		bool sendPacket(String server, int port, String packet);
	private:	
		void registerGPRS_GSM();
		void setUpPDP();
		bool openTCPSocket(String server, int port);
		void resetGSM();
		void closeSocket();
		SerialInterface *interface;
		String pdpContext;
		String userPassword;
		byte gsmResetPin;
};
#endif
