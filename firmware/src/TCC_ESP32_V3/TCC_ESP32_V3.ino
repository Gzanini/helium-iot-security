#include "LoRaWAN_Radioenge.h"
#include "esp_system.h"
#include "DHT.h"

#define BOOT_LED_PIN 2
#define LED_PIN_ERR 25
#define DHT_PIN 13
#define DHT_TYPE DHT11
#define BOOT_BTN 0

LoRaWAN_Radioenge LoRa(&Serial2);
DHT dht(DHT_PIN, DHT_TYPE);

unsigned long lastSend = 0;
const unsigned long interval = 3600000; // 1 hora em milissegundos

String connectionType = "CS"; // Network Server (TTN [The Things Network] / CS [ChirpStack])

const char* app_eui;
const char* app_key;
uint8_t net = 0xFF;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 26, 27);

  pinMode(BOOT_LED_PIN, OUTPUT);
  pinMode(LED_PIN_ERR, OUTPUT);
  pinMode(BOOT_BTN, INPUT_PULLUP);

  digitalWrite(BOOT_LED_PIN, LOW);
  digitalWrite(LED_PIN_ERR, LOW);

  dht.begin();

  LoRa.begin(true);
  configurarCredenciais();
  JoinNetwork();

  delay(5000);
}

void JoinNetwork(){
  Serial.println("[JOIN] Tentando se conectar à rede " + connectionType + "...");
  bool joined = false;

  while (!joined) {
    LoRa.ATZ();
    delay(1000);

    joined = LoRa.JoinNetwork(OTAA, net, true, false);

    if (joined) {
      Serial.println("[✓] Join realizado com sucesso!");
      digitalWrite(BOOT_LED_PIN, HIGH);
      digitalWrite(LED_PIN_ERR, LOW);
      Serial.println("---------------------------------------------------");
      Serial.println("[JOIN] Primeiro envio após conexão. Enviando dados...");
      delay(2000);
      sendSensorData();
    } else {
      Serial.println("[X] Falha no Join. Tentando novamente em 1 minuto...");
      digitalWrite(LED_PIN_ERR, HIGH);
      delay(60000);
    }
  }
}

void sendSensorData() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("[X] Falha ao ler do sensor DHT11.");
    digitalWrite(LED_PIN_ERR, HIGH);
    while (true);
  }

  char payload[48];
  snprintf(payload, sizeof(payload), "T=%.1f H=%.1f C=%s", temp, hum, connectionType.c_str());

  Serial.print("[TX] Payload: ");
  Serial.println(payload);

  LoRa.SendString(payload, 1);
  delay(500);

  while (Serial2.available()) {
    String response = Serial2.readStringUntil('\n');
    Serial.print("RX: ");
    Serial.println(response);

    if (response.indexOf("AT_NO_NETWORK_JOINED") >= 0) {
      Serial.println("[!] Conexão perdida. Reiniciando ESP32 para refazer o Join...");
      delay(2000);
      esp_restart();
    }
    else if (response.indexOf("AT_TX_OK") >= 0) {
      Serial.println("[✓] Dados enviados com sucesso!");
    }
    else {
      Serial.println("[X] Falha ao enviar dados. Reiniciando ESP32 para tentar novamente...");
      delay(2000);
      esp_restart();
    }
  }

  Serial.println("---------------------------------------------------");
}

void configurarCredenciais() {
  if (connectionType == "CS") {
    LoRa.APPEUI("b6bf8cd2dcfb7654");
    LoRa.APPKEY("550e55107f2b3491c25fc2b95ff29dfa");
    net = 0x00;
  } else if (connectionType == "TTN") {
    LoRa.APPEUI("a2338dcd2eb09db6");
    LoRa.APPKEY("8DE317D23261962D47E419369FA2B2D3");
    net = 0x01;
  } else {
    Serial.println("Tipo de conexão inválido.");
    while (true);
  }
}


void loop() {
  if (millis() - lastSend >= interval) {
    Serial.println("[TIMER] Tempo atingido. Enviando dados...");
    sendSensorData();
    delay(1000);
    lastSend = millis();
  }

  if (digitalRead(BOOT_BTN) == LOW) {
    Serial.println("[BTN] Botão pressionado. Enviando dados...");
    sendSensorData();
    delay(1000);
  }
}
