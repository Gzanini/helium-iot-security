@echo off
setlocal enabledelayedexpansion

REM === Valida parâmetros ===
IF "%~3"=="" (
    echo Uso: send_payload.bat DEVICE_EUI TEMPERATURE HUMIDITY
    exit /b 1
)

set DEVICE_EUI=%~1
set TEMPERATURE=%~2
set HUMIDITY=%~3

REM === Cria JSON e salva no arquivo temporário ===
echo {"device_eui":"%DEVICE_EUI%","temperature":%TEMPERATURE%,"humidity":%HUMIDITY%} > temp_payload.json

REM === Converte para base64 e lê o resultado em uma linha ===
certutil -encode temp_payload.json temp_payload.b64 >nul
set BASE64_DATA=

for /f "skip=1 delims=" %%a in (temp_payload.b64) do (
    if not defined BASE64_DATA (
        set BASE64_DATA=%%a
    )
)

REM === Remove arquivos temporários ===
del temp_payload.json >nul
del temp_payload.b64 >nul

REM === Envia para o tópico Pub/Sub usando gcloud ===
gcloud pubsub topics publish helium-data --message="%BASE64_DATA%"

endlocal
