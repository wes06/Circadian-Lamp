unsigned int localPort = 2390;      // local port to listen for UDP packets

/* Don't hardwire the IP address or we won't get the benefits of the pool.
 *  Lookup the IP address for the host name instead */
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
IPAddress timeServerIP; // time.nist.gov NTP server address
const char* ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

const int localTime = -3; //Brasil = UTC -3




// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{

  Serial.println("Starting UDP");
  udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());

  
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}


unsigned long NTP_packet_sent;
boolean waitingForPacket = false;

int sendPacketAgain = 10;

void getAndPrintTime() {
  //get a random server from the pool
  
  if(!waitingForPacket){
    WiFi.hostByName(ntpServerName, timeServerIP);
    sendNTPpacket(timeServerIP); // send an NTP packet to a time server
    // wait to see if a reply is available
    waitingForPacket = true;
    NTP_packet_sent = millis();
  }
  if (millis() - 1000 > NTP_packet_sent) {
    int cb = udp.parsePacket();
    if (!cb) {
      Serial.println("no packet yet");
      NTP_packet_sent = millis();
      sendPacketAgain--;
      if(sendPacketAgain == 0){
        waitingForPacket = false;  
        sendPacketAgain = 10;
      }
    }
    else {
      
      sendPacketAgain = 10;
      waitingForPacket = false;
      Serial.print("packet received, length=");
      Serial.println(cb);
      // We've received a packet, read the data from it
      udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

      //the timestamp starts at byte 40 of the received packet and is four bytes,
      // or two words, long. First, extract the two words:

      unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
      unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
      // combine the four bytes (two words) into a long integer
      // this is NTP time (seconds since Jan 1 1900):
      unsigned long secsSince1900 = highWord << 16 | lowWord;
      //Serial.print("Seconds since Jan 1 1900 = " );
      //Serial.println(secsSince1900);

      // now convert NTP time into everyday time:
      //Serial.print("Unix time = ");
      // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
      const unsigned long seventyYears = 2208988800UL;
      // subtract seventy years:
      //unsigned long epoch = secsSince1900 - seventyYears;
      // print Unix time:
      //Serial.println(epoch);


      // print the hour, minute and second:
      //Serial.print("Local time is ");       // UTC is the time at Greenwich Meridian (GMT)
      //Serial.print(((epoch  % 86400L) / 3600) + localTime); // print the hour (86400 equals secs per day)
      //Serial.print(':');
      //if ( ((epoch % 3600) / 60) < 10 ) {
        // In the first 10 minutes of each hour, we'll want a leading '0'
      //  Serial.print('0');
      //}
      //Serial.println((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)

      //Serial.print(':');
      //if ( (epoch % 60) < 10 ) {
      //  // In the first 10 seconds of each minute, we'll want a leading '0'
      //  Serial.print('0');
      //}
      //Serial.println(epoch % 60); // print the second

      setTime(secsSince1900 - seventyYears + localTime*3600);

      timeAlreadySet = true;
      
      //int weekDay = (secsSince1900 % 604800L) / 86400;
      //int hora = ((secsSince1900 % 86400L)/3600) + localTime ;
      //int minuto = (secsSince1900 % 3600L) / 60;
      //Serial.print(weekDay);
      //Serial.print(" ");
      Serial.print(hour());
      Serial.print(":");
      Serial.println(minute());
      Serial.println("bla");

      // modulo 86400
      // modulo 3600
      udp.stop();
    }
  }

}
