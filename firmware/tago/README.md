# 🌐 Integração com a Plataforma TagoIO – `firmware/tago/`

Esta pasta contém os scripts de análise e utilitários utilizados na integração entre os dispositivos embarcados do projeto e a plataforma **TagoIO**, que foi adotada como ambiente principal de visualização e análise de dados.


## 📁 Arquivos e suas funções

### ✅ Análises principais (executadas no TagoIO)

- **`analyze_current_standby_peak.txt`**  
  Analisa os valores de corrente (`radioenge_current` e `total_current`) e classifica os dados em **standby** e **pico** usando média e desvio padrão. Gera variáveis como `standby_total_mA` e `peak_radioenge_mA`.

- **`calculate_energy_metrics.txt`**  
  Calcula o **consumo energético por hora** com base na corrente total e tensão, além da **tensão média** dos sensores e **consumo médio diário estimado**.

- **`copy_device_data.txt`**  
  Copia dados históricos entre dois dispositivos TagoIO. Útil para backup ou migração de dados entre C1 e C2.

- **`count_daily_messages.txt`**  
  Agrupa todas as mensagens da variável `temperature` por data e contabiliza o total de mensagens enviadas por dia (`total_messages_today`).

- **`daily_status_and_message_counter.txt`**  
  Avalia a quantidade de mensagens enviadas no dia e define um **status** (`Ativo` ou `Inativo`) com base no tempo desde a última leitura.

- **`estimate_daily_energy_consumption.txt`**  
  Estima o **número de horas ativas por dia** e calcula o **consumo energético diário** com base nesse tempo. Gera variáveis como `horas_ativas_dia` e `consumo_dia_Wh`.

- **`register_last_update_time.txt`**  
  Salva a **hora formatada da última leitura recebida** da variável `temperature`, útil para monitoramento de conectividade (`last_success`).


### 🧰 Utilitários e auxiliares

- **`payload-parser-c1.txt`**  
  Script usado para **decodificar payloads compactados** vindos do Circuito 1. Exemplo: extrai `T=25.3 H=55.1` e converte para variáveis `temperature` e `humidity` com metadata de conexão.


## 📚 Mais informações

Para mais detalhes sobre a estrutura dos dados, variáveis enviadas e lógica por trás de cada script:

👉 Acesse a [Wiki do projeto](https://github.com/Gzanini/helium-iot-security/wiki)


