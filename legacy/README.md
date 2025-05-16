# Código Legado – `legacy/`

Esta pasta contém as primeiras versões do projeto, que foram mantidas para fins de consulta e histórico de desenvolvimento.

## O que está incluído aqui

- Versões iniciais do firmware Arduino, utilizadas para testes locais e envio direto via Wi-Fi.
- Scripts de integração com o Google Cloud Platform (GCP) desenvolvidos na fase inicial do projeto.
- Códigos de prototipagem e testes que foram posteriormente substituídos por versões mais otimizadas.


## Por que migramos para o TagoIO?

Inicialmente, o projeto utilizava a Google Cloud (BigQuery + Cloud Storage) como destino final para os dados dos sensores, com uma estrutura baseada em APIs, scripts Python e Cloud Functions.

Contudo, alguns fatores motivaram a migração para a plataforma TagoIO:

- Facilidade de configuração de dashboards (ambiente no-code).
- Suporte nativo ao protocolo LoRaWAN e integração com a rede Helium.
- Menor custo e menor complexidade para a visualização dos dados.
- Redução na quantidade de componentes e serviços intermediários (sem necessidade de criar APIs ou rotas para ingestão).

Com a adoção do TagoIO, foi possível centralizar:
- A recepção dos dados via Webhook,
- A visualização em tempo real dos sensores,
- E a execução de análises (scripts de automação) diretamente na plataforma.


## Observação

Todo o conteúdo da pasta `legacy/` está congelado e não representa a versão final do projeto. O código atualizado pode ser encontrado nas pastas:

- [`firmware/srs`](./firmware/src) – Código embarcado atualizado (C1 e C2)
- [`analysis/`](./firmware/tago) – Scripts executados via TagoIO para análise dos dados
- [`ChirpStackAPI/`](./firmware/src) – Códigos .py para extrair dados da ChirpStackAPI e envio para TagoIO.

