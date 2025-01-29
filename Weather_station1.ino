#include <Wire.h>
#include <SFE_BMP180.h>  // For BMP180
#include <BH1750.h>      // For BH1750 Light Sensor
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>
#include <cfloat>  // For FLT_MAX
 
// I2C Pins
#define I2C_SDA 21
#define I2C_SCL 22
 
// Sensor Objects
SFE_BMP180 bmp;
BH1750 lightMeter;
 
// WiFi credentials
const char* ssid = "Wi-Fi SSID";
const char* password = "Wi-Fi Password";

 
// Server endpoint
const char* serverURL = "https://weatherstation-backend-76068a291fbb.herokuapp.com/api/sensor-data";
 
// Sensor readings
float temperature = 0.0;
float pressure = 0.0;
float windSpeed = 0.0;
float windDirection = 0.0;
float uvIndex = 0.0;
float lightIntensity = 0.0;
 
// Pins for wind sensors
const int sensorPins[3] = {32, 33, 34};  // Pins for 3 sensors
const int numReadings = 400;  // Averaging count to reduce noise
 
// Define the analog pin where the sensor's SIG pin is connected
#define UV_SENSOR_PIN 18
 
// Data structure to store degree and 3 sensor values
struct WindData {
  int degree;
  float sensor[3];
};
 
// Dataset for 3 sensors and their readings
const WindData windDataset[] = {
  {0, {2445.9, 3537.11, 3885.73}},
  {5, {2386.79, 3595.46, 3861.78}},
  {10, {2322.92, 3662.21, 3829.64}},
  {15, {2289, 3703.64, 3792.41}},
  {20, {2258.61, 3741.29, 3743.59}},
  {25, {2249.26, 3770.54, 3690.03}},
  {30, {2284.43, 3801.5, 3623.31}},
  {35, {2321.91, 3819.6, 3551.35}},
  {40, {2365.78, 3843.13, 3470.48}},
  {45, {2448.45, 3857.29, 3389.48}},
  {50, {2567.46, 3870.26, 3277.97}},
  {55, {2688.89, 3878.17, 3194.25}},
  {60, {2776.06, 3884.4, 3096.44}},
  {65, {2886.22, 3893.73, 2977.47}},
  {70, {2980.79, 3899.85, 2878.78}},
  {75, {3086.98, 3904.68, 2774.75}},
  {80, {3151.42, 3911.86, 2701.38}},
  {85, {3254.64, 3911.25, 2599.78}},
  {90, {3322.66, 3913.68, 2513.26}},
  {95, {3400.4, 3916.95, 2451.91}},
  {100, {3457.95, 3917.63, 2422.57}},
  {105, {3514.34, 3916.5, 2397.68}},
  {110, {3559.25, 3916.64, 2400.36}},
  {115, {3604.73, 3916.89, 2418.63}},
  {120, {3639.23, 3911.91, 2453.41}},
  {125, {3658.28, 3908.37, 2536.26}},
  {130, {3686.64, 3904.37, 2610.1}},
  {135, {3710.2, 3897.31, 2694.8}},
  {140, {3730.18, 3888.19, 2789.75}},
  {145, {3741.01, 3881.27, 2873.76}},
  {150, {3757.42, 3870.98, 2964.94}},
  {155, {3768.95, 3857.13, 3079.18}},
  {160, {3781.51, 3845.15, 3179.59}},
  {165, {3789.04, 3819.65, 3279.13}},
  {170, {3799.71, 3796.77, 3369.94}},
  {175, {3803.88, 3770.21, 3453.42}},
  {180, {3806.38, 3731.81, 3544.56}},
  {185, {3814.27, 3690.49, 3622.71}},
  {190, {3816.35, 3645.18, 3681.45}},
  {195, {3818.22, 3580.44, 3736.27}},
  {200, {3821.48, 3523.81, 3781.51}},
  {205, {3825.4, 3441.9, 3827.93}},
  {210, {3824.25, 3358.96, 3855.49}},
  {215, {3824.83, 3256.8, 3883.47}},
  {220, {3825.46, 3148.56, 3906.9}},
  {225, {3822.57, 3024.35, 3928.29}},
  {230, {3823.12, 2892.03, 3947.6}},
  {235, {3816.28, 2762.89, 3960.91}},
  {240, {3811.89, 2647.9, 3971.47}},
  {245, {3808.97, 2492.67, 3979.67}},
  {250, {3800.33, 2372.37, 3987.61}},
  {255, {3790.63, 2258.44, 3996.44}},
  {260, {3783.28, 2157.57, 4000.65}},
  {265, {3775.32, 2079.95, 4004.71}},
  {270, {3757.36, 2014.67, 4009.79}},
  {275, {3739.2, 2002.86, 4012.17}},
  {280, {3723.09, 2005.35, 4015.29}},
  {285, {3693.98, 2025.27, 4015.82}},
  {290, {3659.26, 2083.24, 4016.4}},
  {295, {3625.12, 2154.66, 4015.36}},
  {300, {3573.59, 2230.72, 4018.25}},
  {305, {3505.49, 2367.83, 4013.74}},
  {310, {3430.06, 2502.38, 4007.35}},
  {315, {3357.97, 2621.93, 4005.52}},
  {320, {3265.19, 2761.7, 3997.11}},
  {325, {3176.82, 2882.81, 3997.36}},
  {330, {3080.97, 2991.54, 3985.6}},
  {335, {2968.47, 3112.98, 3972.22}},
  {340, {2854.06, 3221.42, 3963.36}},
  {345, {2736.8, 3319.42, 3950.69}},
  {350, {2633.47, 3404.63, 3931.6}},
  {355, {2552.36, 3469.69, 3914.29}}
};
 
