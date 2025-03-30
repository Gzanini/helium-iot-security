import base64
import json
from datetime import datetime
from google.cloud import bigquery

def handle_lorawan_message(event, context):
    if 'data' not in event:
        print("Evento sem campo 'data'")
        return

    try:
        decoded_data = base64.b64decode(event['data']).decode('utf-8')
        payload = json.loads(decoded_data)
    except Exception as e:
        print(f"❌ Erro ao decodificar payload: {e}")
        return

    payload["timestamp"] = datetime.utcnow().isoformat()

    try:
        client = bigquery.Client()
        table_id = "helium-iot-tcc.helium_data.sensor_readings"
        rows_to_insert = [{
            "device_eui": payload.get("devEUI", "unknown"),
            "timestamp": payload["timestamp"],  # YYYY-MM-DDTHH:MM:SSZ
            "temperature": float(payload.get("decoded", {}).get("temperature", 0)),
            "humidity": float(payload.get("decoded", {}).get("humidity", 0))
        }]
        errors = client.insert_rows_json(table_id, rows_to_insert)
        if errors:
            print(f"Erros ao inserir no BigQuery: {errors}")
        else:
            print("Dados inseridos no BigQuery com sucesso.")
    except Exception as e:
        print(f"Erro geral: {e}")
