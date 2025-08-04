#include <HTTP_Method.h>
#include <Middlewares.h>
#include <Uri.h>
#include <WebServer.h>

/*#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "";
const char* password = "";

// Set web server port number to 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        currentLine += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 2) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Send your "Hello World" HTML response
            client.println("<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
            client.println("<body><h1>Hello World</h1></body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}*/


#include <WiFi.h>
#include <WebSocketsServer.h>

#include <math.h>
#define ANALOG_IN 13
int ThermistorPin = 13;
int Vo;
float R1 = 10000; // value of R1 on board
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; //steinhart-hart coeficients for thermistor
int fetPin = 23;
const int pinUP = 255;
const int pinDOWN =0;

//const char* ssid = "";
//const char* password = "";
const char* ssid = "";
const char* password = "";
// Pins for vibration and heat pad control
const int VIBRATION_PIN = 32;
const int HEAT_PAD_PIN = 23;

WebSocketsServer webSocket = WebSocketsServer(81); // Port 81

void setup() {
  Serial.begin(115200);
  // pinMode(ThermistorPin, INPUT);
  //pinMode(fetPin,OUTPUT);
  pinMode(VIBRATION_PIN, OUTPUT);
  pinMode(HEAT_PAD_PIN, OUTPUT);
  digitalWrite(VIBRATION_PIN, LOW);
  digitalWrite(HEAT_PAD_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected! IP address: ");
  Serial.println(WiFi.localIP());

  webSocket.begin();
  webSocket.onEvent(handleWebSocketMessage);
}

void loop() {
  webSocket.loop();
}

void handleWebSocketMessage(uint8_t client_num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    String msg = (char*)payload;
    Serial.println("Received: " + msg);

    if (msg == "vibrate") {
      digitalWrite(VIBRATION_PIN, HIGH);
      delay(500);
      digitalWrite(VIBRATION_PIN, LOW);
    } else if (msg == "heat") {
      digitalWrite(HEAT_PAD_PIN, HIGH);
      delay(2000); // Optional: auto-off after 2s
      digitalWrite(HEAT_PAD_PIN, LOW);
    }
  }
}