float readSensor(int pin) {
  long sum = 0;
  for (int i = 0; i < numReadings; i++) {
    sum += analogRead(pin);
  }
  return (float)sum / numReadings;
}
 
float calculateDistance(const float *sensors, const WindData &data) {
  float sum = 0;
  for (int i = 0; i < 3; i++) {
    float diff = sensors[i] - data.sensor[i];
    sum += diff * diff;
  }
  return sqrt(sum);
}
 
int predictWindDirection() {
  float sensors[3];
  for (int i = 0; i < 3; i++) {
    sensors[i] = readSensor(sensorPins[i]);
  }
 
  int bestDegree = -1;
  float minDistance = FLT_MAX;
  for (const auto &data : windDataset) {
    float distance = calculateDistance(sensors, data);
    if (distance < minDistance) {
      minDistance = distance;
      bestDegree = data.degree;
    }
  }
  return bestDegree;
}
 
// Hall effect sensor variables
const int hallPin = 2;
volatile unsigned long lastPulseTime = 0;
volatile unsigned int pulseCount = 0;
const unsigned long debounceTime = 5;
const unsigned long measurementInterval = 5000;
const float rotationsPerMeterPerSecond = 0.421*2;
unsigned long lastMeasurementTime = 0;
 
// Setup function
void setup() {
  Serial.begin(115200);
 
  Wire.begin(I2C_SDA, I2C_SCL);
 
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
  }
 
  if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire)) {
    Serial.println("Error initializing BH1750 sensor.");
  } else {
    Serial.println("BH1750 initialized.");
  }
 
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
 
  // Initialize UV sensor pin
  pinMode(UV_SENSOR_PIN, INPUT);
  Serial.println("UV Detection Sensor Test");
 
  // Initialize Hall effect sensor pin
  pinMode(hallPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hallPin), countPulse, FALLING);
}
 
void countPulse() {
  unsigned long currentTime = millis();
  if (currentTime - lastPulseTime > debounceTime) {
    pulseCount++;
    lastPulseTime = currentTime;
  }
}
 
void loop() {
  char status;
  double T, P;
 
  // Read temperature and pressure from BMP180
  status = bmp.startTemperature();
  if (status != 0) {
    delay(status);
    status = bmp.getTemperature(T);
    if (status != 0) {
      temperature = T;
    }
  }
 
  status = bmp.startPre ssure(3);
  if (status != 0) {
    delay(status);
    status = bmp.getPressure(P, T);
    if (status != 0) {
      pressure = P;
    }
  }
 
  // Read light intensity from BH1750
  lightIntensity = lightMeter.readLightLevel();
 
  // Read UV intensity
  int sensorValue = analogRead(UV_SENSOR_PIN);
  float voltage = (sensorValue / 4095.0) * 3.3;
  uvIndex = voltage * 10; // Intensity in mW/cm²
 
  // Measure wind speed using Hall effect sensor
  unsigned long currentTime = millis();
  if (currentTime - lastMeasurementTime >= measurementInterval) {
    noInterrupts();
    unsigned int count = pulseCount;
    pulseCount = 0;
    interrupts();
 
    float frequency = (float)count / (measurementInterval / 1000.0);
    windSpeed = frequency / rotationsPerMeterPerSecond;
 
    lastMeasurementTime = currentTime;
 
    Serial.print("Frequency: ");
    Serial.print(frequency, 2);
    Serial.print(" Hz, Wind Speed: ");
    Serial.print(windSpeed, 2);
    Serial.println(" m/s");
  }
 
  // Predict wind direction using kNN
  windDirection = predictWindDirection();
 
  // Print sensor readings
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");
  Serial.print("Light Intensity: ");
  Serial.print(lightIntensity);
  Serial.println(" lx");
  Serial.print("Wind Speed: ");
  Serial.print(windSpeed);
  Serial.println(" m/s");
  Serial.print("Wind Direction: ");
  Serial.print(windDirection);
  Serial.println(" degrees");
  Serial.print("UV Intensity: ");
  Serial.print(uvIndex);
  Serial.println(" mW/cm²");
 
  // Create JSON payload
  // Create JSON payload with proper formatting
String jsonData = "{\n";
jsonData += "  \"temperature\": " + String(temperature, 2) + ",\n";
jsonData += "  \"pressure\": " + String(pressure, 2) + ",\n";
jsonData += "  \"wind_speed\": " + String(windSpeed, 2) + ",\n";
jsonData += "  \"wind_direction\": " + String(windDirection, 2) + ",\n";
jsonData += "  \"uv_index\": " + String(uvIndex, 2) + ",\n";
jsonData += "  \"light_intensity\": " + String(lightIntensity, 2) + "\n";
jsonData += "}";
 
 
  // Send data to server
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");
 
    int httpResponseCode = http.POST(jsonData);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.print("Response: ");
      Serial.println(response);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
 
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
 
delay(5000);  // Wait for 5 seconds before taking new readings
}