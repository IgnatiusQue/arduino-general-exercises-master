
 

void setup() {
  
    Serial.begin(9600);
    Serial.println("Test");
       Serial.println("");

 String raw ="0affaa40";
 Serial.println(raw.length());
 
 for(int i=0;i<raw.length();i+= 2){
 // Serial.println(i);
 char f[]={raw.charAt(i),raw.charAt(i+ 1)};
   Serial.print(f); 
  Serial.print(" "); 
   Serial.print(StrToHex(f)); 
  Serial.println(" "); 
  }

//   int a=64;         
//      Serial.println(char(a));
//   char* b="@";
//    Serial.println(byte(b[0]));
//Serial.println (StrToHex("0A"));
  
}

void loop() {

}

int StrToHex(char str[])
{
  return (int) strtol(str, 0, 16);
}
 
   
