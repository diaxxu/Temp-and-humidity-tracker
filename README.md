# ESP32 Temp & Humidity Logger

Project using ESP32 + DHT22 + OLED.  
Shows real-time temperature and humidity on OLED and a web page.

## Components
- ESP32
- DHT22 sensor
- OLED (SSD1306)
- Jumper wires

## Features
- Real-time readings every 10s
- Display on OLED
- Web page with current and past readings

## How to Use
1. Flash `main.cpp` to ESP32
2. Connect to WiFi (edit SSID + password in code)
3. Open browser → `http://<ESP32_IP>`
4. View live data

## Wiring

| DHT22  | ESP32 |
|--------|-------|
| VCC    | 3.3V  |
| GND    | GND   |
| DATA   | D4    |

| OLED   | ESP32 |
|--------|-------|
| VCC    | 3.3V  |
| GND    | GND   |
| SDA    | D21   |
| SCL    | D22   |
