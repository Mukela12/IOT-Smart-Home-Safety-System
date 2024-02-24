#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
float temperature = 0.0;
float humidity = 0.0;

const char* ssid = "Aziz_&_Farioula_Welcome_U@unifi";
const char* password = "Vmat6428";
const char* host = "192.168.0.26";
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println("");
  Serial.println("Server-------------------------------");
  Serial.print("Configuring access point");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  Serial.println("-------------------------------------");
  Serial.println("");

  // Initialize LCD
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.print("Temp: --.- C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: --.-%");
  delay(1000);
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("Server-------------------------------");
  Serial.println("New client");
  Serial.print("From client = ");
  while (!client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  client.flush();
  Serial.print(req);
  if (req.indexOf("Temperature:") != -1 && req.indexOf("Humidity:") != -1) {
    temperature = getValue(req, "Temperature:", "C");
    humidity = getValue(req, "Humidity:", "%");

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");
  }

  client.flush();
  Serial.println("Client disconnected");
  Serial.println("-------------------------------------");
  Serial.println("");
}

float getValue(String data, String key, String unit) {
  int start = data.indexOf(key) + key.length();
  int end = data.indexOf(unit, start);
  return data.substring(start, end).toFloat();
}
