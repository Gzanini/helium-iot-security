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

REM === Escapa aspas para JSON ficar correto no gcloud ===
set JSON_PAYLOAD={\"device_eui\":\"%DEVICE_EUI%\",\"temperature\":%TEMPERATURE%,\"humidity\":%HUMIDITY%}

REM === Publica no tópico (gcloud converte para base64 automaticamente) ===
gcloud pubsub topics publish helium-data --message="%JSON_PAYLOAD%"

endlocal
