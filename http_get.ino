/*
  Web client

 * Description:  This sketch sends data to AskSensors (https://asksensors.com) using the Arduino Ethernet shield.
 *  Author: https://asksensors.com, 2018
 *  github: https://github.com/asksensors
 */

#include <SPI.h>
#include <Ethernet.h>


// ETHERNET config.

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 1, 177);

// ASKSENSORS config.     
char server[] = "asksensors.com";                               // ASKSENSORS host name
const int port = 80;                                      // Port: HTTP=80
const char* apiKeyIn = "MTWN7AQOLWJNEIF8RGMAW5EGKQFAHN2K";      // API KEY IN (change it with your API KEY IN)


// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
    // if you get a connection, report back via serial:
  if (client.connect(server, port)) { //35.229.58.223, 8585
    Serial.print("connected asksensors.com");
      //Create a URL for the request
      String url = "http://asksensors.com/api.asksensors/write/";
      url += apiKeyIn;
      url += "?module1=";
      url += 100;
      Serial.print("********** requesting URL: ");
      Serial.println(url);
     //Make a HTTP request:
      client.print(String("GET ") + "/api.asksensors/write/MTWN7AQOLWJNEIF8RGMAW5EGKQFAHN2K?module1=20" + " HTTP/1.1\r\n" +
               "Host: " + "asksensors.com" + "\r\n" +
               "Connection: close\r\n\r\n");
    client.println();
    
    Serial.println("> Request sent to ASKSENSORS");
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}
