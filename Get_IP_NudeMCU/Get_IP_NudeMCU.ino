#include <ESP8266WiFi.h>

const char* ssid = "Aziz_&_Farioula_Welcome_U@unifi"; // Your WiFi ssid
const char* password = "Vmat6428"; // Your Wifi password;
// the setup function runs once pressed reset or power the board
void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // waiting for serial port to connect
  }
  Serial.print("Attempting to connect to SSID");
  WiFi.begin(ssid, password); //--> Activate or add or use this code if it fails to connect to wifi.
  // connecting to WiFi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");

        Serial.print(WiFi.status());
    // Connect to WPA/WPA2 network. 
    // Waiting 1 seconds for connection:
    delay(1000);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   // assigning IP address to ESP
}
void loop() {

}
