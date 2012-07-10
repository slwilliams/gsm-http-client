
/*
	GSMInterface.cpp - Library for interfacing with the gsm module
	Created by Scott Williams, 05/07/2012
*/
#include "Arduino.h"
#include "string.h"
#include "SerialInterface.h"
#include "GSMInterface.h"

//Can't seem to call this serialInterface for some reason
SerialInterface *serialinterface;
String pdpContext, userPassword;
byte gsmResetPin;


GSMInterface::GSMInterface()
{	
}

void GSMInterface::initialise(SerialInterface *_serialInterface, String _pdpContext, String _userPassword, byte _gsmResetPin)
{
	serialinterface = _serialInterface;
	pdpContext = _pdpContext;
	userPassword = _userPassword;
	gsmResetPin = _gsmResetPin;
	resetGSM();
	registerGPRS_GSM();
	setUpPDP();
}

bool GSMInterface::sendPacket(String server, int port, String packet) 
{
	if(packet.length() > 990)
		return false;
	
	while(1)
	{
		if(!openTCPSocket(server, port))
		{
			resetGSM();			
			registerGPRS_GSM();
			setUpPDP();
			continue;
		}
		
		int packetSize = packet.length()-1;
		serialinterface->printToGSM("AT+SDATATSEND=1," + String(packetSize));
	  	serialinterface->writeToGSM(13);
	  	delay(100);
		serialinterface->printToGSM(packet);
		delay(100);	
		
		if(serialinterface->pollForResponseFromCommand("", "OK", false))
		{		
			serialinterface->printlnToDebug("[Data sent]");
			closeSocket();		
			return true;			
		}
		
		resetGSM();		
		registerGPRS_GSM();
		setUpPDP();		
	}
}

void GSMInterface::registerGPRS_GSM()
{
	while(1)
	{
		serialinterface->printlnToDebug("[GPRS Attaching]");	
		if(serialinterface->pollForResponseFromCommand("AT+CGATT?", "+CGATT: 1", true))
			break;
		else
			resetGSM();	
	}
}

void GSMInterface::setUpPDP()
{
	while(1)
	{	
		serialinterface->pollForResponseFromCommand("AT+CGDCONT=1," + pdpContext, "OK", false);
		serialinterface->pollForResponseFromCommand("AT+CGPCO=0," + userPassword + ", 1", "OK", false);		    
		serialinterface->printlnToDebug("[Activating PDP]");
		if(serialinterface->pollForResponseFromCommand("AT+CGACT=1,1", "OK", false))
		{
			break;
		}
		else
		{
			resetGSM();			
			registerGPRS_GSM();
		}
	}
}

bool GSMInterface::openTCPSocket(String server, int port)
{
	serialinterface->pollForResponseFromCommand("AT+SDATACONF=1,\"TCP\",\"" + server + "\"," + port, "OK", false);	
	serialinterface->pollForResponseFromCommand("AT+SDATASTART=1,1", "OK", false);	
	if(serialinterface->pollForResponseFromCommand("AT+SDATASTATUS=1", "+SOCKSTATUS:  1,1", true))
	{
		serialinterface->printlnToDebug("[TCPSocketOpen]");	
		return true;
	}
	else
	{
		return false;
	}
}

void GSMInterface::closeSocket()
{
	serialinterface->printlnToGSM("AT+SDATASTART=1,0");	
	delay(200);
	serialinterface->printlnToDebug("[TCPSocketClosed]");	
}

void GSMInterface::resetGSM()
{
	pinMode(gsmResetPin, OUTPUT);
	digitalWrite(gsmResetPin, LOW);
	delay(50);
	digitalWrite(gsmResetPin, HIGH);
	delay(500);
	delay(5000);
}
