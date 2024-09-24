#include <math.h>
#include <WiFi.h>
#include <PicoMQTT.h>
#include <WiFiManager.h>
#include <PZEM004Tv30.h>

#define LED 18
#define WIFI_BUTTON 4
#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17
#define PZEM_SERIAL Serial2

String Wifissid;
PicoMQTT::Server mqtt;
PZEM004Tv30 pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN);

int push_count;
int commandMsg = 2;
int wifi_timeout = 90; // seconds
const long intervalTemp = 1000; // milliseconds
unsigned long start_time;
unsigned long previousMillis = 0;

// DEVICE ID
const char* topic_ack = "opin/kWhMeter_4zpk1/ack";
const char* topic_d2u = "opin/kWhMeter_4zpk1/d2u";
const char* topic_u2d = "opin/kWhMeter_4zpk1/u2d";
const char* device_ssid = "OPIN-kWhMeter-4zpk1";

void connect_mqtt() {
  Serial.println("\nStart MQTT Broker");
  const char* mqtt_server = WiFi.localIP().toString().c_str();

  // Subscribe to a topic pattern and attach a callback
  mqtt.subscribe(topic_u2d, [](const char * topic, const char * payload) {
    Serial.printf("Received message in topic '%s': %s\n", topic, payload);
    commandMsg = atoi(payload);
  });

  // Start the broker
  mqtt.begin();

  delay(100);
  Serial.println("MQTT Broker ready");
}

void connect_wifi() {
  Serial.println("\n Connecting...");
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);

  WiFiManager wm;
  wm.setConnectTimeout(5);
  wm.setConfigPortalTimeout(wifi_timeout);
  wm.startConfigPortal(device_ssid);

  if (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }else if (WiFi.status() == WL_CONNECTED){
    Serial.println("Connected");
    connect_mqtt();
  }
}

void reset_wifi() {
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);

  WiFiManager wm;
  WiFi.disconnect();
  wm.resetSettings();
}

void reconnect_wifi(String ssid, String pass) {
  delay(100);
  Serial.println("Reconnecting...");
  WiFi.disconnect();
  WiFi.begin(ssid, pass);

  unsigned long start_timeout = millis();
  while (WiFi.status() != WL_CONNECTED){
    if (millis() - start_timeout >= 3000){
      break;
    }
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
  if (WiFi.status() == WL_CONNECTED){
    Serial.println("Connected");
    connect_mqtt();
  }
}

void setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  Serial.begin(115200);
  Serial.println("\n Starting up");
  pinMode(LED, OUTPUT);
  pinMode(WIFI_BUTTON, INPUT_PULLUP);
}

void loop() {
  // WIFI and MQTT Connection
  push_count = 0;
  if (digitalRead(WIFI_BUTTON) == LOW) {
    start_time = millis();
    while (true) {
      if (millis() - start_time >= 100 && digitalRead(WIFI_BUTTON) == HIGH) {
        push_count = 1;
        break;
      }
      if (millis() - start_time >= 2000 && digitalRead(WIFI_BUTTON) == LOW) {
        push_count = 2;
        break;
      }
    }
  }

  if (push_count == 1) {
    connect_wifi();
  } else if (push_count == 2) {
    reset_wifi();
    connect_wifi();
  }

  if (WiFi.status() != WL_CONNECTED){
    WiFiManager wm;
    reconnect_wifi(wm.getWiFiSSID(), WiFi.psk());
  } else {
    mqtt.loop();
    digitalWrite(LED, HIGH);
  }

  // Main Program
  if (commandMsg == 1) {
    Serial.println("Energy reset");
    float energy = pzem.energy();
    pzem.resetEnergy();
    String json_data =  String("{") +
                        String("\"state\": 0") + String(",") +
                        String("\"energy\":") + String(energy, 4) +
                        String("}");
    mqtt.publish(topic_ack, json_data.c_str());
  }
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= intervalTemp) {
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    if(current < 0.00001 || power < 0.00001){
      Serial.println("Load is not on");
      String json_data =  String("{") +
                          String("\"load_state\": \"off\"")  +
                          String("}");
      mqtt.publish(topic_d2u, json_data.c_str());
    } else if (!isnan(voltage) || !isnan(current) || !isnan(power) || !isnan(energy) || !isnan(frequency) || !isnan(pf)) {
      Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
      Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
      Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
      Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
      Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
      Serial.print("Power Factor: "); Serial.println(pf);         Serial.println();
      String json_data =  String("{") +
                          String("\"load_state\": \"on\",")  +
                          String("\"voltage\":")      + String(voltage, 2)    + String(",") +
                          String("\"current\":")      + String(current, 2)    + String(",") +
                          String("\"power\":")        + String(power, 2)      + String(",") +
                          String("\"energy\":")       + String(energy, 4)     + String(",") +
                          String("\"frequency\":")    + String(frequency, 2)  + String(",") +
                          String("\"power_factor\":") + String(pf, 2) +
                          String("}");
      mqtt.publish(topic_d2u, json_data.c_str());
    }
    previousMillis = currentMillis;
  }
  commandMsg = 2;
  delay(10);
}
