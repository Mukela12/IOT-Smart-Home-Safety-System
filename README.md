## Project Description

The "Smart Home Safety System" is an advanced Internet of Things (IoT) project 
designed to enhance domestic safety by leveraging real-time environmental 
monitoring. This system integrates a network of sensors, actuators, and 
microcontrollers to detect and respond to potential hazards such as high temperatures 
and gas leaks. Utilizing two ESP8266 microcontrollers, the system divides 
responsibilities: one acts as a client, interfacing with sensors (DHT11 for temperature 
and humidity, MQ-9 for gas detection) and actuators (servo motors for window 
control, buzzer for alarms), while the other functions as a server, managing data 
display on an LCD and network communications. The inclusion of LEDs provides 
intuitive visual feedback, indicating safe or hazardous conditions. Remote monitoring 
and control are facilitated through the Blynk mobile and web application, enhancing 
user engagement and system responsiveness.


## Data Flow and Processing

The system's operation involves the following steps:

# 1. Sensor Data Acquisition and Processing:
   
• The client ESP8266 reads data from the DHT11 and MQ-9 sensors, assessing 
environmental conditions.

• It processes this data to determine if there are any conditions (like high 
temperature or gas levels) that require immediate action.

# 2. Actuator Control:
   
• Based on the sensor data, the client ESP8266 controls various actuators. This 
includes activating the buzzer, lighting LEDs, and adjusting the servo motors 
to open or close windows.

# 3. Client-to-Server Communication:

• The client ESP8266 sends the processed sensor data to the server ESP8266.

• The server ESP8266 updates the LCD display with the latest temperature and 
humidity readings, providing a local, real-time data visualization.

# 4. Client-to-Blynk App Communication:
• The client ESP8266 communicates directly with the Blynk app, sending 
sensor data for remote visualization.

• It also receives user commands from the app, such as adjustments to the servo 
motor positions, and implements these commands in real-time.

![image](https://github.com/Mukela12/IOT-Smart-Home-Safety-System/assets/65640620/36c08a4e-fce6-4347-a594-cfe2ab42e0a5)


