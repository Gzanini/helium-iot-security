#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

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
  .dio = {19, 4, 2},
};

void onEvent(ev_t ev) {
  Serial.print(os_getTime());
  Serial.print(": ");
  switch (ev) {
    case EV_JOINING:
      Serial.println("🔄 Tentando conectar via OTAA...");
      break;
    case EV_JOINED:
      Serial.println("✅ Conectado à rede LoRaWAN via OTAA!");
      break;
    case EV_JOIN_FAILED:
      Serial.println("❌ Falha na conexão OTAA.");
      break;
    default:
      Serial.print("Evento: ");
      Serial.println(ev);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("🔧 Iniciando LMIC para Join Test...");

  SPI.begin(5, 16, 17, 18); // SCK, MISO, MOSI, SS
  os_init();
  LMIC_reset();
  LMIC_selectSubBand(1);
  LMIC_startJoining();
}

void loop() {
  os_runloop_once();
}
