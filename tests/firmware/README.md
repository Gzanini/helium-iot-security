# Firmware Tests

Esta pasta contém códigos de teste desenvolvidos com ESP32 para integração com redes LoRaWAN (Helium) utilizando diferentes módulos.

Cada sketch está em uma pasta separada, conforme exigido pela Arduino IDE. Abaixo você encontra uma descrição rápida de cada exemplo e links para download.


## 📂 Testes disponíveis

### 🔹 [`join_OTAA_test`](join_OTAA_test/join_OTAA_test.ino)
Testa a conexão via OTAA com a rede Helium usando **ESP32 + módulo LoRa RFM95W (915 MHz)**.

- Utiliza dois LEDs como feedback visual:
  - LED verde indica conexão bem-sucedida
  - LED amarelo indica falha na conexão
- No terminal serial (baud rate 115200), exibe os logs do processo de conexão com a rede LoRaWAN (eventos LMIC).
- Ideal para validar a comunicação com a rede Helium.

### 🔹 [`LoRaWAN_OTAA_Example`](LoRaWAN_OTAA_Example/LoRaWAN_OTAA_Example.ino)
Teste de envio LoRaWAN utilizando **ESP32 + módulo LoRaWAN da Radioenge (código RD49C)** com a biblioteca `LoRaWAN_Radioenge`.

- Realiza join via OTAA com a TTN.
- Envia uma mensagem de texto `"elcereza.com"` no canal 1 após a conexão.
- Aciona o GPIO 2 alternando entre HIGH e LOW a cada 5 segundos.
- Exibe os parâmetros do módulo via `printParameters()` no terminal.

📝 **Baseado no código do repositório:** [github.com/elcereza/LoRaWAN](https://github.com/elcereza/LoRaWAN)  
