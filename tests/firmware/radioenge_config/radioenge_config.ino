#include "LoRaWAN_Radioenge.h"

LoRaWAN_Radioenge LoRa(&Serial2);

String commandBuffer = "";  

void setup() {
  Serial.begin(9600);                          // Comunicação com o PC
  Serial2.begin(9600, SERIAL_8N1, 26, 27);     // Comunicação com o módulo (TX = 26, RX = 27)

  delay(500);          // Aguarda estabilizar comunicação
  LoRa.begin(true);    // Inicializa o módulo e busca parâmetros

  LoRa.printParameters(); // Exibe DevEUI, AppEUI, AppKey, etc.
  
}

void loop() {
  // Envia do PC → módulo
  while (Serial.available()) {
    char c = Serial.read();
  commandBuffer += c;

    if (c == '\n' || c == '\r') {
      commandBuffer.trim();
      if (commandBuffer.length() > 0) {
        Serial.println("TX: " + commandBuffer);
        Serial2.println(commandBuffer);
      }
      commandBuffer = "";
    }
  }

  // Envia do módulo → PC
  if (Serial2.available()) {
    String resposta = Serial2.readStringUntil('\n');
    Serial.print("RX: ");
    Serial.println(resposta);
  }
}
