# Código-fonte dos Dispositivos – `firmware/src/`

Esta pasta contém os firmwares desenvolvidos para os dois circuitos do projeto de TCC, programados para o microcontrolador ESP32, utilizando sensores físicos e comunicação LoRaWAN via módulo Radioenge RD49C.

## Arquivos disponíveis

### 🔹 `tcc-helium-c1.ino`
Firmware responsável pelo Circuito 1, que realiza a leitura de dados ambientais.

**Funcionalidade:**
- Leitura de temperatura e umidade com o sensor DHT11
- Envio dos dados via LoRaWAN
- Formatação leve do payload (`T=xx.x H=yy.y`)
- Operação contínua com prioridade na simplicidade e estabilidade

### 🔹 `tcc-helium-c2.ino`
Firmware do Circuito 2, utilizado para monitoramento de consumo de energia elétrica.

**Funcionalidade:**
- Leitura de tensão e corrente nos canais do sensor INA3221
- Cálculo de consumo estimado (com base em amostragens)
- Transmissão de dados estruturados via LoRaWAN
- Envio de múltiplas variáveis em um único ciclo (ex: `radioenge_current`, `radioenge_voltage`, etc.)

## Mais detalhes

A explicação completa sobre o funcionamento de cada circuito, esquema de ligação dos sensores, e como esses dados são processados está disponível na:

[Wiki do projeto](https://github.com/Gzanini/helium-iot-security/wiki)

