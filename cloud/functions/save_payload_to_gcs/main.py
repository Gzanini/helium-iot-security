import base64
import json
from datetime import datetime
from google.cloud import storage
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

    device_eui = payload.get("devEUI", "unknown_device")
    timestamp_str = datetime.utcnow().strftime("%Y%m%dT%H%M%S")
    filename = f"raw/{device_eui}_{timestamp_str}.json"

    try:
        client = storage.Client()
        bucket = client.bucket("helium-iot-payloads")
        blob = bucket.blob(filename)
        blob.upload_from_string(json.dumps(payload, indent=2), content_type="application/json")
        print(f"Payload salvo em: {filename}")
        return "Success", 200
    except Exception as e:
        print(f"Erro ao salvar no GCS: {e}")
        return "GCS Error", 500

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
