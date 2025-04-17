#include "LoRaWAN_Radioenge.h"

#define LED_PIN_G 2
#define LED_PIN_R 4

LoRaWAN_Radioenge LoRa(&Serial2);

void setup() {
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_R, OUTPUT);
  digitalWrite(LED_PIN_G, LOW);
  digitalWrite(LED_PIN_R, LOW);

  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  LoRa.begin(true);    // Inicializa o módulo e busca parâmetros
  LoRa.printParameters();

  bool joined = LoRa.JoinNetwork(OTAA, CS, false, false);
  delay(10000);

  if (joined) {
    Serial.println("✅ JOIN realizado com sucesso!");
    digitalWrite(LED_PIN_G, HIGH);
  } else {
    Serial.println("❌ JOIN falhou.");
    digitalWrite(LED_PIN_R, HIGH);
  }
}

void loop() {
  // Envia do PC → módulo
  if (Serial.available()) {
    Serial2.write(Serial.read());
  }

  // Envia do módulo → PC
  if (Serial2.available()) {
    Serial.write(Serial2.read());
  }
}
