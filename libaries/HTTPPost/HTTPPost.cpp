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

int HTTPPost::initialise(HardwareSerial *_USBSerial, HardwareSerial *_GSMSerial, String pdpContext, String userPassword, byte gsmResetPin) 
{
	serialInterface.initialise(_USBSerial, _GSMSerial);	
	int response = gsmInterface.initialise(&serialInterface, pdpContext, userPassword, gsmResetPin);	
	sender = &gsmInterface;
	return response;
}

bool HTTPPost::openTCPSocket(String server, int port)
{
	return sender->openTCPSocket(server, port);
}

void HTTPPost::closeTCPSocket()
{
	sender->closeTCPSocket();
}

bool HTTPPost::sendRawPostPacket(String host, int port, String path, String data, String contentType)
{
	String packet = "POST " + path + " HTTP/1.1\r\nHost: " + host + ":" + String(port) + "\r\n" + contentType + "\r\nContent-Length: " + String(data.length()) + "\r\n\r\n" + data + "\r\n" + (char)26;	
	return sender->sendRawPacket(packet);
}

int HTTPPost::post(String server, int port, String path, String content, String contentType)
{
	String packet = "POST " + path + " HTTP/1.1\r\nHost: " + server + ":" + String(port) + "\r\n" + contentType + "\r\nContent-Length: " + String(content.length()) + "\r\n\r\n" + content + "\r\n" + (char)26;	
	return sender->sendPacket(server, port, packet);
}

int HTTPPost::get(String server, int port, String path, String content)
{
	String packet = "GET " + path + + "?" + content + " HTTP/1.0\r\n\r\n" + (char)26;	
	return sender->sendPacket(server, port, packet);
}
