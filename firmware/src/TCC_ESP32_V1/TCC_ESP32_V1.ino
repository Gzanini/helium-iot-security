#include "DHT.h"
#include <SPI.h>  // Biblioteca para comunicação SPI
#include <LoRa.h> // Biblioteca para comunicação LoRa

// Definições de estados da comunicação LoRaWAN
#define ST_COMM_IDLE        0 // Estado inativo
#define ST_COMM_AT          1 // Estado de envio de comandos AT
#define ST_COMM_JOIN        2 // Tentando ingressar na rede
#define ST_COMM_WAIT_JOIN   3 // Aguardando resposta de associação à rede

// Definição do tipo de sensor e pinos
#define DHTTYPE             DHT11 // Tipo de sensor utilizado
const int DHTPIN = 22; // Pino do ESP32 conectado ao DHT11
const int BUTTON_PIN = 0; // Pino do botão embutido no ESP32

// Credenciais OTAA (Over-The-Air Activation)
const uint8_t APPEUI[8] = { 0xE2, 0xE4, 0x33, 0x38, 0xEC, 0x6C, 0x86, 0xB9 }; // Join EUI
const uint8_t DEVEUI[8] = { 0xB5, 0x0E, 0x32, 0x84, 0xDC, 0x46, 0x0F, 0x28 }; // Device EUI
const uint8_t APPKEY[16] = { 0xFD, 0xCC, 0x5A, 0x40, 0x8D, 0x08, 0x16, 0xC5, 
                             0x00, 0x29, 0x55, 0xC9, 0x36, 0x57, 0x8F, 0x1F }; // Chave de ativação

// Definição dos pinos do módulo LoRa RA-02
#define LORA_MISO  16  // Pino MISO (entrada de dados do LoRa para o ESP32)
#define LORA_MOSI  18  // Pino MOSI (saída de dados do ESP32 para o LoRa)
#define LORA_SCK   17  // Pino SCK (clock do barramento SPI)
#define LORA_NSS   19  // Pino NSS (chip select do módulo LoRa)
#define LORA_RST   21  // Pino RESET do módulo LoRa
#define LORA_DIO0  5   // Pino DIO0 do LoRa (usado para interrupções)

// Variáveis globais para controle da comunicação e leitura dos sensores
int g_CommStatus = ST_COMM_IDLE;
unsigned long g_Time = 0;
unsigned long g_TimeSensorReading = 0;
unsigned long lastButtonPress = 0;
String g_inATString;
DHT g_dht(DHTPIN, DHTTYPE);
float g_Humidity = 0.0;
float g_Temperature = 0.0;
bool g_NetworkJoined = false;

void setup() {
    g_dht.begin();
    Serial.begin(115200); // Inicializa o monitor serial para depuração
    
    // Configuração do barramento SPI para comunicação com o módulo LoRa
    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_NSS);
    LoRa.setPins(LORA_NSS, LORA_RST, LORA_DIO0);

    // Inicializa o LoRa na frequência de 915MHz (Brasil)
    if (!LoRa.begin(915E6)) {
        Serial.println("Falha ao iniciar LoRa!");
        while (1); // Loop infinito em caso de falha na inicialização
    }
    Serial.println("LoRa iniciado com sucesso!");

    pinMode(BUTTON_PIN, INPUT_PULLUP); // Configuração do botão embutido do ESP32
    delay(500);

    Serial.println("\n\n-------- Teste de LoRaWan com DHT11 ----------");
}

void loop() {
    // Lógica de conexão com a rede Helium
    if (millis() - g_Time > 2000) {
        g_Time = millis();
        switch (g_CommStatus) {
            case ST_COMM_IDLE:
                g_CommStatus = ST_COMM_AT;
                break;

            case ST_COMM_AT:
                Serial.println("Iniciando conexão LoRa...");
                g_CommStatus = ST_COMM_JOIN;
                break;

            case ST_COMM_JOIN:
                Serial.println("Tentando ingressar na Helium...");
                LoRa.beginPacket();
                LoRa.print("JOIN");
                LoRa.endPacket();
                g_CommStatus = ST_COMM_WAIT_JOIN;
                break;
        }
    }

    // Verifica se o botão foi pressionado para envio manual
    if (digitalRead(BUTTON_PIN) == LOW) { 
        if (millis() - lastButtonPress > 1000) {
            Serial.println("Botão pressionado! Enviando dados agora...");
            enviarDados();
            lastButtonPress = millis();
        }
    }

    // Envia os dados automaticamente a cada 1 hora (3600000 ms)
    if (millis() - g_TimeSensorReading > 3600000) {
        g_TimeSensorReading = millis();
        enviarDados();
    }
}

void enviarDados() {
    g_Temperature = g_dht.readTemperature(); // Lê temperatura
    g_Humidity = g_dht.readHumidity(); // Lê umidade

    Serial.print("Temperatura: ");
    Serial.print(g_Temperature);
    Serial.println(" °C");

    Serial.print("Umidade: ");
    Serial.print(g_Humidity);
    Serial.println(" %");

    if (g_NetworkJoined) {
        LoRa.beginPacket();
        LoRa.print("T:");
        LoRa.print(g_Temperature);
        LoRa.print(" H:");
        LoRa.print(g_Humidity);
        LoRa.endPacket();
        Serial.println("Dados enviados via LoRa!");
    } else {
        Serial.println("Dispositivo não conectado à rede! Tentando novamente...");
    }
}
