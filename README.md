gsm-http-client
===============

GSM HTTP client for Arduino.


Installation:

Copy the libaries folder into /home/user/sketchbook/ a restart of the arduino IDE may be necessary.

The test sketch shows the main functionality of the libary - it can send data via POST or GET. The GET request uses the variable data for the data being transmitted i.e. the url sent is: http://108.174.49.28/test.php?data=1234
You can supply either an IP address or an URL for the server.

initialise takes the following parameters; the memory address of the usb serial (always &Serial), the memory address of the gsm serial (this will differ depending on the pins used to connect the module e.g. tx2,rx2 -> &Serial2), apn, apn username and password, pin number connected to the gsm reset pin.

Currently the test sketch is set to use the vodafone network, but here are some common apn's for other networks:

	Vodafone
    APN (contract): internet
    APN (PAYG): pp.vodafone.co.uk
    Username: web
    Password: web
    
    Orange
    APN: orangeinternet 
    Username: leave blank
    Password: leave blank
    
    O2 
    APN (contract): mobile.o2.co.uk
    APN (PAYG): m-bb.o2.co.uk
    Username: web
    Password: web
    
    T-Mobile
    APN: general.t-mobile.uk 
    Username: leave blank
    Password: leave blank
    
    Three
    APN: 3internet 
    Username: leave blank 
    Password: leave blank
    
    Tesco Mobile (uses the O2 network)
    APN: prepay.tesco-mobile.com
    Username: tescowap
    Password: password
    
    Virgin Mobile (uses the T-Mobile network)
    APN: goto.virginmobile.uk
    Username: user
    Password: leave blank
    
    BT Mobile (uses the Vodafone network)
    APN: btmobile2.bt.com
    Username: bt
    Password: bt
    
    ASDA Mobile (uses the Vodafone network)
    APN: asdamobiles.co.uk
    Username: web
    Password: web


