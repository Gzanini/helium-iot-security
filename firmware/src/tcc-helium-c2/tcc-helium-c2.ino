#include <Wire.h>
#include "INA3221.h"
#include <WiFi.h>
#include <HTTPClient.h>

INA3221 ina3221(0x40);

#define SDA_PIN 19
#define SCL_PIN 21

#define LED_OK 4
#define LED_ERR 22

const char* ssid = "Sebratel492"; //zanini_301
const char* password = "f0f1nha2020"; //72232fdb16
const char* tago_token = "71453302-c687-4a0b-93cb-7d7dc1a319ed";
String connectionType = "CS"; // ChirpStack

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  pinMode(LED_OK, OUTPUT);
  pinMode(LED_ERR, OUTPUT);
  digitalWrite(LED_OK, LOW);
  digitalWrite(LED_ERR, LOW);

  delay(1000);
  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);

  unsigned long startTime = millis();
  const unsigned long timeout = 15000;

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

  for (int ch = 0; ch < 3; ch++) {
    ina3221.enableChannel(ch);
    ina3221.setShuntR(ch, 0.1);
    ina3221.setWarningCurrent(ch, 3000);
    ina3221.setCriticalCurrent(ch, 3200);
  }

  ina3221.setModeShuntBusContinuous();
  ina3221.setMaskEnable(0x0000);

  Serial.println("Configuração finalizada.");
}

void sendToTago(float v1, float i1, float v2, float i2) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://api.tago.io/data");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Device-Token", tago_token);

    String payload = "[";
    payload += "{\"variable\":\"total_voltage\",\"value\":" + String(v1, 3) + ",\"unit\":\"V\",\"metadata\":{\"connection\":\"" + connectionType + "\"}},";
    payload += "{\"variable\":\"total_current\",\"value\":" + String(i1, 3) + ",\"unit\":\"mA\",\"metadata\":{\"connection\":\"" + connectionType + "\"}},";
    payload += "{\"variable\":\"radioenge_voltage\",\"value\":" + String(v2, 3) + ",\"unit\":\"V\",\"metadata\":{\"connection\":\"" + connectionType + "\"}},";
    payload += "{\"variable\":\"radioenge_current\",\"value\":" + String(i2, 3) + ",\"unit\":\"mA\",\"metadata\":{\"connection\":\"" + connectionType + "\"}}";
    payload += "]";

    int httpResponseCode = http.POST(payload);
    if (httpResponseCode > 0) {
      Serial.println("✅ Dados enviados ao TagoIO!");
      digitalWrite(LED_ERR, LOW);
    } else {
      Serial.print("❌ Erro ao enviar: ");
      Serial.println(httpResponseCode);
      digitalWrite(LED_ERR, HIGH);
    }
    http.end();
  } else {
    Serial.println("❌ Wi-Fi desconectado.");
    digitalWrite(LED_ERR, HIGH);
  }
}

void loop() {
  float totalVoltage = ina3221.getBusVoltage_mV(0) / 1000.0;
  float totalCurrent = ina3221.getCurrent_mA(0);
  float radioengeVoltage = ina3221.getBusVoltage_mV(1) / 1000.0;
  float radioengeCurrent = ina3221.getCurrent_mA(1);

  Serial.println("🔍 Leituras:");
  Serial.printf("Total - V: %.2f | I: %.3f A\n", totalVoltage, totalCurrent);
  Serial.printf("Radioenge - V: %.2f | I: %.3f A\n", radioengeVoltage, radioengeCurrent);

  sendToTago(totalVoltage, totalCurrent, radioengeVoltage, radioengeCurrent);
  delay(1000);  // 1 s
}
