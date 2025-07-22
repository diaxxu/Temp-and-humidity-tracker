#include <WiFi.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>
#include <WebServer.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins
#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
WebServer server(80);

float temp = 0.0;
float hum = 0.0;

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>ESP32 Logger</title></head><body>";
  html += "<h2>Temperature: " + String(temp) + " °C</h2>";
  html += "<h2>Humidity: " + String(hum) + " %</h2>";
  html += "<p>Refresh every 10 seconds</p>";
  html += "<script>setTimeout(()=>location.reload(), 10000);</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected. IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

unsigned long lastRead = 0;

void loop() {
  server.handleClient();

  if (millis() - lastRead > 10000) {
    lastRead = millis();

    temp = dht.readTemperature();
    hum = dht.readHumidity();

    if (isnan(temp) || isnan(hum)) {
      Serial.println("Failed to read from DHT");
      return;
    }

    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("Temp: ");
    display.print(temp);
    display.print(" C");

    display.setCursor(0, 30);
    display.print("Hum: ");
    display.print(hum);
    display.print(" %");

    display.display();

    Serial.println("Updated display + web");
  }
}
