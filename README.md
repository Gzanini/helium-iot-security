# Aumento da Segurança em Redes IoT Utilizando a Blockchain e o Protocolo LoRaWAN

**Artigo do TCC:** *Aumento da Segurança em Redes IoT Utilizando a Blockchain e o Protocolo LoRaWAN: Estudo de Caso com a Rede Helium*  
**Curso:** Engenharia da Computação – Universidade do Vale do Rio dos Sinos (Unisinos)

Este repositório contém o código, documentação e experimentos desenvolvidos no **Trabalho de Conclusão de Curso (TCC)** que investiga o uso da tecnologia blockchain aliada ao protocolo LoRaWAN, por meio da **Rede Helium**, para aumentar a segurança em redes de Internet das Coisas (IoT).

---

## 🧠 Resumo

Este trabalho apresenta um estudo sobre a segurança em redes de Internet das Coisas (IoT), com foco na integração do protocolo LoRaWAN à tecnologia blockchain. Como parte prática do projeto, foi implementado um sensor de temperatura e umidade utilizando a rede Helium, que combina LoRaWAN com blockchain para registrar e validar transações de dados. A comunicação entre o dispositivo e a rede foi feita por meio do protocolo MQTT, e os dados foram processados em uma Cloud Function do Google Cloud Platform (GCP), sendo armazenados no BigQuery e em arquivos brutos no Cloud Storage. O objetivo foi avaliar o funcionamento da rede Helium e verificar o potencial de sua estrutura para garantir segurança, escalabilidade e confiabilidade em aplicações IoT.

---

## 🛠 Tecnologias Utilizadas

- **ESP32** – Microcontrolador para controle do sensor e envio via LoRa.
- **Sensor DHT11** – Coleta de temperatura e umidade.
- **Módulo LoRa RFM95W (915 MHz)** – Comunicação via protocolo LoRaWAN.
- **Rede Helium** – Infraestrutura descentralizada de gateways baseada em blockchain.
- **Protocolo MQTT** – Transporte leve e eficiente para mensagens IoT.
- **Google Cloud Platform (GCP)**:
  - **Cloud Pub/Sub** – Recebimento de mensagens LoRaWAN via integração com a Helium.
  - **Cloud Functions** – Processamento automático dos dados recebidos.
  - **BigQuery** – Armazenamento e consulta dos dados estruturados.
  - **Cloud Storage** – Armazenamento de arquivos brutos com payloads recebidos.

---

## 📡 Funcionamento do Sistema

1. O ESP32 lê os dados do sensor DHT11 (temperatura e umidade).
2. Os dados são enviados via LoRaWAN utilizando o módulo RFM95W.
3. A rede Helium recebe os pacotes e os encaminha para um tópico MQTT.
4. O MQTT entrega a mensagem no **Pub/Sub** da GCP.
5. Uma **Cloud Function** é acionada automaticamente:
   - Adiciona timestamp ao conteúdo.
   - Salva o payload bruto no **Cloud Storage**.
   - Salva os dados estruturados no **BigQuery** para consulta futura.

---

## 🗂 Estrutura do Projeto
```
📦 helium-iot-security
├── firmware/                  # Código para ESP32 + LoRa + sensores
│   ├── src/                   # Código-fonte principal (.ino ou .cpp/.h)
│   ├── lib/                   # Bibliotecas utilizadas no projeto (ex: LMIC custom, DHT)
│   └── docs/                  # Esquemáticos de ligação, prints do serial monitor, etc.
│
├── cloud/                     # Código e infraestrutura em nuvem (GCP)
│   ├── functions/             # Cloud Functions para tratar dados
│   ├── pubsub/                # Scripts de criação/configuração de tópicos
│   ├── bigquery/              # Scripts SQL para criação de tabelas
│   └── storage/               # Scripts ou configurações para GCS
│
├── diagrams/                  # Diagramas da arquitetura (Lucidchart, draw.io etc.)
│
├── tests/                     # Testes locais e unitários
│   ├── cloud_functions/       # Testes das funções em nuvem
│   └── firmware/              # Testes simulados no Tinkercad ou plataformas similares
│
├── docs/                      # Documentação geral do projeto (PDFs, referências, etc.)
│   └── tcc/                   # Entregas e versões do TCC (ex: TCC1, TCC2)
│
├── .gitignore
└── README.md
```


---

## 👨‍💻 Autor

**Guilherme Zanini da Silva**  
Aluno de Engenharia da Computação – Unisinos  
Ano de conclusão: 2025

**Orientadora:**  
Profª. Me. Janaina Conceição Sutil Lemos


