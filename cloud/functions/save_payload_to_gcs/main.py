import base64
import json
from datetime import datetime
from google.cloud import storage

def handle_lorawan_message(event, context):
    if 'data' not in event:
        print("Evento sem campo 'data'")
        return
    
    try:
        decoded_data = base64.b64decode(event['data']).decode('utf-8')
        payload = json.loads(decoded_data)
    except Exception as e:
        print(f"Erro ao decodificar payload: {e}")
        return

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
    except Exception as e:
        print(f"Erro ao salvar no GCS: {e}")
