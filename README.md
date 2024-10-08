# OPIN kWh Meter

[![License](https://img.shields.io/badge/license-Apache%202-blue.svg)](https://www.apache.org/licenses/LICENSE-2.0)

![kWh Meter](https://github.com/OPIN-Smart-Home/kWhMeter/blob/main/asset/kWhMeter.png)

## Table of Contents
For User
- [Introduction](#introduction)
- [Features](#features)
- [Components and Interface](#components-and-interface)
- [User Guide](#user-guide)

For Developer
- [Installation](#installation)
- [MQTT Topics](#mqtt-topics)
- [Limitations](#limitations)
- [Future Development](#future-development)

Additional Information
- [OPIN Smart Home Devices](#opin-smart-home-devices)
- [Acknowledgments](#acknowledgments)
- [Further Information](#further-information)

 ---
 ---

# For User
## Introduction
The OPIN kWh Meter is an innovative smart energy monitoring solution designed to provide users with real-time insights into their energy consumption. This standalone device is part of the broader OPIN ecosystem, which enhances home energy management and efficiency.

The OPIN kWh Meter accurately measures the amount of electricity used, enabling users to make informed decisions about their energy usage, leading to improved efficiency and potential cost savings. By tracking electricity consumption remotely through the OPIN mobile app, the kWh Meter enhances comfort and empowers users to monitor and optimize their energy usage effectively.

Designed for modern energy management, the kWh Meter helps users gain a better understanding of their electricity consumption, contributing to reduced carbon footprints and lower energy bills.

For developers, the OPIN kWh Meter integrates seamlessly with the OPIN system, facilitating easy communication and control. By leveraging MQTT topics for interaction, developers can enhance the functionality of the kWh Meter within the OPIN network, making it a versatile component of any smart home system.

## Features
1. **Real-Time Energy Monitoring**:  
   Provides live updates on electricity consumption, allowing users to track their energy usage instantly.
2. **Historical Data Logging**:  
   Stores historical consumption data, enabling users to analyze their energy usage patterns over time for informed decision-making.
3. **Cost Estimation**:  
   Users can calculate their energy costs based on consumption, helping them understand their electricity bills and make informed decisions about energy usage.
4. **Remote Monitoring and Control**:  
   Users can monitor their kWh Meter from anywhere using the OPIN mobile app, giving them the ability to manage energy consumption even when away from home.
5. **Easy Installation**:  
   Designed for straightforward installation, the OPIN kWh Meter can be set up quickly without requiring extensive technical knowledge.
6. **Integration with OPIN System**:  
   Fully compatible with the OPIN ecosystem, allowing users to leverage additional features and functionalities from other OPIN devices for enhanced energy management.
7. **Supports MQTT Protocol**:  
   Utilizes the MQTT messaging protocol for efficient communication, enabling seamless integration and control within the OPIN network.

## Components and Interface
The following components are used in the OPIN kWh Meter. The numbers correspond to the labels in the [cover image](#opin-kwh-meter):
1. [**ESP32 Devkit V1**](<https://olddocs.zerynth.com/r2.3.3/official/board.zerynth.doit_esp32/docs/index.html>)  
   The microcontroller responsible for managing the device's operations and communication via MQTT. It handles data from the energy metering module and sends it to the OPIN Gateway.
2. **LED**  
   The device features an LED that indicates the Wi-Fi connection status, helping users verify whether the device is connected to the network.
3. **Button**  
   A button is provided for initiating the Wi-Fi configuration process, allowing users to connect the device to their network. This button can also be used to reset the Wi-Fi connection.
4. [**HLK-PM01 AC-DC Converter**](<https://www.hlktech.net/index.php?id=105>)  
   This module converts the high-voltage AC input to a low-voltage DC output suitable for powering the ESP32 and other internal components.
5. [**PZEM-004T 10A AC Energy Metering Module**](<https://innovatorsguru.com/wp-content/uploads/2019/06/PZEM-004T-V3.0-Datasheet-User-Manual.pdf/>)  
   A current and voltage sensor that measures energy consumption in real-time. It calculates the total power usage, current, voltage, and energy consumption and communicates this data to the ESP32 for further processing.
6. **AC Plug**  
   The AC plug connects the OPIN kWh Meter to a standard power outlet, providing power to the system and the devices plugged into the power strip.
7. **3-Socket Power Strip**  
   A standard power strip with three sockets for connecting multiple electrical devices. This strip is monitored by the PZEM-004T module to measure the energy consumption of any devices plugged into it.

## User Guide
This section provides step-by-step instructions on how to set up and use the OPIN kWh Meter effectively.
### 1. Plug in the OPIN kWh Meter
Connect the AC plug of the kWh Meter to a power outlet.

### 2. LED Indicator
1. **Solid**: The device is connected to the network.
2. **Blinking continuously**: The device is not connected to a network or in the process of connecting.
3. **Off**: The device is either not powered or in WiFi configuration mode.

### 3. WiFi Configuration
#### Add WiFi Configuration
1. **Initiate WiFi Configuration**  
   - Press the button once to enter WiFi configuration mode. The LED will blink twice, indicating that the device is ready to connect to a network.  
   ![Button1](https://github.com/OPIN-Smart-Home/kWhMeter/blob/main/asset/button1.gif)

2. **Connect to the Network**  
   - Open the WiFi settings on your mobile, laptop, or PC.
   - Connect to the kWh Meter SSID `OPIN-kWhMeter-[device_id]`. Your device should automatically redirect you to the WiFi configuration interface (captive portal).
      > **Tips**: If you're not redirected to the captive portal automatically, try the following:  
      (1) Look for a notification asking you to `log in to the network`,  
      (2) Go to [WiFi settings](<https://media.techietech.tech/2020/06/Forget-Network.jpg.webp>) and select something like `Manage network settings`,  
      (3) Manually access the captive portal by opening `192.168.4.1` in your browser.
   - Once inside the configuration interface, select `Configure WiFi`. Choose your home WiFi SSID from the list, enter the password, and click `Save`. (Refer to the provided images for detailed guidance.)  
   ![Configure WiFi](https://github.com/OPIN-Smart-Home/kWhMeter/blob/main/asset/configure_wifi.png)

3. **Confirm Connection**  
   - After the connection is established, the LED will turn solid, indicating that the kWh Meter is successfully connected to your WiFi network.

#### Reset WiFi Configuration
1. **Initiate Reset**  
   - Press and hold the button for at least two seconds. The LED will blink three times (indicating reset) followed by two blinks (entering WiFi configuration mode), signaling that the WiFi settings have been reset. This action will erase all previously saved WiFi configurations.  
   ![Button2](https://github.com/OPIN-Smart-Home/kWhMeter/blob/main/asset/button2.gif)

2. **Reconnect to the Network**  
   - After resetting the WiFi, follow step [2 "Connect to the Network"](#add-WiFi-configuration) from the **Add WiFi Configuration** section to reconnect the kWh Meter to your WiFi.

#### Check IP Address of the kWh Meter
1. **Initiate WiFi Configuration**  
   - Press the button once to enter WiFi configuration mode. The LED will blink twice, indicating that the device is ready for network configuration.  
   ![Button1](https://github.com/OPIN-Smart-Home/kWhMeter/blob/main/asset/button1.gif)

2. **Connect to the Network**  
   - Open the WiFi settings on your mobile, laptop, or PC.
   - Connect to the kWh Meter SSID `OPIN-kWhMeter-[device_id]`, and your device will be redirected to the WiFi configuration interface (captive portal).  
      > **Tip**: If you're not redirected to the captive portal automatically, try the following:  
      (1) Look for a notification asking you to `log in to the network`,  
      (2) Go to [WiFi settings](<https://media.techietech.tech/2020/06/Forget-Network.jpg.webp>) and select `Manage network settings`,  
      (3) Manually access the captive portal by opening `192.168.4.1` in your browser.
   - The IP address of the kWh Meter will be shown in the connected WiFi details box. (Refer to the provided image for reference.)  
   ![Check IP](https://github.com/OPIN-Smart-Home/kWhMeter/blob/main/asset/check_ip.jpeg)

3. **Exit Configuration Mode**  
   - After checking the IP address, select `Exit` to complete the configuration process. The LED will turn solid, indicating that the kWh Meter is successfully connected to your WiFi network.

### 4. Connect kWh Meter to OPIN Mobile App
1. **Add New Device**  
   - Open the OPIN mobile app and click the `Add New Device` option.  
   - Select `kWh Meter` from the list of devices.  
   - Enter the `Device ID` and `IP Address` of the kWh Meter.  
   - Fill in additional fields such as `Customer ID`, `Device Name`, and `Cost per kWh`. You can find your local electricity cost on the [PLN Mobile App](<https://layanan.pln.co.id/pln-mobile>).  
   - Click `Submit`.  
   > **Note**: Ensure that the `Device ID` and `IP Address` are accurate to avoid issues during the device setup.

2. **Monitoring Energy Consumption**  
   - From the OPIN mobile app, navigate to the dashboard and select your `kWh Meter`.  
   - The app will display real-time data on:
     - **Current Power Consumption**: See how much power is currently being used by the connected devices.
     - **Voltage and Current Measurements**: View the voltage and current being supplied to the connected devices.
     - **Frequency**: Monitor the frequency of the electrical supply to ensure it remains stable.
     - **Power Factor**: Check the power factor to see how efficiently your devices are using electricity.
     - **Total Energy Consumption**: Track the total amount of energy consumed over time.
     - **Cost Estimation**: An estimate of the electricity bill based on your energy usage. You can adjust the cost per kWh in the app settings to match your local electricity rates.

3. **Reset Energy Consumption**  
   - In the app, there is an option to reset the current energy consumption and cost.  
   - When you reset, the current energy data is cleared, but the total energy consumed and the cost up to that point are stored in the history.  
   - You can view past energy consumption and cost records in the `History` section, making it easier to monitor and track your long-term energy usage.

### 5. Troubleshooting
1. **Device Not Connecting to Wi-Fi**
   - **Check Wi-Fi Credentials**: Ensure that the correct Wi-Fi credentials (SSID and password) are entered during the setup.
   - **Proximity to Router**: Make sure the kWh Meter is within the range of your Wi-Fi router. Try moving it closer to the router for better signal strength.
   - **Reboot the Device**: Unplug the kWh Meter from the power outlet and plug it back in to restart the device.

2. **App Not Displaying Data**
   - **Check Device ID and IP Address**: Ensure that the correct Device ID and IP address are entered in the app. Incorrect entries can prevent data from being displayed.

---
---

# For Developer
This section provides guidelines for developers looking to contribute to the OPIN Smart Home system. It's recommended to pay attention on [For User](#for-user) section.
## Installation
### Prerequisites
Before you begin, ensure you have the following installed on your development environment:
- **Arduino IDE** for uploading the firmware to the ESP32.
- **ESP32 Board Package** for Arduino IDE. For Arduino IDE, you can install it by going to **File > Preferences > Additional Board Manager URLs** and adding `https://dl.espressif.com/dl/package_esp32_index.json`. Then, navigate to **Tools > Board > Board Manager** and search for "ESP32".
- **Required Libraries**:
  - **Math**: For mathematical calculations involved in energy consumption, cost, and other metrics.
  - **WiFi**: For WiFi connectivity.
  - [**PicoMQTT** by Michał Leśniewski](<https://github.com/mlesniew/PicoMQTT>) version `0.3.8` : To enable the ESP32 to function as an MQTT broker/server.
  - [**WiFiManager** by tzapu](<https://github.com/tzapu/WiFiManager>) version `2.0.17`: For handling WiFi connections and configurations.
  - [**PZEM004Tv30** by Jakub Mandula](https://github.com/mandulaj/PZEM-004T-v30) version `1.1.2`: To interface with the PZEM-004T v3.0 energy meter, enabling the reading of voltage, current, and power values.

### Clone the Repository
To get started with the project, clone the repository to your local machine:
```bash
git clone https://github.com/OPIN-Smart-Home/kWhMeter.git
```

## MQTT Topics
The following MQTT topics are utilized for communication between the OPIN kWh Meter and the OPIN gateway:
- **Device to User (d2u)**:  
  `opin/kWhMeter_[device_id]/d2u`  
  This topic is used for sending data from the kWh Meter to the user, including real-time energy consumption and status updates.  
- **User to Device (u2d)**:  
  `opin/kWhMeter_[device_id]/u2d`  
  This topic is utilized for commands from the user to the kWh Meter. Its sole function is resetting the energy consumption data.  
- **Acknowledgment (ack)**:  
  `opin/kWhMeter_[device_id]/ack`  
  The topic for sending acknowledgment messages, which include the latest energy consumption data.  
- **Device SSID**:  
  `OPIN-kWhMeter-[device_id]`  
  This SSID is employed for connecting the kWh Meter to WiFi during the initial configuration process.
> **Note**: The gateway will not accept the same `device_id` for multiple kWh Meters. Developers must ensure that each kWh Meter has a unique `device_id` to avoid communication conflicts within the system.

## Limitations
While the OPIN kWh Meter is designed to provide accurate energy monitoring, there are some limitations to consider:
1. **Network Dependency**:  
   The kWh Meter requires a stable Wi-Fi connection for full functionality. Any disruptions or loss of connection may lead to interruptions in data reporting.
2. **Device ID Uniqueness**:  
   Each kWh Meter must have a unique `device_id`. Duplicate `device_id`s are not permitted, as they can lead to communication conflicts with the OPIN gateway.
3. **Power Dependency**:  
   The kWh Meter must be powered on to function. If the power supply is interrupted or turned off, the device will be non-operational until power is restored.
4. **Basic Functionality**:  
   The kWh Meter is primarily designed to monitor energy consumption and provide feedback on current usage. It does not support advanced features like remote control of connected devices or automation.

## Future Development
To enhance the capabilities of the OPIN kWh Meter, several future developments could be considered:
1. **Advanced Data Analytics**:  
   Implementing features that allow for detailed analytics and reporting on energy usage trends over time, helping users make informed decisions about their energy consumption.
2. **Integration with Smart Home Systems**:  
   Enhancing compatibility with other smart home devices, enabling automated responses based on energy consumption patterns (e.g., turning off devices when a certain threshold is reached).
3. **Remote Control Features**:  
   Considering the inclusion of remote control functionalities for connected devices based on real-time energy monitoring, allowing users to manage energy usage proactively.

---
---

# Additional Information
## OPIN Smart Home Devices
Other devices:
- [OPIN Smart Gateway](<https://github.com/OPIN-Smart-Home/OPIN-JetsonNano-public>)
- [OPIN Smart Lamp](<https://github.com/OPIN-Smart-Home/SmartLamp>)
- [OPIN Smart Door Lock](<https://github.com/OPIN-Smart-Home/DoorLock>)
- [OPIN Smart AC Control](<https://github.com/OPIN-Smart-Home/ACControl>)

## Acknowledgments
This project makes use of:  
- [PicoMQTT](<https://github.com/mlesniew/PicoMQTT>) by [mlesniew](<https://github.com/mlesniew>) (Michał Leśniewski), under [LGPL-3.0 license](<https://github.com/mlesniew/PicoMQTT/blob/master/LICENSE>).
- [WiFiManager](<https://github.com/tzapu/WiFiManager>) by [tzapu](<https://github.com/tzapu>), under [MIT license](<https://github.com/tzapu/WiFiManager/blob/master/LICENSE>).
- [PZEM004Tv30](<https://github.com/mandulaj/PZEM-004T-v30>) by [mandulaj](<https://github.com/mandulaj>) (Jakub Mandula), under [MIT license](<https://github.com/mandulaj/PZEM-004T-v30/blob/master/LICENSE>).

We appreciate their efforts and contributions, which have been instrumental in the development of this project.

## Further Information
For further information, please feel free to contact me at:
- **Email**: [anisahfarah28@gmail.com](mailto:anisahfarah28@gmail.com)
- **LinkedIn**: [Anisah Farah Fadhilah](https://www.linkedin.com/in/anisahfarahfadhilah)
