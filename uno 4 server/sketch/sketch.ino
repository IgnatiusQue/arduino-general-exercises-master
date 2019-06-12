#include <enc28j60.h>
#include <EtherCard.h>
#include <net.h>

#include <EtherCard.h>
#define STATIC 1  // set to 1 to disable DHCP (adjust myip/gwip values below)

#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,1,200 };
// gateway ip address
static byte gwip[] = { 192,168,1,1 };
#endif

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[500]; // tcp/ip send and receive buffer

const char page[] PROGMEM =
"HTTP/1.0 503 Service Unavailable\r\n"
"Content-Type: text/html\r\n"
"Retry-After: 600\r\n"
"\r\n"
"<html>"
  "<head><title>"
    "TESTE DE PAGINA WEB"
  "</title></head>"
  "<body>"
  "<font face=Verdana>"
 "<font size=5>" 
  "<font color=Blue>"
      "<h3>SE VOCE ESTA VENDO ESTA PAGINA TUDO OCORREU CERTO!!!!</h3>"
    "<p><em>"
    "<font size=7>" 
  "<font color=Red>"
      "TESTE EFETUADO EM 20/09/2016.<br />"
      "BETO DAHER"
    "</em></p>"
  "</body>"
"</html>"
;

void setup(){
  Serial.begin(57600);
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

void loop(){
  // wait for an incoming TCP packet, but ignore its contents
  if (ether.packetLoop(ether.packetReceive())) {
    memcpy_P(ether.tcpOffset(), page, sizeof page);
    ether.httpServerReply(sizeof page - 1);
  }
}
