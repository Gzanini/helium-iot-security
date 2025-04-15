#include "LoRaWAN_Radioenge.h"

LoRaWAN_Radioenge LoRa(&Serial2);

void setup() {
  Serial.begin(9600);                          // Comunicação com o PC
  Serial2.begin(9600, SERIAL_8N1, 16, 17);     // Comunicação com o módulo (TX = 17, RX = 16)

  delay(500);          // Aguarda estabilizar comunicação
  LoRa.begin(true);    // Inicializa o módulo e busca parâmetros

  LoRa.printParameters(); // Exibe DevEUI, AppEUI, AppKey, etc.
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
