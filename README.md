Hardware Simulation

The hardware prototype of this project was developed and validated using the Wokwi IoT Simulator together with PlatformIO in Visual Studio Code. The simulation replicates the behavior of the proposed ESP32-based Smart Ayurvedic and Naturopathic Health Monitoring System before physical hardware implementation.

Components Used
Component	                Purpose
ESP32 DevKit V1	          Main microcontroller
DHT22	                    Temperature and Humidity sensing
MPU6050                  	Motion and Activity detection
SSD1306 OLED Display	    Real-time health dashboard
Push Button	              OLED page navigation
Green LED                	Balanced wellness indication
Red LED	                  Dosha imbalance indication
Piezo Buzzer	            Audible alert for imbalance

Simulation Features

The hardware simulation demonstrates:

🌡️ Real-time Temperature Monitoring
💧 Real-time Humidity Monitoring
🏃 Activity Detection using MPU6050
🌿 Rule-based Dosha Classification (Vata, Pitta, Kapha, Balanced)
📊 Wellness Score Calculation
📺 Interactive Multi-page OLED Interface
🔘 Push-button Navigation
🟢 Green LED for Balanced State
🔴 Red LED for Imbalance Detection
🔔 Buzzer Alerts
💡 Personalized Ayurvedic Wellness Recommendations

OLED Pages

The OLED interface consists of four interactive pages:

Page 1 – Smart Health Dashboard
Temperature
Humidity
Wellness Score
Page 2 – Activity Monitoring
Movement Status
X-axis Acceleration
Y-axis Acceleration
Z-axis Acceleration
Page 3 – Dosha Analysis
Current Dominant Dosha
Wellness Status
Page 4 – Personalized Recommendation
Dosha-specific wellness recommendations

Simulation Workflow
Power ON
     │
     ▼
Initialize ESP32
     │
     ▼
Read DHT22 Sensor
     │
     ▼
Read MPU6050 Sensor
     │
     ▼
Calculate Wellness Score
     │
     ▼
Determine Dosha
(Vata/Pitta/Kapha/Balanced)
     │
     ▼
Update OLED Display
     │
     ▼
LED & Buzzer Alert
     │
     ▼
Repeat

Development Environment
IDE: Visual Studio Code
Extension: PlatformIO
Simulation Platform: Wokwi
Programming Language: C++
Framework: Arduino
Target Board: ESP32 DevKit V1
