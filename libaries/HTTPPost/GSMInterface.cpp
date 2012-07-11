
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
byte gsmResetPin;


GSMInterface::GSMInterface()
{	
}

int GSMInterface::initialise(SerialInterface *_serialInterface, String pdpContext, String userPassword, byte _gsmResetPin)
{
	serialinterface = _serialInterface;
	gsmResetPin = _gsmResetPin;
	resetGSM();
	if(!registerGPRS_GSM())
		return 504;
	if(!setUpPDP(pdpContext, userPassword))
		return 503;
	else
		return 200;
}

int GSMInterface::sendPacket(String server, int port, String packet) 
{
	if(!openTCPSocket(server, port))
		return 500;
		
	int packetSize = packet.length()-1;
	serialinterface->printToGSM("AT+SDATATSEND=1," + String(packetSize));
	serialinterface->writeToGSM(13);
	delay(100);
	serialinterface->printToGSM(packet);
	
	if(serialinterface->pollForResponseFromCommand("", "OK", false))
	{
		delay(100);
		closeTCPSocket();
		return 200;
	}
	else
	{
		closeTCPSocket();
		return 501;
	}
}

bool GSMInterface::sendRawPacket(String packet) 
{	
	int packetSize = packet.length()-1;
	serialinterface->printToGSM("AT+SDATATSEND=1," + String(packetSize));
	serialinterface->writeToGSM(13);
	delay(100);
	Serial.println(packet);
	serialinterface->printToGSM(packet);
	delay(100);	
	
	if(serialinterface->pollForResponseFromCommand("", "OK", false))
	{
		return true;
	}
	else
	{
		closeTCPSocket();
		return false;
	}
}

bool GSMInterface::registerGPRS_GSM()
{
	serialinterface->printlnToDebug("[GPRS Attaching]");	
	return serialinterface->pollForResponseFromCommand("AT+CGATT?", "+CGATT: 1", true);
}

bool GSMInterface::setUpPDP(String pdpContext, String userPassword)
{
	if(!serialinterface->pollForResponseFromCommand("AT+CGDCONT=1," + pdpContext, "OK", false))
		return false;
	if(!serialinterface->pollForResponseFromCommand("AT+CGPCO=0," + userPassword + ", 1", "OK", false))
		return false;
	serialinterface->printlnToDebug("[Activating PDP]");
	return serialinterface->pollForResponseFromCommand("AT+CGACT=1,1", "OK", false);	
}

bool GSMInterface::openTCPSocket(String server, int port)
{
	delay(200);
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

void GSMInterface::closeTCPSocket()
{
	serialinterface->printlnToGSM("AT+SDATASTART=1,0");	
	delay(200);
	serialinterface->printlnToDebug("[TCPSocketClosed]");	
}

void GSMInterface::resetGSM()
{
	/*Serial1.flush();
	digitalWrite(31, LOW);
	pinMode(31, OUTPUT);
	delay(3000);	
	pinMode(31, INPUT);
	delay(5000);*/
}
