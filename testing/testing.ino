#include <HTTPPost.h>
#include <string.h>

HTTPPost post;

void setup() 
{  
  post.initialise(&Serial, &Serial1, "\"IP\",\"pp.vodafone.co.uk\"", "\"web\",\"web\"", (byte)31);
}

void loop() 
{
  post.get("108.174.49.28", 80, "/test.php", "data1=test&data2=test2");
  delay(100);
  post.post("scottwilliams.org.uk", 80, "/posttest.php", "data=thisistest1234&data2=this", "Content-Type: application/x-www-form-urlencoded");
  delay(100);
}