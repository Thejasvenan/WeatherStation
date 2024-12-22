const express = require("express");
const mysql = require("mysql2");
const bodyParser = require("body-parser");
const cors = require("cors");
require("dotenv").config();

const app = express();
const port = process.env.PORT || 5000;

// Middleware
app.use(bodyParser.json());
app.use(cors());

// MySQL connection
const db = mysql.createConnection({
  host: process.env.DB_HOST,
  user: process.env.DB_USER,
  password: process.env.DB_PASSWORD,
  database: process.env.DB_NAME,
});

db.connect((err) => {
  if (err) {
    console.error("Database connection failed:", err);
    return;
  }
  console.log("Connected to MySQL database");
});

// Route to insert sensor data
app.post("/api/sensor-data", (req, res) => {
  const {
    temperature,
    pressure,
    wind_speed,
    wind_direction,
    uv_index,
    light_intensity,
  } = req.body;

  // Ensure all values are provided
  if (
    temperature === undefined || 
    pressure === undefined || 
    wind_speed === undefined || 
    wind_direction === undefined || 
    uv_index === undefined || 
    light_intensity === undefined
  ) {
    return res.status(400).send("All sensor data fields are required.");
  }
  
  const query = `
    INSERT INTO sensor_data (temperature, pressure, wind_speed, wind_direction, uv_index, light_intensity) 
    VALUES (?, ?, ?, ?, ?, ?)`;

  db.query(
    query,
    [temperature, pressure, wind_speed, wind_direction, uv_index, light_intensity],
    (err, result) => {
      if (err) {
        console.error("Failed to insert data:", err);
        res.status(500).send("Database error");
        return;
      }
      res.status(201).send("Data inserted successfully");
    }
  );
});

// Route to fetch all sensor data
app.get("/api/sensor-data", (req, res) => {
  const query = "SELECT * FROM sensor_data ORDER BY timestamp DESC";
  db.query(query, (err, results) => {
    if (err) {
      console.error("Failed to fetch data:", err);
      res.status(500).send("Database error");
      return;
    }
    res.json(results);
  });
});

// Route to fetch the latest (current) sensor data
app.get("/api/weather/current", (req, res) => {
  const query = `
    SELECT temperature, pressure, wind_speed, wind_direction, uv_index, light_intensity, timestamp
    FROM sensor_data
    ORDER BY timestamp DESC
    LIMIT 1;`;

  db.query(query, (err, results) => {
    if (err) {
      console.error("Failed to fetch current data:", err);
      res.status(500).send("Database error");
      return;
    }

    if (results.length === 0) {
      res.status(404).send("No sensor data available. ESP32 might not be connected.");
      return;
    }

    res.json(results[0]); // Return the most recent data
  });
});

// Start the server
app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
