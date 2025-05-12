import requests

# === CONFIGURAÇÕES ===
DEVICE_TOKEN = "7ca06cb3-c03c-449e-8f3e-1eae4869df83"  # Device Token do TagoIO
HEADERS = {
    "Content-Type": "application/json",
    "Device-Token": DEVICE_TOKEN
}

# === FUNÇÃO PARA ENVIAR UM DADO ===
def enviar_variavel(variavel, valor, data_iso):
    payload = {
        "variable": variavel,
        "value": valor,
        "time": data_iso,  # aparecerá como 'Time' no Tago
        "metadata": {
            "source": "helium-terminal"
        }
    }
    response = requests.post("https://api.tago.io/data", json=payload, headers=HEADERS)
    print(f"[{variavel}] -> {response.status_code}: {response.text}")

def enviar_variavel_unidade(variavel, valor, data_iso, unidade):
    payload = {
        "variable": variavel,
        "value": valor,
        "unit": unidade,
        "time": data_iso,  # aparecerá como 'Time' no Tago
        "metadata": {
            "source": "helium-terminal"
        }
    }
    response = requests.post("https://api.tago.io/data", json=payload, headers=HEADERS)
    print(f"[{variavel}] -> {response.status_code}: {response.text}")


# === EXECUÇÃO DIRETA ===
if __name__ == "__main__":
    # ✅ DEFINA AQUI OS VALORES A ENVIAR
    data_alvo = "2025-04-30"  # Formato ISO 8601, obrigatório para 'time'
    uplink = 20
    up_copy = 0
    downlink = 3
    join = 0
    uplink_mic = 0
    dc_balance = 97675
    weekly_dc_cost = 232 #somar o custo dos ultimos 7 dias da tabela
    total_requests_dia_anterior = 354 #somar todos os ultimos dias na Tago para o campo total_requests_all_time


    # 🚀 ENVIO PARA O TAGOIO
    total_requests = (uplink + up_copy + downlink + join)
    total_requests_all_time = total_requests + total_requests_dia_anterior
    enviar_variavel("uplink", uplink, data_alvo)
    enviar_variavel("up_copy", up_copy, data_alvo)
    enviar_variavel("downlink", downlink, data_alvo)
    enviar_variavel("join_error", join, data_alvo)
    enviar_variavel("total_requests", total_requests, data_alvo)
    enviar_variavel("total_requests_all_time", total_requests_all_time, data_alvo)
    enviar_variavel("uplink_mic", uplink_mic, data_alvo)

    dc_cost = (100000 - dc_balance)
    enviar_variavel_unidade("dc_balance", dc_balance, data_alvo, "DCs")
    enviar_variavel_unidade("dc_cost", dc_cost, data_alvo, "DCs")
    # enviar_variavel_unidade("weekly_dc_cost", weekly_dc_cost, data_alvo, "DCs")

    print("✅ Dados enviados com sucesso para o TagoIO!")