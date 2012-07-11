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
  switch(post.post("ec2-50-112-222-224.us-west-2.compute.amazonaws.com", 8161, "/api/bank/action/deposit.php", "bankid=8&amount=1.00", "Content-Type: application/x-www-form-urlencoded"))
  {
    case 200: Serial.println("Data successfully sent");
              break;
    case 500: Serial.println("Couldn't open TCP socket");
              break;
    case 501: Serial.println("Data not successfully sent");
              break;
  }
  delay(5000);
}
