# 🌤️ IoT Weather Monitoring System - Backend & ESP32 Integration

This repository contains the **fully custom-built backend server** and **ESP32 Arduino code** for our **IoT-based Weather Monitoring System**. The system collects real-time environmental data (temperature, pressure, wind speed/direction, UV index, and light intensity) from sensors, transmits it to a custom web server, and stores readings in a MySQL database for visualization and analysis.

---

## 🛠️ Fully Custom-Built Backend System

**Purpose-built with Node.js and Express.js** to serve as the bridge between ESP32 sensors and frontend dashboard, featuring robust data handling and security.

### 🔥 Core Features

**Backend (Node.js/Express.js):**
- ✅ **Lightweight Express.js server** optimized for IoT payloads
- 🔄 **Dual API endpoints**:
  - `POST /api/sensor-data` → Receives & validates ESP32 JSON data
  - `GET /api/weather/current` → Returns latest sensor readings
  - `GET /api/sensor-data` → Provides historical data for analytics
- 🛡️ **Data Validation**:
  - Rejects incomplete/invalid sensor entries
  - Returns meaningful error messages (e.g., "ESP32 offline", "Invalid sensor data")
- 🏗️ **Modular Architecture**:
  - Easy to extend with new sensors/endpoints
  - Clear separation of routes, controllers, and DB logic

**ESP32 (Arduino):**
- 📶 **Efficient HTTP communication** with minimal JSON payloads
- ⚡ **Low-power optimizations** for continuous operation
- 🔧 **Sensor calibration support** in firmware

---

## 🗂️ Repository Structure

| Branch       | Contents |
|--------------|----------|
| **`backend`** | `server.js`, database models, API routes, and middleware |
| **`esp32-code`** | Complete Arduino sketch for sensor reading and HTTP transmission |

---

## 🔐 Security & Credential Management

**Enterprise-grade protection using:**
- **Dotenv** for credential isolation
- **Git-ignored `.env` file** pattern
- **Encrypted database connections**

### 🛡️ Example `.env` Configuration
```env
DB_HOST=your-database-host
DB_USER=your-db-username
DB_PASSWORD=your-db-password
DB_NAME=your-database-name
```

---

## 🚀 Deployment & Infrastructure

### ☁️ Hosting Solutions
| Component   | Platform  | Benefits |
|-------------|-----------|----------|
| **Backend** | Heroku    | Free tier, auto-scaling, easy CI/CD |
| **Frontend** | Netlify  | Global CDN, instant cache invalidation |
| **Database** | MySQL | Relational data integrity |

### 🌐 Live Systems
- 🖥️ **Dashboard**: [weatherstationm2.netlify.app](https://weatherstationm2.netlify.app)
- 💾 **Frontend Code**: [github.com/Thejasvenan/WeatherFrontend](https://github.com/Thejasvenan/WeatherFrontend)

---

## 🔧 Installation Guide

### Backend Setup
```bash
git clone https://github.com/your-repo.git
git checkout backend
npm install
echo "DB_HOST=localhost\nDB_USER=root\nDB_PASSWORD=pass\nDB_NAME=weather" > .env
node server.js
```

### ESP32 Setup
1. Install required Arduino libraries:
   - WiFi.h
   - HTTPClient.h
   - Sensor-specific libraries
2. Configure `SECRET_SSID` and `SECRET_PASS` in credentials.h
3. Set backend endpoint in `config.h`

---

## 🚧 Future Roadmap

### 💻 Software Enhancements
| Priority | Feature | Status |
|----------|---------|--------|
| P0 | HTTPS/SSL Encryption | Planned |
| P1 | User Authentication | In Design |
| P2 | Anomaly Detection Alerts | Research Phase |
| P3 | Mobile App Integration | Backlog |

### ⚙️ Hardware Improvements
| Component | Upgrade Target |
|-----------|----------------|
| Wind Vane | 1° precision with hall-effect sensors |
| Housing | IP67 waterproof enclosures |
| Power | Solar + supercapacitor backup |
| Connectivity | LoRaWAN for remote sites |

---

## 🤝 Contributions & Suggestions Welcome!

If you have suggestions, ideas, or want to improve the system, feel free to open an issue or send a pull request. Your input is valuable and appreciated! 🧠💬

Let's build something awesome together.
— *Built with passion by Thejas 💙*
