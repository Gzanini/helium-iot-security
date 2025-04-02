#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

#define LED_PIN_G 22
#define LED_PIN_Y 23

static const u1_t PROGMEM APPEUI[8]  = { 0x00, 0x00, 0x00, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 }; // padrão TagoIO
static const u1_t PROGMEM DEVEUI[8]  = { 0xB5, 0x0E, 0x32, 0x84, 0xDC, 0x46, 0x0F, 0x28 }; // seu DevEUI
static const u1_t PROGMEM APPKEY[16] = { 0x77, 0xCB, 0x69, 0xBA, 0xA1, 0x00, 0x49, 0x9F,0xB4, 0x50, 0x41, 0x7C, 0xBF, 0x29, 0x6C, 0xDF }; // seu AppKey

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
	  digitalWrite(LED_PIN_G, LOW);
	  digitalWrite(LED_PIN_Y, LOW);
      break;
    case EV_JOINED:
      Serial.println("✅ Conectado à rede LoRaWAN via OTAA!");
	  digitalWrite(LED_PIN_G, HIGH);
	  digitalWrite(LED_PIN_Y, LOW);
      break;
    case EV_JOIN_FAILED:
      Serial.println("❌ Falha na conexão OTAA.");
	  digitalWrite(LED_PIN_G, LOW);
	  digitalWrite(LED_PIN_Y, HIGH);
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
  
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_Y, OUTPUT);
  digitalWrite(LED_PIN_G, LOW);
  digitalWrite(LED_PIN_Y, LOW);

  SPI.begin(5, 16, 17, 18); // SCK, MISO, MOSI, SS
  os_init();
  LMIC_reset();
  LMIC_selectSubBand(1);  // <- ESSENCIAL PARA HELIUM US915
  LMIC_startJoining();
}

void loop() {
  os_runloop_once();
}
