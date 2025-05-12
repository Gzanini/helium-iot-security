import requests

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


# === FUNÇÃO: CONSULTAR INFORMAÇÕES GERAIS DO DEVICE ===
def consultar_info_dispositivo(dev_eui):
    url = f"{BASE_URL}/devices/{dev_eui}"
    response = requests.get(url, headers=HEADERS)

    if response.status_code != 200:
        print(f"❌ Erro ao buscar informações do dispositivo: {response.status_code}")
        print(response.text)
        return

    device = response.json().get("device", {})

    print("\n📋 Informações Gerais do Dispositivo:")
    print(f" - Nome:               {device.get('name')}")
    print(f" - DevEUI:             {device.get('dev_eui')}")
    print(f" - Application ID:     {device.get('application_id')}")
    print(f" - Device Profile ID:  {device.get('device_profile_id')}")
    print(f" - Tipo de ativação:   {'OTAA' if device.get('skip_fcnt_check') == False else 'ABP'}")
    print(f" - Criado em:          {device.get('created_at')}")
    print(f" - Última modificação: {device.get('updated_at')}")
    print(f" - Ativo:              {device.get('is_disabled') is False}")


# === EXECUÇÃO DIRETA ===
if __name__ == "__main__":
    consultar_info_dispositivo(DEV_EUI)
