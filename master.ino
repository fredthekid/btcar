//Remote (Master Bluetooth)

#include <SoftwareSerial.h>

SoftwareSerial Master(9,10); // 9 = RX, 10 = TX

void btinit()
{
  boolean test = true; //used for t
  
  //init comp to uno serial
  Serial.begin(115200); //serial between computer and uno
  Serial.println("Initializing computer to UNO connection...");
  while(!Serial){;} //wait for connection
  Serial.println(":)");
  
  //init uno to bt serial
  Master.begin(9600); //serial between uno and bluetooth
  Serial.println("Initializing master...");
  while(!Master){;} //wait for connection
  Serial.println(":)");
  
  //config bluetooth for connection
  Master.print("$$$"); //enter command mode
  delay(50);
  Master.println("SM,1"); // set to master mode
  delay(50);
  Master.println("I,10"); // find slave
  delay(50);
  
  
  
  Serial.println("SR,asdf"); //store slave address
  Serial.println("C"); //connect to slave
  
  
  Serial.println("---");//exit command mode
}
