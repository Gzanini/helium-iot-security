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

    device_eui = payload.get("device_eui", "unknown_device")
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

# ========== FLASK APP ==========
app = Flask(__name__)

@app.route("/", methods=["POST"])
def handle_request():
    try:
        body = request.get_json(silent=True)
        event = {"data": body.get("message", {}).get("data", "")}
        return handle_lorawan_message(event, None)
    except Exception as e:
        print(f"Erro inesperado: {e}")
        return "Internal error", 500

# ========== EXECUTA O FLASK ==========
if __name__ == "__main__":
    import os
    port = int(os.environ.get("PORT", 8080))
    app.run(host="0.0.0.0", port=port)
