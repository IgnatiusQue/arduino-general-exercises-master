/*
////////////////////////////////////////////////////////////////////////////////////////////////////
  AUTOR: JUAN BIONDI                                               FECHA:       FEBRERO/2014      
  PROGRAMA:    			                                   VERSION:     1.0               
  DISPOSITIVO: ATMEL 328                                           COMPILADOR:  AVR               
  ENTORNO:     PROTEUS                                             SIMULADOR:   VSM        
  TARJETA DE PROGRAMACION:                                         DEBUGGER:                      
////////////////////////////////////////////////////////////////////////////////////////////////////

  Web Server
 
 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pin A4 
 
 This pin has a temperature sensor (LM35)

////////////////////////////////////////////////////////////////////////////////////////////////////
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
// LIBRERIAS                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SPI.h>
#include <Ethernet.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIABLES GLOBALES                                                                             //
////////////////////////////////////////////////////////////////////////////////////////////////////
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,30);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(4988);

////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCIONES                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// CONFIGURACION                                                                                  //
////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
 // Open serial communications and wait for port to open:
  analogReference(INTERNAL);
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// PRINCIPAL                                                                                      //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 3");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<style>");
          client.println("body {background-color:lightgray}");
          client.println("h1 {color:blue}");
          client.println("p {color:red}");
          client.println("</style>");
          client.println("<FONT FACE=currier > Demostracion de un servidor web para mostrar la temperatura </FONT>");
          client.println("<br>");
          client.println("<FONT FACE=currier >  del aula con un sensor LM35 y un escudo de Arduino.</FONT>");

   
  
          // output the value of the temperature of the sensor connected to the analog pin
          int sensorReading = analogRead(A4);
          float temperatura = (sensorReading*1.1*100) / 1024;
          client.println("<br>");
          client.println("<br>");
          client.print("<center>");
          client.print("<h1>");
          client.print("La temperatura leida es: ");
          client.print(temperatura);
          client.print(" C");
          client.print("</h1>");
          client.print("<center>");
          client.println("<br>");
          client.println("<br>");
          
/*
////////////////////////////////////////////////////////////////////////////////////////////////////
          Now if the temperature is higher than the one we stablish it will print on the 
          remote computer a text with the word WARNING in Spanish
////////////////////////////////////////////////////////////////////////////////////////////////////
*/         
          
                
          if (temperatura >= 25)
            {
              //termometro();
                client.println("<div align=");
                String izquierda = "center";
                client.println(izquierda);
                client.println("<br>");
                client.print("<p>");
                client.println("!*****************************************************************************************************************************!");
                client.print("<p>");
                client.println("!___________@@@____@@_______@@____@@@@@____@@@@@___________@@@@_______@@@@________@@@@______________!");
                client.print("<p>");
                client.println("!_______@@_________@@________@@_______@@______@@____@@@______@@__@@_____@@___@@___@@_______@@___________!");
                client.print("<p>");
                client.println("!_______@@_________@@________@@_______@@______@@______@@_____@@____@@____@@_____@@_@@_______@@___________!");
                client.print("<p>");
                client.println("!_______@@_________@@________@@_______@@______@@______@@___@@@@@@@@___@@_____@@_@@_______@@__________!");
                client.print("<p>");
                client.println("!________@@_________@@______@@________@@______@@____@@@___@@________@@__@@___@@____@@_____@@____________!");
                client.print("<p>");
                client.println("!____________@@_________@@@__________@@@@@___@@@@@______@@__________@@_@@@@@________@@@@_____________!");
                client.print("<p>");
                client.println("!******************************************************************************************************************************!");
                //client.print("</p>");
                
            }
/*
////////////////////////////////////////////////////////////////////////////////////////////////////
          End of the if to write te WARNING word
////////////////////////////////////////////////////////////////////////////////////////////////////
*/             

          client.println("<br />"); 
          client.println("<img src=http://2.bp.blogspot.com/-9HHpJcFcwvg/Uk3Am5pT6cI/AAAAAAAAABE/YTAioD1T1Sc/s1600/CIFPN1.jpg alt=some_text>");
          client.println("<br />"); 
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}


