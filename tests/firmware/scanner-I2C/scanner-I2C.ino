#include <Wire.h>

void setup() {
  Wire.begin(19, 21);  // SDA, SCL
  Serial.begin(115200);
  Serial.println("I2C scanner...");
  
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Dispositivo I2C encontrado no endereço 0x");
      Serial.println(address, HEX);
    }
    delay(10);
  }
}

void loop() {}
