# 🌤️ IoT Weather Monitoring System - Backend

This repository contains the **backend server** and **ESP32 Arduino code** for our **IoT-based Weather Monitoring System**. The system collects real-time environmental data such as temperature, pressure, wind speed, wind direction, UV index, and light intensity from sensors, transmits it to a custom web server, and stores the readings in a MySQL database for visualization and analysis.

---

## 🛠️ Fully Custom-Built Backend

This backend is **fully custom-made using Node.js and Express.js**, purpose-built for real-time sensor data collection, processing, and distribution. It serves as the **bridge between ESP32 and the frontend dashboard**, ensuring secure, efficient, and meaningful data handling.

### 🔥 Key Features

- **Express.js-based server** for handling HTTP POST/GET requests smoothly.
- **Direct JSON communication** with ESP32 for minimal and structured payload exchange.
- **Data validation logic** that ensures only valid and complete sensor records are stored.
- **Dual API endpoints**:
  - `POST /api/sensor-data` → to receive new sensor readings.
  - `GET /api/weather/current` → to fetch the most recent sensor data.
  - `GET /api/sensor-data` → to fetch historical data for dashboard charts.
- **Error handling**: If the ESP32 is offline or the database/server fails, user-friendly error messages are shown on the frontend (e.g., “ESP32 not connected”, “Server not available”).
- **Clean structure** for easy expansion (adding more sensors or analytics later).

---

## 🗂️ Repository Branches

- **`backend` branch** → Contains `server.js`, the backend API that:
  - Accepts data from ESP32.
  - Validates and stores it into MySQL.
  - Serves real-time and historical data to the frontend.
  
- **`esp32-code` branch** → Contains the Arduino sketch that:
  - Reads and formats data from sensors.
  - Sends JSON to the backend via HTTP.

---

## 🔐 Secure Credential Management with Dotenv

To keep your MySQL credentials safe and secure:

- This project uses the [`dotenv`](https://www.npmjs.com/package/dotenv) package.
- All database credentials are stored in a `.env` file (excluded from version control).

### ✅ Example `.env` file

```env
DB_HOST=your-database-host
DB_USER=your-db-username
DB_PASSWORD=your-db-password
DB_NAME=your-database-name
PORT=5000
````

---

## 🚀 Getting Started

To run the backend locally:

1. Clone the repository and switch to the `backend` branch:

   ```bash
   git checkout backend
   ```

2. Install the dependencies:

   ```bash
   npm install
   ```

3. Create a `.env` file in the root directory with your MySQL credentials (as shown above).

4. Start the server:

   ```bash
   node server.js
   ```

> The backend will run on `http://localhost:5000` or the port defined in your `.env`.

---

## 🌐 Deployment

### 🚀 Cloud Hosting

* **Heroku** was chosen to deploy the backend due to its **free student-friendly plan**, seamless integration, and reliable uptime.
* **Netlify** is used to host the frontend React application due to its **zero-cost hosting and fast CDN delivery**.

### 🔗 Live Frontend

* 🌍 **Website**: [https://weatherstationm2.netlify.app](https://weatherstationm2.netlify.app)
* 💻 **Frontend GitHub Repo**: [WeatherStation Frontend](https://github.com/Thejasvenan/WeatherFrontend)

---

## 💡 Future Software Enhancements

* 🔐 Add user authentication and access control
* 🚨 Real-time alerts for abnormal sensor readings
* 📱 Mobile app integration
* 🔒 Encrypted data transmission using HTTPS + SSL/TLS
* 🔐 Encrypt historical data stored in MySQL
* ⚙️ Auto-scaling architecture for adding more sensors

---

## 🧰 Planned Hardware Improvements

* 🎯 Achieve **1-decimal accuracy** for wind direction sensing
* 🌧️ Build **fully waterproof and robust** sensor enclosures
* 🔋 Enable **battery-free ESP32 operation** using solar or long-life power
* 📶 Use **GSM/SIM or LoRa modules** for connecting in remote/no-internet areas

---

## 🤝 Contributing & Feedback

This project is actively being improved. If you have an idea or suggestion to enhance the system — like improving data handling, adding more sensor support, or optimizing performance — feel free to open an issue or create a pull request.

Let's build a smarter world together.
— *Built from scratch with passion by Thejas 💙*

