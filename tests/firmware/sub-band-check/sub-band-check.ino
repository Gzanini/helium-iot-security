#include "LoRaWAN_Radioenge.h"

#define LED_PIN_G 2 //esquerda
#define LED_PIN_R 4 // direita (lado da antena)

LoRaWAN_Radioenge LoRa(&Serial2);

// Lista das sub-bandas (US915), cada uma com 8 canais uplink
const char* chmask_list[8] = {
  "FF00:0000:0000:0000:0001:0000",  // Sub-band 1
  "00FF:0000:0000:0000:0002:0000",  // Sub-band 2 (Melhor conectividade nos testes)
  "0000:FF00:0000:0000:0004:0000",  // Sub-band 3
  "0000:00FF:0000:0000:0008:0000",  // Sub-band 4
  "0000:0000:FF00:0000:0010:0000",  // Sub-band 5
  "0000:0000:00FF:0000:0020:0000",  // Sub-band 6
  "0000:0000:0000:FF00:0040:0000",  // Sub-band 7
  "0000:0000:0000:00FF:0080:0000"   // Sub-band 8
};

void setup() {
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_R, OUTPUT);
  digitalWrite(LED_PIN_G, LOW);
  digitalWrite(LED_PIN_R, LOW);

  Serial.begin(9600);                            // Comunicação com PC
  Serial2.begin(9600, SERIAL_8N1, 16, 17);       // Comunicação com o módulo (TX=17, RX=16)

  LoRa.begin(true);  // Inicializa o módulo

  // Parâmetros do dispositivo (ajuste com os seus valores do Helium Console)
  LoRa.APPEUI("9C6F4E7E25D9AFBB");
  LoRa.APPKEY("EEBA57047087E0B566AC8768E9F6672A");
  delay(500);

  Serial.println("\n🚀 Iniciando teste automático de sub-bandas...\n");

  for (int i = 0; i < 8; i++) {
    Serial.print("🛰️  Testando Sub-banda ");
    Serial.print(i);
    Serial.print(" → AT+CHMASK=");
    Serial.println(chmask_list[i]);

    // Envia comando AT diretamente via Serial2
    Serial2.print("AT+CHMASK=");
    Serial2.println(chmask_list[i]);
    delay(1000); // Tempo para o módulo aplicar

    // Tenta o join
    bool joined = LoRa.JoinNetwork(OTAA, TTN, true, false);

    if (joined) {
      Serial.print("✅ Sub-banda ");
      Serial.print(i);
      Serial.println(" JOIN OK ✅\n");
      digitalWrite(LED_PIN_G, HIGH);
      digitalWrite(LED_PIN_R, LOW);
      break;
    } else {
      Serial.print("❌ Sub-banda ");
      Serial.print(i);
      Serial.println(" JOIN ERROR ❌\n");
    }

    delay(6000); // Aguarda antes de tentar a próxima sub-banda
  }

  Serial.println("🔁 Fim dos testes.");
  digitalWrite(LED_PIN_R, HIGH);
  digitalWrite(LED_PIN_G, LOW);
}

void loop() {
  // Nada aqui
}
