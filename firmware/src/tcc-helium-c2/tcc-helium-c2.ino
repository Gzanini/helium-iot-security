#include <Wire.h>
#include "INA3221.h"
#include <WiFi.h>
#include <HTTPClient.h>

INA3221 ina3221(0x40);  // Endereço padrão

#define SDA_PIN 19
#define SCL_PIN 21

#define LED_OK 4     // LED verde
#define LED_ERR 22   // LED vermelho

const char* ssid = "Sebratel492";
const char* password = "f0f1nha2020";
const char* tago_token = "bf671878-6b0e-44f9-9fc3-395f23a5fe33";
String connectionType = "CS"; //// Network Server (TTN [The Things Network] / CS [ChirpStack])

unsigned long lastSend = 0;
const unsigned long interval = 60000; // 1 minuto

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  pinMode(LED_OK, OUTPUT);
  pinMode(LED_ERR, OUTPUT);
  digitalWrite(LED_OK, LOW);
  digitalWrite(LED_ERR, LOW);

  delay(1000);
  Serial.println("\n📡 Escaneando redes...");
  int n = WiFi.scanNetworks();
  bool redeEncontrada = false;

  for (int i = 0; i < n; ++i) {
    Serial.printf("📶 %s | RSSI: %d dBm\n", WiFi.SSID(i).c_str(), WiFi.RSSI(i));
    if (WiFi.SSID(i) == ssid) {
      redeEncontrada = true;
    }
  }

  if (!redeEncontrada) {
    Serial.println("❌ Rede desejada não encontrada!");
    digitalWrite(LED_ERR, HIGH);
    return;
  }

  Serial.println("Tentando conectar ao Wi-Fi...");
  WiFi.begin(ssid, password);

  unsigned long startTime = millis();
  const unsigned long timeout = 15000;  // 15 segundos para tentar conectar

  while (WiFi.status() != WL_CONNECTED && millis() - startTime < timeout) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Conectado ao Wi-Fi!");
    digitalWrite(LED_OK, HIGH);
  } else {
    Serial.println("\n❌ Falha na conexão Wi-Fi.");
    digitalWrite(LED_ERR, HIGH);
    return;
  }

  Serial.println("Inicializando INA3221...");
  if (!ina3221.begin()) {
    Serial.println("INA3221 não detectado!");
    digitalWrite(LED_ERR, HIGH);
    while (1);
  }

  ina3221.enableChannel(0);
  ina3221.setShuntR(0, 0.1);
  ina3221.setWarningCurrent(0, 3000);
  ina3221.setCriticalCurrent(0, 3200);
  ina3221.setModeShuntBusContinuous();
  ina3221.setMaskEnable(0x0000);

  Serial.println("Configuração finalizada.");
}

void sendToTago(float voltage, float current) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://api.tago.io/data");

    http.addHeader("Content-Type", "application/json");
    http.addHeader("Device-Token", tago_token);

    String payload = "[";
    payload += "{\"variable\":\"voltage\",\"value\":" + String(voltage, 3) + ",\"metadata\":{\"connection\":\"" + connectionType + "\"}},";
    payload += "{\"variable\":\"current\",\"value\":" + String(current, 3) + ",\"metadata\":{\"connection\":\"" + connectionType + "\"}}";
    payload += "]";

    int httpResponseCode = http.POST(payload);
    if (httpResponseCode > 0) {
      Serial.println("Dados enviados ao TagoIO com sucesso!");
      digitalWrite(LED_ERR, LOW);
    } else {
      Serial.print("❌ Erro ao enviar: ");
      Serial.println(httpResponseCode);
      digitalWrite(LED_ERR, HIGH);
    }

    http.end();
  } else {
    Serial.println("Wi-Fi desconectado.");
    digitalWrite(LED_ERR, HIGH);
  }
}

void loop() {
  float voltage = ina3221.getBusVoltage_mV(0) / 1000.0;
  float current = ina3221.getCurrent_mA(0);

  Serial.print("Tensão (V): ");
  Serial.print(voltage, 3);
  Serial.print(" | Corrente (mA): ");
  Serial.println(current, 3);

  sendToTago(voltage, current);

  delay(2800);
}
