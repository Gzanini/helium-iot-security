# Firmware Tests – `firmware/tests/`

Esta pasta contém os códigos de teste utilizados durante o desenvolvimento e integração dos circuitos com redes LoRaWAN (principalmente Helium), sensores e periféricos. Cada teste foi desenvolvido em um sketch separado para facilitar a validação individual de funcionalidades.

Os testes foram feitos com ESP32, módulos RFM95W e Radioenge RD49C, além de sensores como o INA3221 e periféricos I2C.

## Testes disponíveis

### 🔹 [`join_OTAA_test`](join_OTAA_test/join_OTAA_test.ino)
Valida a conexão LoRaWAN via OTAA utilizando ESP32 + RFM95W (915 MHz) na rede Helium.

- LED verde → conexão bem-sucedida  
- LED amarelo → falha na conexão  
- Exibe eventos LMIC no terminal serial


### 🔹 [`LoRaWAN_OTAA_Example`](LoRaWAN_OTAA_Example/LoRaWAN_OTAA_Example.ino)
Teste de envio LoRaWAN com ESP32 + módulo Radioenge RD49C.

- Envia `"elcereza.com"` após join via OTAA
- Alterna GPIO 2 a cada 5 segundos
- Usa `printParameters()` para debug do módulo

Baseado em: [elcereza/LoRaWAN](https://github.com/elcereza/LoRaWAN)


### 🔹 [`conection-wifi-test`](conection-wifi-test/conection-wifi-test.ino)
Testa a conexão do ESP32 com redes Wi-Fi, utilizado na fase inicial para envio direto via internet antes da integração com LoRaWAN.


### 🔹 [`log-INA3221`](log-INA3221/log-INA3221.ino)
Testa a leitura dos três canais de corrente e tensão do sensor INA3221.

- Exibe leituras contínuas no terminal serial
- Útil para calibrar e validar o consumo energético no C2


### 🔹 [`radioenge_config`](radioenge_config/radioenge_config.ino)
Exibe todos os parâmetros configurados no módulo RD49C da Radioenge usando comandos AT.

- Utilizado para debug e ajustes manuais


### 🔹 [`scanner-I2C`](scanner-I2C/scanner-I2C.ino)
Scanner de barramento I2C para detectar sensores e módulos conectados ao ESP32.

- Útil durante a prototipagem para validar endereço do INA3221 e demais periféricos


### 🔹 [`sub-band-check`](sub-band-check/sub-band-check.ino)
Verifica se o módulo está configurado corretamente na sub-banda da Helium (UA915).


### 🔹 [`unique-sub-band-test`](unique-sub-band-test/unique-sub-band-test.ino)
Teste complementar ao anterior, utilizado para validar que o dispositivo só responde dentro da sub-banda desejada.


## Mais informações

Todos esses testes foram fundamentais para o sucesso da integração final com a rede Helium e estão descritos em detalhes na:

[Wiki do projeto](https://github.com/Gzanini/helium-iot-security/wiki)

