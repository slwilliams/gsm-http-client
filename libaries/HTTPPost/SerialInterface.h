/*
	SerialInterface.h - Library for interfacing with serial ports
	Created by Scott Williams, 05/07/2012
*/
#ifndef SerialInterface_h
#define SerialInterface_h

#include "Arduino.h"
#include "string.h"

class SerialInterface 
{
	public:
		SerialInterface();	
		void initialise(HardwareSerial *&_usbSerial, HardwareSerial *&_GSMSerial);
		bool pollForResponseFromCommand(String command, String expectedResponse, bool resendCommand);
		void softReset();
		void printToDebug(String data);
		void printToDebug(char c);
		void printlnToDebug(String data);
		void printToGSM(String data);
		void printToGSM(char c);
		void writeToGSM(int c);
		void printlnToGSM(String data);
		char readDebug();
		char readGSM();
		bool GSMAvailable();
	private:	
		HardwareSerial *usbSerial;
		HardwareSerial *GSMSerial;		
};
#endif
