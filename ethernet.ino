// simple starting sketch for using the ethercard to send/receive info over the internet
// it displays the reading from input pin A0 as a demonstration and the led can be turned on or off via ethernet

// send data to the arduino by adding a command onto the end of the URL   e.g.  HTTP://172.22.139.5/option1  
//        http://x.x.x.x.x/on turns the led on, http://x.x.x.x.x/off turns it off


#include <EtherCard.h>

#define DEBUG 1   // set to 1 to display debug info via seral link

int sensorPin = A0;    // select the input pin for the potentiometer to display as test data
int LEDpin = 8;        // pin the LED is on   (you cant use the onboard one as the ethernet card uses it)

// web page buffer
  byte Ethernet::buffer[500];
  BufferFiller bfill;


// ----------------------------------------------


// HTML page to display

  static word homePage() {
  word sensorValue = analogRead(sensorPin);    
  bfill = ether.tcpOffset();

  // put variables in the HTML area as $d for a number and $c for text then add the actual values after the comma at the end
  // note   "<meta http-equiv=refresh content=5>"   tells the page to auto refresh every 5 seconds
  bfill.emit_p( PSTR ( 
    "HTTP/1.0 503 test page\r\n"
    "Content-Type: text/html\r\n"
    "Retry-After: 600\r\n"
    "\r\n"
    "<html>"
    "<head><title>"
    "Arduino test page"
    "</title></head>"
    "<body>"
    "<h3>This is a test page from the arduino</h3>" 
    "<p><em>"
    "input reading of A0 = $D <br />"
    "Led is $D <br />"
    "</em></p>"
    "</body>"
    "</html>" 
  ) , sensorValue , digitalRead(LEDpin) ) ;
  return bfill.position();
  }


// ----------------------------------------------


void setup () {

  // set LED pin 13 as output (so the led can be turned on and off)
  pinMode(LEDpin, OUTPUT);  
  
  // ethernet interface mac address
  static byte mymac[] = { 0x74,0x69,0x69,0x69,0x30,0x30 };

  //internet port to use (normal = 80)
  ether.hisport = 80 ; 

  // initialize serial:
  Serial.begin(9600);
  #if DEBUG
    Serial.println("Arduino Ethernet Sketch Started.....");
  #endif

  // start ethernet
  if (ether.begin(sizeof Ethernet::buffer, mymac, 10) == 0)
    Serial.println( "Failed to access Ethernet controller");
    
  // get ip from dhcp
  if (ether.dhcpSetup() == 0) 
    Serial.println( "Failed to get ip address from dhcp");
  
}


// ----------------------------------------------


void loop () {

  // check ip address has not expired
  if (ether.dhcpExpired()) {
  if (ether.dhcpSetup() == 0) 
    Serial.println( "Failed to renew ip address from dhcp");
  }


  // check if anything has come in via ethernet
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  
  if (pos) { // check if valid tcp data is received
    // data received from ethernet

       char* data = (char *) Ethernet::buffer + pos;

//       #if DEBUG       // display incoming data     - this is handy but tends to lock the arduino up ?
//         Serial.println("----------------");
//         Serial.println("data received:");
//         Serial.println(data);
//         Serial.println("----------------");
//       #endif

       // "on" command received     
       if (strncmp("GET /on",data,7) == 0) {
         digitalWrite(LEDpin, HIGH);   // set the LED on
       #if DEBUG
         Serial.println("option1 received");
       #endif
       }

       // "off" command received     
       if (strncmp("GET /off",data,8) == 0) {
         digitalWrite(LEDpin, LOW);   // set the LED off
       #if DEBUG
         Serial.println("option2 received");
       #endif
       }

       ether.httpServerReply(homePage()); // send web page data
   }
  
}



// ----------------------------------------------
// end
