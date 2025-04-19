#include <Wire.h>
#include "INA3221.h"

INA3221 ina3221(0x40);  // Endereço padrão

#define SDA_PIN 19
#define SCL_PIN 21

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  delay(500);

  Serial.println("Inicializando INA3221...");

  if (!ina3221.begin()) {
    Serial.println("INA3221 não detectado!");
    while (1);
  }

  // Configura canal 0 (CH1)
  ina3221.enableChannel(0);               // Canal 0 é o CH1
  ina3221.setShuntR(0, 0.1);              // Resistor de 0.1 Ohm
  ina3221.setWarningCurrent(0, 3000);     // 3000 mA = 3A (bem alto, só pra não disparar)
  ina3221.setCriticalCurrent(0, 3200);    // Limite ainda maior

  // Modo contínuo
  ina3221.setModeShuntBusContinuous();    // Medição contínua de tensão e corrente

  // Desativa alertas
  ina3221.setMaskEnable(0x0000);          // Desativa todos os alertas

  Serial.println("Configuração finalizada.");
}

void loop() {
  float voltage = ina3221.getBusVoltage_mV(0);
  float current = ina3221.getCurrent_mA(0);

  Serial.print("Tensão (V): ");
  Serial.print(voltage / 1000.0, 3);
  Serial.print(" | Corrente (mA): ");
  Serial.println(current, 3);

  delay(2000);
}
