# Smart_Safety_Vest
A wearable IoT-based safety monitoring system designed for industrial workers.
The Smart Safe Vest continuously monitors hazardous gases, temperature, and humidity and sends real-time data to an IoT dashboard while providing immediate alerts using LEDs and an LCD display.

This project aims to enhance worker safety in hazardous industrial environments by integrating sensors directly into wearable gear.

**📌 Project Overview**
Industrial environments often expose workers to toxic gases, extreme temperatures, and unsafe humidity levels. Traditional monitoring systems rely on stationary sensors or manual inspection, which may not provide real-time alerts.
The Smart Safe Vest solves this problem by embedding sensors into a wearable vest that:
- Detects hazardous gas levels
- Monitors temperature and humidity
- Sends real-time data to a cloud dashboard
- Alerts workers immediately during unsafe conditions

🧠 System Architecture

The system works in the following way:

 1️⃣ Sensors collect environmental data  
 2️⃣ NodeMCU processes sensor readings  
 3️⃣ Data is displayed on LCD  
 4️⃣ Alerts are triggered through LED indicators  
 5️⃣ Data is transmitted via WiFi to the Blynk IoT Dashboard  

 📡 IoT Dashboard

The system integrates with Blynk IoT to visualize data in real-time.

Dashboard displays:
- Temperature
- Humidity
- CO gas levels
- Smoke levels
- LPG levels

Both desktop and mobile dashboards can be used for monitoring.

![Circuit_Diagram]()
