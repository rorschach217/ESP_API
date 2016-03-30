boolean checkESP() {
  espStatus = false;
  Serial1.println("AT");  
  delay(1000);
  espStatus = read_until_ESP("OK");  
  if(espStatus){    
    return true;
  }
  return false;
}

boolean resetESP() {
  espStatus = false;
  Serial1.println("AT+RST");  
  delay(1000);
  espStatus = read_until_ESP("OK");
  delay(1000);
  if(espStatus){    
    return true;
  }
  return false;
}

boolean checkWiFiStatus() {
  delay(1000);
  espStatus = false;
  Serial1.println("AT+CIFSR");  
  delay(1000);
  espStatus = read_until_ESP("192.168.");
  if(espStatus){
    Serial.print("\nConnected to Wifi !");
    wifiConnected = true;
    return true;
  }
  return false;
}

boolean connectWifi(){
  espStatus = false;
  Serial1.println("AT+CWMODE=1");
  espStatus = read_until_ESP("OK");
  if(!espStatus){
    return false;
  }
  espStatus = false;
  Serial1.println("AT+CWJAP=\"Taneja\",\"taneja1993\"");
  delay(1000);
  espStatus = read_until_ESP("CONNECTED");  
  delay(1000);  
  if(espStatus){
    return true;
  }
  return false;
}

void checkServerStatus() {
  espStatus = false;
  Serial1.println("AT+CIPSTATUS");
  delay(2000);
  if(read_until_ESP("STATUS:2")){
    serverStatus = 2;
  }else if(read_until_ESP("STATUS:3")){
    serverStatus = 3;
  }else if(read_until_ESP("STATUS:4")){
    serverStatus = 4;
  }else{
    serverStatus = 0;
  }
}

boolean connectToServer() {  
  espStatus = false;
  Serial1.println("AT+CIPSTART=4,\"TCP\",\"www.google.com\",80");
  delay(5000);
  espStatus = read_until_ESP("4,CONNECT");  
  if(espStatus){
    return true;
  }   
  return false;
}

void actionOnServerStatus(int serverStatus){
  espStatus = false;
  //Serial.println("status in function");  
  //Serial.println(serverStatus);
  switch(serverStatus){
    case 2:
      Serial.print("\nConnecting To Server");  
      Serial1.println("AT+CIPCLOSE");  
      delay(1000);
      espStatus = read_until_ESP("OK");
      if(espStatus) {
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
      break;
    case 3:
      serverConnected = true;
      Serial.println("\nConnected To Server");  
      while(!callApi()){
        Serial.print(".");
      }
      break;
    case 4:
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
      break;
    default:
      Serial1.println("AT+CIPCLOSE");  
      delay(1000);
      espStatus = read_until_ESP("OK");
      break;
  }
}

boolean callApi() {
  espStatus = false;
  Serial1.println("AT+CIPSEND=4,39");
  Serial1.println("GET /about HTTP/1.1\r\nHost: google.com\r\n\r\n");
  delay(5000);
  espStatus = read_until_ESP("SEND OK");
  read_API();
  delay(1000);
  if(espStatus){
    return true;
  }   
  return false;
}

boolean lowerBaudSet(){
  espStatus = false;
  Serial1.println("AT+UART_DEF=9600,8,1,0,0");
  delay(1000);
  espStatus = read_until_ESP("OK");
  delay(1000);
  if(espStatus){
    return true;
  }   
  return false;
}

