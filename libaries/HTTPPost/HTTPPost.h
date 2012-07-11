/*
	HTTPPost.h - Library for sending HTTP post over GPRS
	Created by Sam Hughes-Gage, Adrian Wragg and Scott Williams 27/06/2012
*/
#ifndef HTTPPost_h
#define HTTPPost_h

#include "Arduino.h"
#include "string.h"

class HTTPPost 
{
	public:
		HTTPPost();
		int initialise(HardwareSerial *_usbSerial, HardwareSerial *_GSMSerial, String pdpContext, String userPassword, byte gsmResetPin);
		int post(String server, int port, String path, String content, String contentType);
		int get(String server, int port, String path, String content);
};
#endif
