#include "LoRaWAN_Radioenge.h"

#define LED_PIN_G 2 //esquerda
#define LED_PIN_R 25 // direita (lado da antena)

LoRaWAN_Radioenge LoRa(&Serial2);

String connectionType = "CS"; // Network Server (TTN [The Things Network] / CS [ChirpStack])

const char* app_eui;
const char* app_key;
uint8_t net = 0xFF;

// Lista das sub-bandas (US915), cada uma com 8 canais uplink
const char* chmask_list[9] = {
  "FF00:0000:0000:0000:0001:0000",  // Sub-band 1
  "00FF:0000:0000:0000:0002:0000",  // Sub-band 2 (Melhor conectividade nos testes)
  "0000:FF00:0000:0000:0004:0000",  // Sub-band 3
  "0000:00FF:0000:0000:0008:0000",  // Sub-band 4
  "0000:0000:FF00:0000:0010:0000",  // Sub-band 5
  "0000:0000:00FF:0000:0020:0000",  // Sub-band 6
  "0000:0000:0000:FF00:0040:0000",  // Sub-band 7
  "0000:0000:0000:00FF:0080:0000",  // Sub-band 8
  "FFFF:0000:0000:0000:0000:0000"   // 64 canais de uplink
};

void setup() {
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_R, OUTPUT);
  digitalWrite(LED_PIN_G, LOW);
  digitalWrite(LED_PIN_R, LOW);

  Serial.begin(9600);                            // Comunicação com PC
  Serial2.begin(9600, SERIAL_8N1, 26, 27);       // Comunicação com o módulo (TX=26, RX=27)

  configurarCredenciais();
  LoRa.begin(true);
  delay(500);

  Serial.println("\n🚀 Iniciando teste automático de sub-bandas...\n");

  for (int i = 0; i < 9; i++) {
    Serial.print("🛰️  Testando Sub-banda ");
    Serial.print(i);
    Serial.print(" → AT+CHMASK=");
    Serial.println(chmask_list[i]);

    // Envia comando AT diretamente via Serial2
    LoRa.CHMASK(chmask_list[i]);
    delay(1000); // Tempo para o módulo aplicar

    // Tenta o join
    bool joined = LoRa.JoinNetwork(OTAA, net, true, false);

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
  // Nada aqui
}
