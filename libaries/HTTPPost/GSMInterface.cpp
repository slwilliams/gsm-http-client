
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

int GSMInterface::initialise(SerialInterface *_serialInterface, String _pdpContext, String _userPassword, byte _gsmResetPin)
{
	serialinterface = _serialInterface;
	pdpContext = _pdpContext;
	userPassword = _userPassword;
	gsmResetPin = _gsmResetPin;
	resetGSM();
	if(!registerGPRS_GSM())
		return 504;
	if(!setUpPDP())
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
		closeSocket();
		return 200;
	}
	else
	{
		closeSocket();
		return 501;
	}
}

int GSMInterface::sendPacketChunked(String server, int port, String path, String content, String contentType) 
{
	Serial.println("Calculating chunks");
	byte numChunks = ceil(content.length()%(999-(47 + String(port).length() + path.length() + contentType.length() + String(content.length()).length())));
	Serial.println(numChunks);
	
	while(1){}
	
	if(!openTCPSocket(server, port))
		return 500;
		
/*	while(1)
	{
		int packetSize = packet.length()-1;
		serialinterface->printToGSM("AT+SDATATSEND=1," + String(packetSize));
		serialinterface->writeToGSM(13);
		delay(100);
		serialinterface->printToGSM(packet);
		delay(100);	
		
		if(serialinterface->pollForResponseFromCommand("", "OK", false))
		{
			serialinterface->printlnToDebug("Sent chunk");
			//numSent ++;
		}
		else
		{
			closeSocket();
			return 501;
		}
	}*/

}

bool GSMInterface::registerGPRS_GSM()
{
	serialinterface->printlnToDebug("[GPRS Attaching]");	
	return serialinterface->pollForResponseFromCommand("AT+CGATT?", "+CGATT: 1", true);
}

bool GSMInterface::setUpPDP()
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
	/*Serial1.flush();
	digitalWrite(31, LOW);
	pinMode(31, OUTPUT);
	delay(3000);	
	pinMode(31, INPUT);
	delay(5000);*/
}
