#include <SPI.h>
#include <WiFiNINA.h>

//#include "arduino_secrets.h" 

char ssid[] = "ESP8266-Access-Point";      
char pass[] = "123456789";  
int keyIndex = 0; 

int status = WL_IDLE_STATUS;

char server[] = "http://192.168.4.1/Data";
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


void Show_meme() {
}

void Drive (int x, int y) {
  

}

void loop() {
  String buffer = "";
  int x;
  int y;
  int button;
  int i=0;
  while (client.available()) {
    char c = client.read();
    buffer += c;
  }
  string k="";
  char* pom=buffer;
  while(*pom != '$'){
    k += *pom;
    pom++;
  }
  int x =int(k);

  k="";
  pom++;
  while(*pom != '$'){
    k += *pom;
    pom++;
  }
  int y =int(k);

  k="";
  pom++;
  while(*pom != '$'){
    k += *pom;
    pom++;
  }
  int button =int(k);

  if(button == 1){
    Show_meme();
  }
  Drive(x, y);
  


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