
 

void setup() {
  
    Serial.begin(9600);
    Serial.println("Test");
       Serial.println("");
         
     
   int a=64;         
      Serial.println(char(a));
   char* b="@";
    Serial.println(byte(b[0]));

  Serial.println (StrToHex("0A"));
}

void loop() {

}

int StrToHex(char str[])
{
  return (int) strtol(str, 0, 16);
}
 
   
