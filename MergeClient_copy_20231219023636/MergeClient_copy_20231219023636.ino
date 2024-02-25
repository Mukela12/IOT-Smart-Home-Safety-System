#define BLYNK_TEMPLATE_ID "TMPL6OLVqVeC9"
#define BLYNK_TEMPLATE_NAME "IOT project"
#define BLYNK_AUTH_TOKEN "QhMYiNchIfx2YurBZoWV8xz9613jEgMQ"

#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Servo.h>

char auth[] = "QhMYiNchIfx2YurBZoWV8xz9613jEgMQ";

char ssid[] = "wifi name";  
char pass[] = "wifi password";

const char * host = "Server IP Address";        // IP Server

const int httpPort = 80;

String Commands;                       // The command variable that is sent to the server                     

bool btn_press = true;                      // The variable to detect the button has been pressed
int con = 0;                                // Variables for mode

#define DHTPIN D6      // Digital pin D1
#define DHTTYPE DHT11  // DHT 11
#define GasSensorPin A0
#define BuzzerPin D8
#define RedLEDPin D4
#define GreenLEDPin D3
#define button D7
#define ServoPin D5  // Servo control pin
#define ServoPin2 D0  // Servo control pin


DHT dht(DHTPIN, DHTTYPE);
Servo servoMotor;
Servo servoMotor2;
SimpleTimer timer;

int GasDetectactive = 0;
int lastServoPosition = 0; // Variable to store the last servo position
int lastServoPosition2 = 0; // Variable to store the last servo position
int FireDetected = 0;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int gasValue = analogRead(GasSensorPin);


  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.println(h, 2); // Print humidity with two decimal places

  Serial.print("Temperature: ");
  Serial.println(t, 2); // Print temperature with two decimal places

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  Blynk.virtualWrite(V0, h);     // V0 is for Humidity
  Blynk.virtualWrite(V1, t);     // V1 is for Temperature
  Blynk.virtualWrite(V2, gasValue); // V2 is for Gas Value
  Blynk.virtualWrite(V3, lastServoPosition);
  Blynk.virtualWrite(V4, lastServoPosition2);

  if(t > 33) {
    FireDetected = 1;
    digitalWrite(BuzzerPin, HIGH);
    digitalWrite(RedLEDPin, HIGH);   // Turn on red LED
    digitalWrite(GreenLEDPin, LOW);  // Turn off green LED
    servoMotor.write(180);  
    servoMotor2.write(180);          // Set servo angle to 150 degrees
    Serial.println("Temperature is too high! Windows are open");
  }   else if ((t < 28) && (FireDetected == 1))
  {
    digitalWrite(BuzzerPin, LOW);
    digitalWrite(RedLEDPin, LOW);    // Turn off red LED
    digitalWrite(GreenLEDPin, HIGH); // Turn on green LED
    servoMotor.write(lastServoPosition); // Set servo angle to the last position
    servoMotor2.write(lastServoPosition2); // Set servo angle to 150 degrees
    Serial.println("Temperature is back to normal! Windows back to original position");
    FireDetected = 0;
  }

  if (gasValue > 400)
  {  
    GasDetectactive = 1;
    digitalWrite(BuzzerPin, HIGH);
    digitalWrite(RedLEDPin, HIGH);   // Turn on red LED
    digitalWrite(GreenLEDPin, LOW);  // Turn off green LED
    servoMotor.write(180);  
    servoMotor2.write(180);          // Set servo angle to 150 degrees
    Serial.println("Gas detected! Buzzer is ON");
  }
  else if ((gasValue < 380) && (GasDetectactive == 1))
  {
    digitalWrite(BuzzerPin, LOW);
    digitalWrite(RedLEDPin, LOW);    // Turn off red LED
    digitalWrite(GreenLEDPin, HIGH); // Turn on green LED
    servoMotor.write(lastServoPosition); // Set servo angle to the last position
    servoMotor2.write(lastServoPosition2); // Set servo angle to 150 degrees
    Serial.println("No gas detected. Buzzer is OFF");
    GasDetectactive = 0;
  }  
  Serial.println("Writing Data to be sent to LCD");
  String temperatureData = "Temperature:" + String(t, 2) + "C Humidity:" + String(h) + "%";
  Commands = temperatureData;
  Serial.print("Writing Data to be sent to LCD: ");
  Serial.println(Commands);
}

void setup()
{
  Serial.begin(115200);
  pinMode(button, INPUT_PULLUP);            // initialize the pushbutton pin as an input:
  Blynk.begin(auth, ssid, pass);

  pinMode(BuzzerPin, OUTPUT);
  pinMode(RedLEDPin, OUTPUT);
  pinMode(GreenLEDPin, OUTPUT);
  servoMotor.attach(ServoPin);  // Attach the servo motor to the specified pin
  servoMotor2.attach(ServoPin2);  // Attach the servo motor to the specified pin

  dht.begin();
  timer.setInterval(1000L, sendSensor);

  Serial.println("");
  Serial.println("Client-------------------------------");
  Serial.print("Connecting to Network");
  WiFi.mode(WIFI_STA);                      // Mode Station
  WiFi.begin(ssid, pass);               // Matching the SSID and Password
  delay(1000);

    // Waiting to connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("Successfully Connecting");  
  Serial.println("Status : Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("-------------------------------------");
  Serial.println("");
  
}

void loop()
{
  Blynk.run();
  timer.run();
  Serial.println(Commands);
  send_commands();
  delay(100);
}

void send_commands(){
  Serial.println("Sending command...");
  Serial.print("Connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  // We now create a URI for the request  
  Serial.print("Requesting URL : ");
  Serial.println(Commands);

  // This will send the request to the server
  client.print(String("GET ") + Commands + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: Close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {      
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  Serial.print("Server Reply = "); 
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println("Now you can press the button ...");
  Serial.println("-------------------------------------");
  Serial.println("");
}

BLYNK_WRITE(V3)
{
    lastServoPosition =  param.asInt();  // Update the last servo position
    servoMotor.write(lastServoPosition);  // Set the servo position
}
BLYNK_WRITE(V4)
{
    lastServoPosition2 =  param.asInt();  // Update the last servo position
    servoMotor2.write(lastServoPosition2);  // Set the servo position
}
