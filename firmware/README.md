# 🔧 Firmware – Dispositivos IoT

Este diretório contém o firmware desenvolvido para os dispositivos ESP32 utilizados nos dois circuitos do projeto **Aumento da Segurança em Redes IoT Utilizando a Blockchain e o Protocolo LoRaWAN**.


## 📁 Estrutura da pasta `firmware/`

- **`ChirpStackAPI/`**  
  Scripts e testes relacionados à integração com o stack de rede **ChirpStack**, utilizados em etapas preliminares do projeto.

- **`lib/`**  
  Bibliotecas utilizadas no firmware, incluindo drivers para sensores (`DHT11`, `INA3221`), comunicação (`LoRaWAN`), JSON, entre outras.  
  ➜ Veja mais detalhes no [`README` da pasta lib](./lib/README.md).

- **`src/`**  
  Código-fonte principal do firmware embarcado nos dispositivos, com os sketches utilizados nos circuitos C1 (sensor de temperatura/umidade) e C2 (medidor de consumo).

- **`tago/`**  
  Scripts auxiliares e estruturas de payload usados para teste e integração com a **plataforma TagoIO**, que substituiu o uso de GCP por simplicidade e eficiência no monitoramento.
  

## 📚 Mais informações

Para uma explicação detalhada sobre a lógica dos circuitos, sensores utilizados, conexão com a rede Helium, estrutura de mensagens e mais:

➡️ Acesse a [Wiki do repositório](https://github.com/Gzanini/helium-iot-security/wiki)


