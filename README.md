# Aumento da Segurança em Redes IoT utilizando Blockchain e o Protocolo LoRaWAN

Este repositório contém o projeto desenvolvido por Guilherme Zanini da Silva como parte do Trabalho de Conclusão de Curso (TCC) do curso de Engenharia da Computação na Unisinos. O trabalho propõe uma aplicação prática utilizando a **rede Helium** (Blockchain + LoRaWAN) para comunicação segura em redes IoT.

## 📌 Objetivo

Investigar como a integração da **Blockchain Helium** com o protocolo **LoRaWAN** pode aumentar a segurança, a integridade e a confiabilidade na comunicação de dispositivos IoT, especialmente em ambientes sensíveis.

## ⚙️ Estrutura do Projeto

O projeto é dividido em duas etapas práticas, com circuitos independentes:

### 🔹 Circuito 1 (C1) — Sensor Ambiental (Foco principal e desenvolvido no TCC)
- Sensor DHT11 (temperatura/umidade)
- Módulo LoRaWAN Radioenge RD49C
- Envio de dados para a rede Helium
- Integração com **TagoIO** e **Google Cloud** (Legado)

### 🔹 Circuito 2 (C2) — Medidor de Consumo
- Medição de corrente e tensão (Radioenge INA3221)
- Cálculo de consumo energético
- Scripts de análise foram criados com base no C2 para avaliar a atividade e o consumo do C1

> As análises envolvem estimativa de horas ativas por dia, status do sensor, consumo médio por hora, além de agrupamentos por série para facilitar a visualização no TagoIO.

## 🧠 Scripts e Lógicas Desenvolvidas

Os scripts estão localizados na pasta [`tago/`](./firmware/tago/), e realizam tarefas como:
- Contagem de mensagens por dia
- Estimativa de consumo energético
- Análise de standby e picos de corrente
- Monitoramento do último dado recebido
- Migração de dados entre dispositivos

## 🕰️ Código Legado

O código legado, versões antigas de firmware e scripts descontinuados foram movidos para a pasta [`legacy/`](./legacy) e estão disponíveis apenas para consulta.

## 📖 Documentação Completa

A documentação detalhada com a fundamentação teórica, arquitetura, diagramas, testes, resultados e explicações estendidas dos scripts pode ser encontrada na [Wiki do projeto](https://github.com/Gzanini/helium-iot-security/wiki).

## 👨‍🎓 Sobre

Projeto de Conclusão de Curso (TCC) apresentado à Universidade do Vale do Rio dos Sinos — UNISINOS.  
Orientadora: Prof.ª Me. Janaina Conceição Sutil Lemos.

---
