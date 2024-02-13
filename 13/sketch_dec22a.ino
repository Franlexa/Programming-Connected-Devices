#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define DHT_PIN 13
#define DHT_TYPE DHT22

#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14
#define WIRE Wire

#define NEOPIXEL_PIN 12
#define NEOPIXEL_COUNT 4

const char* ssid = "PWME";
const char* password = "welcome to PWME"; 
const char* mqtt_server = "10.1.2.3"; 
const int mqtt_port = 1883;
const char* mqtt_topic = "S219_29"; 

DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(128, 32, &WIRE, -1);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client iot_module")) {
      Serial.println("Connected to MQTT");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("DHT22 test");
  dht.begin();
  Serial.println("DHT22 begun");

  Serial.println("OLED FeatherWing test");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.println("OLED begun");

  Serial.println("WS2812B test");
  strip.begin();
  strip.show();

  display.display();
  delay(1000);

  display.clearDisplay();
  display.display();

  Serial.println("IO test");

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Connecting to WiFi...");
  display.display();

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

  display.clearDisplay();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("H: ");
  display.print(humidity);
  display.print(" %\n");
  display.print("T: ");
  display.print(temperature);
  display.print(" C");
  display.display();

  int color = map(temperature, 0, 30, 0, 255);
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(color, 0, 255 - color));
  }
  strip.show();

  String temperatureString = String(temperature);
  String humidityString = String(humidity);
  String message = "Temperature is: " + temperatureString + "°C Humidity is: " + humidityString + "%";
  client.publish(mqtt_topic, message.c_str());
  Serial.println(message);
}