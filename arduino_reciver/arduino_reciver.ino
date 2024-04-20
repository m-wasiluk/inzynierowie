#include <SPI.h>
#include <WiFiNINA.h>

//#include "arduino_secrets.h" 

char ssid[] = "ESP8266-Access-Point";      
char pass[] = "123456789";  
int keyIndex = 0; 

int status = WL_IDLE_STATUS;

char server[] = "http://192.168.4.1/ZAngle";
WiFiSSLClient client;

void setup() {
  
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

 
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
 
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
  
    status = WiFi.begin(ssid, pass);

  

    delay(10000);
  }
  Serial.println("Connected to WiFi");
  printWiFiStatus();

  Serial.println("\nStarting connection to server...");
  if (client.connect(server, 443)) {
    Serial.println("connected to server");
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println();
  }
}

void loop() {
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  if (!client.connected()) {
    Serial.println();


    ,
    AQSW2
    Serial.println("disconnecting from server.");
    client.stop();

    while (true);
  }
}


void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}