#include <ESP8266WiFi.h>
 
 

const char WiFiAPPSK[] = "sparkfun"; 
WiFiServer internalServer(80);                   


void setup() 
{
  Serial.begin(115200);              
   delay(10);
   
  setupWiFi();
  internalServer.begin();
 
}
void loop() 
{
 captureInternalRequest() ;
}
void captureInternalRequest() { 
  WiFiClient internalWifiServer_client = internalServer.available();  // Check if a client has connected
  if (!internalWifiServer_client)  {return;}
     
    

  Serial.println(">User Connected<");

  String req = internalWifiServer_client.readStringUntil('\r');// Read the first line of the request
 
  Serial.println(req);
   
  internalWifiServer_client.flush();

  // Match the request
  int val = -1;                            // 'val' to keep track of both the
                                           // request type (read/set) and value if set.
  if (req.indexOf("/led/0") != -1)
    val = 0; // Will write LED low
  else if (req.indexOf("/led/1") != -1)
    val = 1; // Will write LED high
  else if (req.indexOf("/read") != -1)
    val = -2;                              // Will print pin reads
                                           // Otherwise request is invalidt


  internalWifiServer_client.flush();

  String s = "HTTP/1.1 200 OK\r\n";        // the common header:
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";

  if (val >= 0)                            // Setting LED?
  {s += "Request.";
   s += val;
   s+="<br> ";} else
  {
    s += "Invalid Request.<br> Try /led/1, /led/0, or /read.";
  }

  s += "</html>\n";

  internalWifiServer_client.print(s);                         // Send the response to the client
  delay(1);
  Serial.println(F("Client disonnected"));

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
  }
void setupWiFi(){
  WiFi.mode(WIFI_AP);

  // Append the last two bytes of the MAC (HEX'd) to string to make unique
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "INUUC" + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, AP_NameString.length() + 1, 0);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}


