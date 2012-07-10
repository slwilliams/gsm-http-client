/*
	HTTPPost.cpp - Library for sending HTTP get/post over GPRS
	Created by Sam Hughes-Gage, Adrian Wragg and Scott Williams 27/06/2012
*/
#include "Arduino.h"
#include "string.h"
#include "HTTPPost.h"
#include "SerialInterface.h"
#include "GSMInterface.h"
#include "Sender.h"

SerialInterface serialInterface;
GSMInterface gsmInterface;
Sender* sender;

HTTPPost::HTTPPost()
{	
}

void HTTPPost::initialise(HardwareSerial *_USBSerial, HardwareSerial *_GSMSerial, String pdpContext, String userPassword, byte gsmResetPin) 
{
	serialInterface.initialise(_USBSerial, _GSMSerial);	
	gsmInterface.initialise(&serialInterface, pdpContext, userPassword, gsmResetPin);	
	sender = &gsmInterface;
	serialInterface.printlnToDebug("[Initialise Finished]");
}

bool HTTPPost::post(String server, int port, String path, String content, String contentType)
{
	String packet = "POST " + path + " HTTP/1.0\r\n" + contentType + "\r\nContent-Length: " + String(content.length()) + "\r\n\r\n" + content + "\r\n" + (char)26;	
	return sender->sendPacket(server, port, packet);
}

bool HTTPPost::get(String server, int port, String path, String content)
{
	String packet = "GET " + path + content + " HTTP/1.0\r\nConnection: Keep-Alive\r\n\r\n" + (char)26;	
	return sender->sendPacket(server, port, packet);
}
