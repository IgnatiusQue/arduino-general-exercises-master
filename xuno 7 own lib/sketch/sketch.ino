#include <ml.h>

#include <EtherCard.h>
 
#define STATIC 1  // set to 1 to disable DHCP (adjust myip/gwip values below)

#if STATIC
// ethernet interface ip address
static byte myip[] = { 
  192,168,1,200 };
// gateway ip address
static byte gwip[] = { 
  192,168,1,1 };
#endif

// ethernet mac address - must be unique on your network
static byte mymac[] = { 
  0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[500]; // tcp/ip send and receive buffer
BufferFiller bfill;

ml ml;
 
void setup(){
 

  Serial.begin(9600);
  Serial.println("\n[backSoon]");
 
 if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
 Serial.println( "Failed to access Ethernet controller");
#if STATIC
  ether.staticSetup(myip, gwip);
#else
  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");
#endif

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  
}
const char http_OK[] PROGMEM =
"HTTP/1.0 200 OK\r\n"
"Content-Type: text/html\r\n"
"Pragma: no-cache\r\n\r\n";

const char http_Found[] PROGMEM =
"HTTP/1.0 302 Found\r\n"
"Location: /\r\n\r\n";

const char http_Unauthorized[] PROGMEM =
"HTTP/1.0 401 Unauthorized\r\n"
"Content-Type: text/html\r\n\r\n"
"<h1>401 Unauthorized</h1>";

void homePage(){
   
  bfill.emit_p(PSTR( "$F"
"<title>Ethercard LED</title>" 
 "Test <a href=\"?reg=12345\">test</a><br>"),
  http_OK ); 
 
}

void deviceInfo(){
 String ip="123";
 int s[] = {4};
 
  bfill.emit_p(PSTR("$F" 
  "<title>iNuuk Module Info site</title>" 
    "myIp=$D.$D.$D.$D\r\n"
    "gwIp=$D.$D.$D.$D"
    ""), http_OK ,myip[0],myip[1],myip[2],myip[3],gwip[0],gwip[1],gwip[2],gwip[3]); 
 
 
}

void loop(){
    ml.blinking(7,700);
  // wait for an incoming TCP packet, but ignore its contents
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len); 
  if (pos) { 
    delay(1);   // necessary for my system
    bfill = ether.tcpOffset();
    char *data = (char *) Ethernet::buffer + pos;
  
        data += 5;
        if (!strncmp("?home",data,5)){  homePage();
        } else  if (!strncmp("?reg=",data,5)){  
      
         String str(data);
         String ins=  str.substring(0, str.indexOf(" "));
         Serial.println(ins);  
         Serial.println(str);
   deviceInfo();
      
        } else {  bfill.emit_p(http_Unauthorized);  }
 
      ether.httpServerReply(bfill.position());    // send http response
    
  }
}
