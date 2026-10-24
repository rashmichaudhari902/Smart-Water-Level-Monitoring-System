# Smart-Water-Level-Monitoring-System
IoT-Based Smart Water Level Monitoring System using ESP32, Ultrasonic Sensor, OLED Display and Blynk IoT.
# 💧 IoT-Based Smart Water Level Monitoring System

\<p align="center">
&#x20; \<b>An IoT-based solution for real-time water level monitoring using ESP32, HC-SR04 Ultrasonic Sensor, SSD1306 OLED Display and Blynk IoT.\</b>
\</p>

---

## 📌 About the Project

The **IoT-Based Smart Water Level Monitoring System** is designed to monitor and display the water level in a container using IoT technology.

The system uses an ESP32 microcontroller integrated with an HC-SR04 ultrasonic sensor to measure the distance between the sensor and the water surface. The measured distance is processed to calculate the water level percentage.

The readings are displayed on an SSD1306 OLED display and transmitted to the Blynk IoT platform for remote monitoring. A local web dashboard also provides an additional interface for viewing water-level information.

The system also incorporates possible water leakage detection to support better water monitoring and management.

## ✨ Key Features

- **Real-Time Monitoring:** Continuously measures the water level.
- **Percentage Calculation:** Displays the water level as a percentage.
- **Ultrasonic Measurement:** Uses the HC-SR04 sensor to detect the water surface distance.
- **OLED Display:** Shows water-level information locally.
- **Blynk IoT Integration:** Enables remote monitoring through the Blynk dashboard.
- **Local Web Dashboard:** Provides a browser-based monitoring interface.
- **Leak Detection:** Includes possible water leakage detection functionality.

## 🛠️ Hardware Components

| Component                 | Description                             |
| ------------------------- | --------------------------------------- |
| ESP32 Development Board   | Main microcontroller                    |
| HC-SR04 Ultrasonic Sensor | Measures distance to the water surface  |
| SSD1306 OLED Display      | Displays real-time water-level readings |
| Breadboard                | Supports hardware connections           |
| Jumper Wires              | Connects electronic components          |
| USB Cable                 | Power supply and programming            |
| Water Container           | Used for water-level monitoring         |

## 💻 Software and Technologies

- Arduino IDE
- Embedded C/C++
- ESP32
- Blynk IoT Platform
- HTML
- CSS
- JavaScript

## 🔌 Circuit Diagram

The circuit connects the ESP32 with the HC-SR04 ultrasonic sensor and SSD1306 OLED display.
<img width="1600" height="720" alt="image" src="https://github.com/user-attachments/assets/a617f7d0-9057-42bd-af70-b7af56fd44b8" />



### Pin Configuration

| Component | Pin  | ESP32 GPIO |
| --------- | ---- | ---------- |
| HC-SR04   | TRIG | GPIO 5     |
| HC-SR04   | ECHO | GPIO 18    |
| OLED      | SDA  | GPIO 21    |
| OLED      | SCL  | GPIO 22    |

## 🔧 Hardware Implementation

The following image shows the actual hardware prototype assembled using the ESP32, ultrasonic sensor, OLED display and connecting wires.

<img width="1152" height="648" alt="image" src="https://github.com/user-attachments/assets/59915690-0e1f-4ee0-b5e8-dba1ba6ccb3b" />


## ⚙️ Working Principle

1. The ESP32 initializes the ultrasonic sensor and OLED display.
2. The HC-SR04 sensor sends ultrasonic pulses towards the water surface.
3. The sensor receives the reflected pulses and measures the distance.
4. The ESP32 processes the distance measurement.
5. The water level is calculated as a percentage using the calibrated container dimensions.
6. The OLED display presents the calculated water level.
7. The readings are updated on the Blynk IoT dashboard.
8. The local web dashboard provides another way to monitor the system.
9. The implemented leakage detection logic checks for possible water leakage.

## 📊 System Architecture

The system follows an IoT-based architecture in which the ultrasonic sensor collects water-level measurements, the ESP32 processes the readings, and the information is made available through local and remote monitoring interfaces.

**System Workflow:**

HC-SR04 Ultrasonic Sensor → ESP32 Microcontroller → Water Level Calculation → OLED Display → Blynk IoT Dashboard / Local Web Dashboard

##

## 🎯 Applications

- Household water storage monitoring
- Small water tanks and containers
- Smart water management systems
- Water conservation applications
- IoT-based monitoring solutions

## 🚀 Future Scope

- Historical water-level data analysis
- Data logging and visualization
- Advanced alert and notification mechanisms
- Automatic water pump control
- Enhanced water management features

## 📁 Project Structure

```text
Smart-Water-Level-Monitoring-System/
│
├── Smart_Water_Level_Monitoring.ino
├── README.md
│
├── Images/
│   ├── circuit_diagram.png
│   └── hardware_setup.jpg

```

## 👩‍💻 Project Information

**Project Title:** IoT-Based Smart Water Level Monitoring System

**Domain:** Internet of Things (IoT)

**Microcontroller:** ESP32

**Development Environment:** Arduino IDE

## 📌 Project Status

The project implements real-time water-level measurement, OLED display output, Blynk IoT integration, local web monitoring and possible water leakage detection.

---

\<p align="center">
&#x20; \<b>Developed as an IoT-based academic project.\</b>
\</p>
