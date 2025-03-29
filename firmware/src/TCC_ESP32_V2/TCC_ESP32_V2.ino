#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include "DHT.h"

#define DHTPIN 22
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define BUTTON_PIN 0
#define INTERVAL 3600000  // 1 hora em milissegundos

unsigned long lastSend = 0;
unsigned long lastButtonPress = 0;

// OTAA credentials
static const u1_t PROGMEM APPEUI[8] = { 0xE2, 0xE4, 0x33, 0x38, 0xEC, 0x6C, 0x86, 0xB9 };
static const u1_t PROGMEM DEVEUI[8] = { 0xB5, 0x0E, 0x32, 0x84, 0xDC, 0x46, 0x0F, 0x28 };
static const u1_t PROGMEM APPKEY[16] = { 0xFD, 0xCC, 0x5A, 0x40, 0x8D, 0x08, 0x16, 0xC5, 0x00, 0x29, 0x55, 0xC9, 0x36, 0x57, 0x8F, 0x1F };

void os_getArtEui(u1_t* buf) { memcpy_P(buf, APPEUI, 8); }
void os_getDevEui(u1_t* buf) { memcpy_P(buf, DEVEUI, 8); }
void os_getDevKey(u1_t* buf) { memcpy_P(buf, APPKEY, 16); }

static osjob_t sendjob;

const lmic_pinmap lmic_pins = {
  .nss = 18,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 21,
  .dio = {19, 4, 2}, // DIO0, DIO1, DIO2
};

void onEvent(ev_t ev) {
  switch (ev) {
    case EV_JOINING:
      Serial.println("🔄 Tentando conectar via OTAA...");
      break;
    case EV_JOINED:
      Serial.println("✅ Dispositivo conectado à rede LoRaWAN!");
      break;
    case EV_TXCOMPLETE:
      Serial.println("📤 Dados enviados com sucesso!");
      break;
    default:
      break;
  }
}

void do_send() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("❌ Falha na leitura do DHT11!");
    return;
  }

  Serial.print("📡 Enviando dados - Temperatura: ");
  Serial.print(temperature);
  Serial.print(" °C | Umidade: ");
  Serial.print(humidity);
  Serial.println(" %");

  uint8_t payload[4];
  int16_t temp_int = (int16_t)(temperature * 100);
  int16_t hum_int  = (int16_t)(humidity * 100);

  payload[0] = highByte(temp_int);
  payload[1] = lowByte(temp_int);
  payload[2] = highByte(hum_int);
  payload[3] = lowByte(hum_int);

  LMIC_setTxData2(1, payload, sizeof(payload), 0);
  Serial.println("✅ Pacote LoRa enfileirado para envio!");
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Iniciando LMIC...");
  
  dht.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  SPI.begin(5, 16, 17, 18); // SCK, MISO, MOSI, SS
  os_init();
  LMIC_reset();

  LMIC_startJoining();
  Serial.println("LMIC iniciado com sucesso!");
}

void loop() {
  os_runloop_once();

  if (millis() - lastSend > INTERVAL && (LMIC.devaddr != 0)) {
    lastSend = millis();
    do_send();
  }

  if (digitalRead(BUTTON_PIN) == LOW && millis() - lastButtonPress > 2000 && (LMIC.devaddr != 0)) {
    lastButtonPress = millis();
    Serial.println("Botão pressionado! Enviando agora...");
    do_send();
  }
}
