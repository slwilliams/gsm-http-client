#include <HTTPPost.h>
#include <string.h>

HTTPPost post;

void setup() 
{  
  post.initialise(&Serial, &Serial1, "\"IP\",\"pp.vodafone.co.uk\"", "\"web\",\"web\"", (byte)31);
}

void loop() 
{
  String data = String(random(1000));
  Serial.println("Sending: " + data);
  post.post("108.174.49.28", 80, "/recorder.php", data);
  delay(100);
  post.post("scottwilliams.org.uk", 80, "/posttest.php", "data=thisistest1234");
}
