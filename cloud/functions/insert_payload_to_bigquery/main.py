import base64
import json
from datetime import datetime
from google.cloud import bigquery
from flask import Flask, request

def handle_lorawan_message(event, context):
    if 'data' not in event:
        print("Evento sem campo 'data'")
        return "Missing data", 400

    try:
        decoded_data = base64.b64decode(event['data']).decode('utf-8')
        payload = json.loads(decoded_data)
    except Exception as e:
        print(f"Erro ao decodificar payload: {e}")
        return "Invalid JSON", 400

    payload["timestamp"] = datetime.utcnow().isoformat() + "Z"

    try:
        client = bigquery.Client()
        table_id = "helium-iot-tcc.helium_data.sensor_readings"
        rows_to_insert = [{
            "device_eui": payload.get("devEUI", "unknown"),
            "timestamp": payload["timestamp"],
            "temperature": float(payload.get("decoded", {}).get("temperature", 0)),
            "humidity": float(payload.get("decoded", {}).get("humidity", 0))
        }]
        errors = client.insert_rows_json(table_id, rows_to_insert)
        if errors:
            print(f"Erros ao inserir no BigQuery: {errors}")
            return "BigQuery insert error", 500
        else:
            print("Dados inseridos no BigQuery com sucesso.")
            return "Success", 200
    except Exception as e:
        print(f"Erro geral: {e}")
        return "Internal error", 500

# ========== FLASK APP PARA CLOUD RUN ==========
app = Flask(__name__)

@app.route("/", methods=["POST"])
def handle_request():
    try:
        body = request.get_json(silent=True)
        if not body:
            return "Empty request", 400

        event = {"data": base64.b64encode(json.dumps(body).encode()).decode()}
        return handle_lorawan_message(event, None)
    except Exception as e:
        print(f"Erro inesperado: {e}")
        return "Internal error", 500
