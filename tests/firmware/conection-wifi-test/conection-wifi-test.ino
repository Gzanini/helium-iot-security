#include <WiFi.h>

#define LED_OK 4     // LED verde (Wi-Fi OK)
#define LED_ERR 22   // LED vermelho (erro)

const char* ssid = "Sebratel492";
const char* password = "f0f1nha2020";

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_OK, OUTPUT);
  pinMode(LED_ERR, OUTPUT);
  digitalWrite(LED_OK, LOW);
  digitalWrite(LED_ERR, LOW);

  Serial.println("\n📡 Escaneando redes Wi-Fi próximas...");
  int n = WiFi.scanNetworks();

  if (n == 0) {
    Serial.println("⚠️ Nenhuma rede Wi-Fi encontrada!");
    digitalWrite(LED_ERR, HIGH);
    return;
  }

  Serial.printf("🔍 %d redes encontradas:\n", n);
  bool redeEncontrada = false;
  for (int i = 0; i < n; ++i) {
    String foundSSID = WiFi.SSID(i);
    Serial.printf("📶 %s | RSSI: %d dBm | Segurança: %s\n",
      foundSSID.c_str(),
      WiFi.RSSI(i),
      (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Aberta" : "Protegida"
    );

    if (foundSSID == ssid) {
      redeEncontrada = true;
    }
  }

  if (!redeEncontrada) {
    Serial.println("\n❌ Rede desejada não encontrada!");
    digitalWrite(LED_ERR, HIGH);
    return;
  }

  Serial.println("\n➡️ Tentando conectar na rede desejada...");
  WiFi.begin(ssid, password);

  unsigned long startAttemptTime = millis();
  const unsigned long timeout = 15000; // 15s para conectar

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Conectado com sucesso!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    digitalWrite(LED_OK, HIGH);
  } else {
    Serial.println("\n❌ Falha ao conectar ao Wi-Fi.");
    digitalWrite(LED_ERR, HIGH);
  }
}

void loop() {
  delay(2000);
  Serial.println("Loop rodando...");
}
