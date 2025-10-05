# Smart Incentivized Dustbin

## Project Overview
The **Smart Incentivized Dustbin** is an IoT-based waste management system designed to promote cleanliness and environmental responsibility on campuses. The system automatically detects waste disposal, identifies users via RFID, and generates QR-based reward vouchers that can be redeemed within the campus. All activity data is logged in a Firebase cloud database and visualized on a web dashboard to monitor usage, bin levels, and top contributors.

---

## Features
- **Automated Waste Detection:** Ultrasonic sensor monitors bin fill levels in real-time.
- **RFID-Based Identification:** Tracks individual student contributions.
- **Reward System:** Generates QR vouchers for responsible waste disposal.
- **Cloud Logging:** Firebase stores all disposal data with timestamps and user IDs.
- **Web Dashboard:** Displays bin fill levels, usage stats, and leaderboards.
- **Alerts & Notifications:** Sends notifications when the bin reaches a threshold level.

---

## Hardware Requirements
| Component | Specification / Description |
|-----------|----------------------------|
| ESP32 Development Board | 32-bit dual-core microcontroller with Wi-Fi/Bluetooth |
| Ultrasonic Sensor (HC-SR04) | Detects bin fill levels using ultrasonic waves |
| RFID Reader (MFRC522) | Reads student RFID cards/tags (13.56 MHz) |
| RFID Cards/Tags | Unique IDs for students |
| TFT Display (2.4”/2.8”) | Displays QR codes and messages |
| Buzzer & LEDs | Provides feedback and status indicators |
| 18650 Li-ion Batteries + Holder | 3.7V rechargeable cells |
| TP4056 Charging Module | Safe battery charging |
| MT3608 / AMS1117 Converters | Voltage regulation for ESP32 and sensors |
| Plastic/Steel Dustbin | Physical waste container |

---

## Software Requirements
- **Arduino IDE** – Upload code to ESP32  
- **Firebase Realtime Database** – Store disposal logs and student data  
- **Vercel / Web Hosting** – Host the web dashboard  
- **Chart.js / HTML / JavaScript** – Frontend for dashboard  
- **QR Code Generation Library (ESP32)** – Generate digital vouchers  

---

## Setup Instructions

1. **Hardware Assembly**
   - Connect the ultrasonic sensor, RFID reader, TFT display, LEDs, and buzzer to the ESP32 as per the wiring diagram.
   - Insert Li-ion batteries and ensure proper voltage regulation.

2. **Arduino Code**
   - Open `main.ino` in Arduino IDE.
   - Install required libraries (RFID, Ultrasonic, QR code library).
   - Update Wi-Fi and Firebase credentials.
   - Upload code to ESP32.

3. **Dashboard Deployment**
   - Open `Dashboard/index.html` and `script.js`.
   - Link to your Firebase database.
   - Deploy files on Vercel or any static web hosting platform.

4. **Testing**
   - Tap a registered RFID card to authenticate.
   - Dispose of waste; verify that the QR code appears on the TFT display.
   - Check real-time logging and leaderboard updates on the web dashboard.

---

## Observations
- Reliable RFID detection within 3–5 cm range.
- Ultrasonic sensor accurately measures bin fill levels.
- QR vouchers generated instantly for each disposal event.
- Real-time cloud logging and dashboard visualization work consistently.

---

## Future Enhancements
- Solar-powered bin for self-sustainability.
- Mobile app integration for students to track and redeem points.
- AI-based automatic waste segregation.
- Multi-bin network for campus-wide monitoring.
- Advanced analytics for optimizing cleaning schedules.

---

## Authors
- **Viraj Sharad Patil** – 2405003  
- **Gargi Prashant Patil** – 2405008  
- **Tanvi Ramchandra Patil** – 2405023  

Under the guidance of **Prof. Vilbha Patil**  
Department of Electronics & Telecommunication Engineering  
Rajarambapu Institute of Technology, Rajaramnagar  

---

## License
This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.

