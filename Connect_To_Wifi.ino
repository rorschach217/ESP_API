void Connect_To_Wifi(){
  Serial.println("\nChecking Hardware and WiFi Connections !");
  Serial.print("Please Wait");
  (checkESP()) ? (!resetESP()) ? Serial.println("\nReset Fail") : NULL : NULL;
  while(!checkWiFiStatus()) {
    if(connectWifi()){
      Serial.print("\nConnected to Wifi !");
      wifiConnected = true;
      break;
    }else{
      Serial.print(".");
    }
  }    
}

