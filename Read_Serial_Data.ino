boolean read_until_ESP(char keyword[]){
  //Serial.println();
  char data_in[200];
  char *search;  
  byte i=0;
  byte data_length = 0;  
  while(Serial1.available()){
    data_in[i]=Serial1.read();
    //Serial.print(data_in[i]);
    i++;
    data_length++;
    delay(30);
  }    
  //Serial.println();
  search = strstr(data_in, keyword);
  //Serial.print("Search : ");
  //Serial.println(search);
  if (search != NULL)
  {
     return true;
  }
  else
  {
     return false;
  }
}

boolean read_API(char keyword[]){
  Serial.println();
  char data_in[200];
  char *search;  
  byte i=0;
  byte data_length = 0;  
  while(Serial1.available()){
    data_in[i]=Serial1.read();
    Serial.print(data_in[i]);
    i++;
    data_length++;
    delay(30);
  }    
  Serial.println();
  search = strstr(data_in, keyword);
  if (search != NULL)
  {
    int count = 100;
    while(Serial1.available() && count > 0){
      data_in[i]=Serial1.read();
      Serial.print(data_in[i]);
      i++;
      delay(100);
      count--;
    }
    return true;
  }
  else
  {
    return false;
  }       
}

