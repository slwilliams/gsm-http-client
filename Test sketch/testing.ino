#include <HTTPPost.h>
#include <string.h>

HTTPPost post;

void setup() 
{  
  //initialise takes: usbserial(always &Serial), gsm serial (depending on the pins you've used i.e. tx2, rx2 = *Serial2 etc.),
  //apn for your sim (always have IP), username and pass for apn, the pin wired to the gsm rst pin.
  //a list of apns for specfifc sims: 
  /*
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
  */
  post.initialise(&Serial, &Serial1, "\"IP\",\"pp.vodafone.co.uk\"", "\"web\",\"web\"", (byte)31);
}

void loop() 
{
  String data = String(random(1000));
  Serial.println("Sending: " + data);
  post.post("108.174.49.28", 80, "/recorder.php", data);
}
