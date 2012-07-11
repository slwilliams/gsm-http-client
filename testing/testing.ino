#include <HTTPPost.h>
#include <string.h>

HTTPPost post;

void setup() 
{  
  switch(post.initialise(&Serial, &Serial1, "\"IP\",\"pp.vodafone.co.uk\"", "\"web\",\"web\"", (byte)31))
  {
    case 200:  Serial.println("Gprs connected");
               break;
    case 504:  Serial.println("Couldn't connect to gsm network");
               break;
    case 503:  Serial.println("Couldn't activate pdp context");
               break;
  }
}

void loop() 
{
  //this still works
  switch(post.post("scottwilliams.org.uk", 80, "/test.php", "data=roflcopyers", "Content-Type: application/x-www-form-urlencoded"))
  {
    case 200: Serial.println("Data successfully sent");
              break;
    case 500: Serial.println("Couldn't open TCP socket");
              break;
    case 501: Serial.println("Data not successfully sent");
              break;
  }
  
  //new
  post.openTCPSocket("scottwilliams.org.uk", 80);
  delay(100);
  //Serial1.flush() probably does the same thing
  while(Serial1.available())
  {
    Serial1.read();
  }
    
  for(int i = 0; i < 30; i ++)
  {
    //you could try changing these
    delay(100);
    
    while(!post.sendRawPostPacket("scottwilliams.org.uk", 80, "/posttest.php", "data="+String(i)+"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||", "Content-Type: application/x-www-form-urlencoded"))
    {
       post.openTCPSocket("scottwilliams.org.uk", 80);
       delay(100);
    }
  }
  
  post.closeTCPSocket();
  
  while(1){}
}
