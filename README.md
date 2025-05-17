# 🌤️ IoT Weather Monitoring System - Backend & ESP32 Code

This repository contains the backend server and ESP32 Arduino code for our **IoT-based Weather Monitoring System**. The system collects real-time environmental data such as temperature, pressure, wind speed, wind direction, UV index, and light intensity using sensors, and transmits it to a web server where it's processed, stored in a MySQL database, and visualized on a frontend dashboard.

---

## 🛠️ Fully Custom-Built Backend (by Me 😎)

This **Node.js-based web server** was **fully custom-made by myself** with the goal of building a lightweight yet powerful backend tailored specifically for real-time IoT data handling.

### 🔥 Unique Features

- **Direct JSON communication** with ESP32 over HTTP using minimal payload for efficiency.
- **Smart validation**: Ensures no incomplete or invalid sensor entries are saved.
- **Dual API support**:
  - `/api/weather/current` → for displaying current readings on the dashboard.
  - `/api/sensor-data` → for visualizing historical trends.
- **Meaningful error handling**: If data is missing or the ESP32 isn't connected, clear and informative responses are returned.
- **Built-in scalability**: Clean structure allows easy extension for more endpoints or sensor types in the future.

---

## 🗂️ Repository Branches

- **`backend` branch** → Contains the `server.js` (Node.js) backend that:
  - Receives data from ESP32 via POST.
  - Stores data in a MySQL database.
  - Provides API routes for both live and historical data.
  
- **`esp32-code` branch** → Contains the Arduino sketch for ESP32 which:
  - Reads sensors.
  - Formats and sends JSON data to the server.

---

## 🔐 Secure Credentials with Dotenv

To **protect sensitive database credentials**, this project uses the **dotenv** package.

- Credentials are stored in a `.env` file. 
- Example `.env`:
  ```env
  DB_HOST=your_database_host
  DB_USER=your_mysql_user
  DB_PASSWORD=your_mysql_password
  DB_NAME=your_database_name

---

## 🚀 How to Run the Server

1. Clone the repository and switch to the `backend` branch:

   ```bash
   git checkout backend
   ```

2. Install dependencies:

   ```bash
   npm install
   ```

3. Create a `.env` file in the root directory with your database details (as shown above).

4. Start the server:

   ```bash
   node server.js
   ```

The server will start on `http://localhost:5000` or the port defined in your `.env`.

---

## 🌐 Deployment

* **Heroku** is used to deploy the backend due to its **student-friendly free credentials** and reliable hosting.
* **Netlify** is used for hosting the frontend due to its fast performance and free tier.

🔗 **Frontend Website**: [weatherstationm2.netlify.app](https://weatherstationm2.netlify.app/)
🔗 **Frontend GitHub Repo**: [github.com/Thejasvenan/WeatherFrontend](https://github.com/Thejasvenan/WeatherFrontend)

---

## 💡 Future Software Improvements

* 🔐 User authentication & login system
* 📱 Mobile app to complement the website
* 🚨 Real-time alerts for abnormal sensor data
* 🔒 Encrypted data transfer (end-to-end HTTPS & SSL)
* 🔐 Encrypted data-at-rest in MySQL
* 📊 Auto-scaling for larger datasets and more sensors

## 🔧 Planned Hardware Enhancements

* 🎯 Wind direction readings accurate to **1 decimal place**
* 🌧️ Fully waterproof & weather-resistant enclosures
* 🔋 Battery-free operation for ESP32 (solar-powered / long-life)
* 🌐 Remote connectivity (SIM/GSM module or LoRa for offline locations)

---

## 🤝 Contributions & Suggestions Welcome!

If you have suggestions, ideas, or want to improve the system, feel free to open an issue or send a pull request. Your input is valuable and appreciated! 🧠💬

Let's build something awesome together.
— *Built with passion by Thejas 💙*
