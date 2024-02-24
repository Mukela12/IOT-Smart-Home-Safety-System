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


### Data Flow and Processing

The system's operation involves the following steps:

#### 1. Sensor Data Acquisition and Processing:
   
   - The client ESP8266 reads data from the DHT11 and MQ-9 sensors, assessing 
environmental conditions.

   - It processes this data to determine if there are any conditions (like high 
temperature or gas levels) that require immediate action.

#### 2. Actuator Control:
   
   - Based on the sensor data, the client ESP8266 controls various actuators. This 
includes activating the buzzer, lighting LEDs, and adjusting the servo motors 
to open or close windows.

#### 3. Client-to-Server Communication:

   - The client ESP8266 sends the processed sensor data to the server ESP8266.

   - The server ESP8266 updates the LCD display with the latest temperature and 
humidity readings, providing a local, real-time data visualization.

#### 4. Client-to-Blynk App Communication:

   - The client ESP8266 communicates directly with the Blynk app, sending 
sensor data for remote visualization.

   - It also receives user commands from the app, such as adjustments to the servo 
motor positions, and implements these commands in real-time.

![image](https://github.com/Mukela12/IOT-Smart-Home-Safety-System/assets/65640620/36c08a4e-fce6-4347-a594-cfe2ab42e0a5)


### Blynk App Functionality

The Blynk app serves as the primary interface for user interaction and monitoring, 
offering two key functionalities:

![image](https://github.com/Mukela12/IOT-Smart-Home-Safety-System/assets/65640620/ce1b5915-b1ef-44ef-9fc5-f3f13b0995fd)

1. Monitoring: It displays real-time data from the DHT11 and MQ-9 sensors. The 
app presents a visual representation of the current environmental conditions, 
including temperature, humidity, and gas levels.

2. Control: Through the app, users can remotely control the system. This includes 
adjusting the positions of the windows via sliders. The position of these sliders 
corresponds to the angle of the servo motors, allowing users to regulate 
ventilation based on the sensor readings.

![image](https://github.com/Mukela12/IOT-Smart-Home-Safety-System/assets/65640620/ab878818-7b6f-466f-aad3-1c4e58b2be87)


## Implementation


#### 1. Client-Side Circuit Assembly

The initial step involves connecting components to the client ESP8266. This setup 
enables the microcontroller to control various actuators based on sensor data, activating 
the buzzer, illuminating LEDs, and operating the servo motors for window 
manipulation.

![image](https://github.com/Mukela12/IOT-Smart-Home-Safety-System/assets/65640620/a74993df-d48c-4c78-9554-94135b5278ae)


#### 2. Server-Side Circuit Configuration

The second step entails assembling the server side circuit by connecting the second 
ESP8266 with the LCD display. This configuration allows the server ESP8266 to 
display temperature and humidity readings received from the client, ensuring local, 
real-time data visualization.

![image](https://github.com/Mukela12/IOT-Smart-Home-Safety-System/assets/65640620/1f89fc1a-259c-41a8-bb96-481a825b40e7)
