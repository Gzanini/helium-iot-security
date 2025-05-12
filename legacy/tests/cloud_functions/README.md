# Testes manuais com envio de payload

Este diretório contém instruções e utilitários para testar o envio de mensagens simuladas para o Pub/Sub e os endpoints no Cloud Run.

## Pré-requisitos

- Ter o `gcloud` instalado e autenticado
- Ter permissões no projeto `helium-iot-tcc`

## Autenticação e seleção de projeto

```bash
gcloud auth login
gcloud config set project helium-iot-tcc
```

## Teste 1: Enviar mensagem diretamente para o tópico Pub/Sub

```bash
gcloud pubsub topics publish helium-data --message="{\"device_eui\":\"test-123456789ABCDEF0\",\"temperature\":22.5,\"humidity\":60.2}"

```

## Teste 2: Enviar para função que salva no GCS via CURL
Antes de enviar, converta o JSON em base64 (pode usar sites online ou script `.bat` incluído):

```bash
echo '{"device_eui":"test-123456789ABCDEF0","temperature":22.5,"humidity":60.2}' | openssl base64
```

Exemplo de envio:

```bash
curl -X POST "https://save-payload-to-gcs-970915750461.us-central1.run.app/" \
  -H "Content-Type: application/json" \
  -d "{\"message\": {\"data\": \"eyJkZXZpY2VfZXVpIjoidGVzdC0xMjM0NTY3ODlBQkNERUYwIiwidGVtcGVyYXR1cmUiOjIyLjUsImh1bWlkaXR5Ijo2MC4yfQ==\"}}"
```

## Teste 3: Enviar para função que salva no BigQuery via CURL
Antes de enviar, converta o JSON em base64 (pode usar sites online ou script `.bat` incluído):

```bash
echo '{"device_eui":"test-123456789ABCDEF0","temperature":22.5,"humidity":60.2}' | openssl base64
```

Exemplo de envio:

```bash
curl -X POST "https://insert-payload-to-bigquery-970915750461.us-central1.run.app/" \
  -H "Content-Type: application/json" \
  -d "{\"message\": {\"data\": \"eyJkZXZpY2VfZXVpIjoidGVzdC0xMjM0NTY3ODlBQkNERUYwIiwidGVtcGVyYXR1cmUiOjIyLjUsImh1bWlkaXR5Ijo2MC4yfQ==\"}}"
```

## Teste 4: Enviar via script `.bat` no Windows

Use o script `send_payload.bat` passando os 3 parâmetros:

```bash
send_payload.bat <device_eui> <temperature> <humidity>
```

Exemplo:

```bash
send_payload.bat test-123456789ABCDEF0 22.5 60.2
```

O script irá codificar os dados, gerar o JSON base64 e enviá-lo corretamente para o tópico `helium-data` no Pub/Sub.