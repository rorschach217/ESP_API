 #include <string.h>
// EspDebug - Test sketch for ESP8266 module
#include <stdlib.h>
// emulate Serial1 if not present
#ifndef HAVE_HWSERIAL1
  #include "SoftwareSerial.h"
  SoftwareSerial Serial1(6, 7); // RX, TX
#endif

boolean espStatus = false;
boolean wifiConnected = false;
boolean serverConnected = false;
int serverStatus = 0;

void setup()
{
  Serial.begin(9600); // serial port used for debugging
  Serial1.begin(9600);  // your ESP's baud rate might be different      
  Serial.print("Setting Baud Rate to 9600");
  while(!lowerBaudSet()){
    Serial.print(".");
  }
  Connect_To_Wifi();
}
 
void loop()
{
  if(wifiConnected && !serverConnected) {    
    checkServerStatus();
    if(serverStatus) {
      actionOnServerStatus(serverStatus);
    }else{
      Serial.print("\nConnecting To Server");
      espStatus = false;
      Serial1.println("AT+CIPMUX=1");
      delay(3000);
      espStatus = read_until_ESP("OK");
      if(espStatus){
        while(!connectToServer()){
          Serial.print(".");
        }
        serverConnected = true;
        Serial.println("\nConnected To Server");
        while(!callApi()){
          Serial.print(".");
        }        
      }
    }
  }else{
    Serial.print("\nWifi Connecction or Server Connection Failed");
    Connect_To_Wifi();
  }
  
  /*
   if(Serial1.available())  // check if the ESP is sending a message
  {
    while(Serial1.available())
    {
      int c = Serial1.read(); // read the next character
      Serial.write((char)c);  // writes data to the serial monitor      
    }
  }
 
  if(Serial.available())
  {
    // wait to let all the input command in the serial buffer
    delay(10);

    // read the input command in a string
    String cmd = "";
    while(Serial.available())
    {
      cmd += (char)Serial.read();
    }

    // print the command and send it to the ESP
    Serial.println();
    Serial.print(">>>> ");
    Serial.println(cmd);

    // send the read character to the ESP
    Serial1.print(cmd);
  }
  */
}
