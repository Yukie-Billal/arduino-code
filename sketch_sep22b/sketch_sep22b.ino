#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);

// Control LAMP variabel
char lamp = D5;
int lampState = HIGH; // default of fo the relay

void setup() {
  Serial.begin(9600);
  WiFi.begin("Bilal","Bismillah1");
  pinMode(lamp, OUTPUT);

  Serial.print("Connecting...");

  while(WiFi.status()!=WL_CONNECTED){ //Loop which makes a point every 500ms until the connection process has finished

    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected! IP-Address: ");
  Serial.println(WiFi.localIP()); //Displaying the IP Address

  if (MDNS.begin("nerd-corner")) {
    Serial.println("DNS started, available with: ");
    Serial.println("http://nerd-corner.local/");
  }
  server.onNotFound([](){ 
    server.send(404, "text/plain", "Link was not found!");  
  });
 
  server.on("/", []() {
    server.send(200, "text/html", "<a href='/on'>TURN ON </a><a href='/off'> TURN OFF</a>");
  });
 
  server.on("/on", []() {
    turnOn();
    server.send(200, "text/html", "<script>window.location.href = '/'</script>");
  });
  server.on("/off", []() {
    turnOff();
    server.send(200, "text/html", "<script>window.location.href = '/'</script>");
  });
  server.begin();
}

void loop() {
  server.handleClient();
  MDNS.update();
}

void turnOn() {
  digitalWrite(lamp, HIGH);
  Serial.println("HIGH");
}

void turnOff(){ //go to "IP-Adress/custom" to call this function
  digitalWrite(lamp, LOW);
  Serial.println("LOW");
}