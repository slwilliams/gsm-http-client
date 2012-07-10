#include <HTTPPost.h>
#include <string.h>

HTTPPost post;

void setup() 
{  
  post.initialise(&Serial, &Serial1, "\"IP\",\"pp.vodafone.co.uk\"", "\"web\",\"web\"", (byte)31);
}

void loop() 
{
//  post.get("108.174.49.28", 80, "/test.php", "data1=test&data2=test2");
//  delay(100);
  post.post("ec2-50-112-222-224.us-west-2.compute.amazonaws.com", 8161, "/api/bank/action/deposit.php", "bankid=8&amount=1.00", "Content-Type: application/x-www-form-urlencoded");
  delay(2000);
}
