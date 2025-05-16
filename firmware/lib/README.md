# Bibliotecas – firmware/lib/

Este diretório contém as bibliotecas utilizadas pelo firmware dos dispositivos ESP32 no projeto Aumento da Segurança em Redes IoT Utilizando a Blockchain e o Protocolo LoRaWAN.

As bibliotecas aqui presentes são responsáveis por viabilizar a leitura dos sensores, a comunicação LoRaWAN com a rede Helium, o tratamento dos dados e o gerenciamento de tempo.


## Bibliotecas incluídas

| Biblioteca       | Finalidade                                                                 |
|------------------|----------------------------------------------------------------------------|
| `DHT11`          | Realiza a leitura de temperatura e umidade via sensor DHT11 (Circuito 1). |
| `INA3221`        | Faz a medição de corrente e tensão em 3 canais via sensor INA3221 (C2).   |
| `LoRaWAN`        | Implementa a comunicação via protocolo LoRaWAN com o módulo RD49C.        |
| `WiFi`           | Biblioteca padrão do ESP32 para debug ou testes de conectividade local.   |
| `ArduinoJson`    | Utilizada para estruturar os dados no formato JSON (usado no envio via serial ou LoRa). |
| `Time`           | Controle de data/hora e formatação de timestamps.                         |
| `ESP32`          | Funções nativas do microcontrolador, como GPIOs, delays, UART, etc.       |


## Observações

- As bibliotecas estão incluídas localmente no repositório para facilitar a compilação do firmware, mesmo sem conexão externa.
- A biblioteca LoRaWAN utilizada é baseada no repositório: [elcereza/LoRaWAN](https://github.com/elcereza/LoRaWAN), com adaptações para integração com o módulo RD49C da Radioenge.
- O firmware pode ser compilado com Arduino IDE.

