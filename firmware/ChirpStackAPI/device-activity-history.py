import requests
from datetime import datetime
from typing import List

# === CONFIGURAÇÕES ===
BASE_URL = "https://console.helium-iot.xyz/api"
JWT_TOKEN = (
    "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9"
    ".eyJhdWQiOiJjaGlycHN0YWNrIiwiaXNzIjoiY2hpcnBzdGFjayIsInN1YiI6IjY1MTlhM2ExLWJjN2QtNGQwYS04NTY4LTYzMzI3ZT"
    "VkMTg1MiIsInR5cCI6ImtleSJ9.luYFXlgSRimMezfTyasYuDsfAmKRhyy-JS3oEAx-B_E"
)
TENANT_ID = "2d3bf215-5c4b-4126-b759-64cbbaa3821f"
DEV_EUI = "0012f80000002ef8"

HEADERS = {
    "Accept": "application/json",
    "Content-Type": "application/json",
    "Grpc-Metadata-Authorization": f"Bearer {JWT_TOKEN}",
    "Grpc-Metadata-Tenant-Id": TENANT_ID
}


# === FUNÇÃO DE CONSULTA POR TIPO DE FRAME ===
def buscar_frames(dev_eui: str, tipo: str, data_alvo: str) -> List[dict]:
    url = f"{BASE_URL}/devices/{dev_eui}/frames?limit=200&type={tipo}"
    response = requests.get(url, headers=HEADERS)

    if response.status_code != 200:
        print(f"❌ Erro ao buscar frames tipo '{tipo}': {response.status_code}")
        return []

    frames = response.json().get("result", [])

    filtrados = []
    for f in frames:
        ts = f.get("createdAt")
        if ts and ts.startswith(data_alvo):
            filtrados.append(f)

    return filtrados


# === EXECUÇÃO PRINCIPAL ===
if __name__ == "__main__":
    data_str = input("📅 Digite a data que deseja consultar (formato YYYY-MM-DD): ").strip()

    try:
        datetime.strptime(data_str, "%Y-%m-%d")
    except ValueError:
        print("❌ Data inválida. Use o formato YYYY-MM-DD (ex: 2025-04-17).")
        exit(1)

    uplinks = buscar_frames(DEV_EUI, "uplink", data_str)
    downlinks = buscar_frames(DEV_EUI, "downlink", data_str)
    joins = buscar_frames(DEV_EUI, "join", data_str)

    print(f"\n📊 Resumo para {data_str}:")
    print(f" - Uplinks:  {len(uplinks)}")
    print(f" - Downlinks: {len(downlinks)}")
    print(f" - Joins:     {len(joins)}")

    # Dados prontos para enviar ao TagoIO
    total_dcs = len(uplinks) * 1 + len(downlinks) * 1 + len(joins) * 2  # exemplo: 2 DCs por join
    print(f" - Estimativa de consumo: {total_dcs} DCs")
