# Configuração LoRaWAN - Módulo Radioenge + ESP32

Manual para configurar e comunicar com o módulo LoRaWAN da Radioenge utilizando um ESP32 via comunicação serial.  
O objetivo é conectar o dispositivo à rede Helium via OTAA (Over-The-Air Activation), utilizando comandos AT.

---

## Informações do Dispositivo

- **Device EUI**: `0012F80000002EF8`  
- **Join EUI (App EUI)**: `9C:6F:4E:7E:25:D9:AF:BB`  
- **App Key**: `EE:BA:57:04:70:87:E0:B5:66:AC:87:68:E9:F6:67:2A`  

---

## Comandos AT Utilizados

```bash
ATZ                                  # Resetar o módulo (opcional para limpar configuração anterior)
AT                                   # Verifica comunicação com o módulo Radioenge
AT+SAVE                              # Salvar
AT+DR=0                              # Define o data rate (DR0 = SF10BW125, ideal para long range)
AT+NJM=1                             # Define o modo de junção como OTAA
AT+APPEUI=9C:6F:4E:7E:25:D9:AF:BB    # Define o Join EUI (Application EUI)
AT+APPKEY=EE:BA:57:04:70:87:E0:B5:66:AC:87:68:E9:F6:67:2A  # Define a chave da aplicação
AT+CHMASK=00FF:0000:0000:0000:0002:0000  # Define a sub-banda (Sub-band 2 no exemplo)
AT+JOIN                              # Inicia o processo de conexão com a rede LoRaWAN
```

## Máscaras de Sub-Bandas US915

Essas máscaras representam os canais ativos em cada sub-banda do plano de frequência US915:

```bash
"FF00:0000:0000:0000:0001:0000",  // Sub-band 0
"00FF:0000:0000:0000:0002:0000",  // Sub-band 1
"0000:FF00:0000:0000:0004:0000",  // Sub-band 2
"0000:00FF:0000:0000:0008:0000",  // Sub-band 3
"0000:0000:FF00:0000:0010:0000",  // Sub-band 4
"0000:0000:00FF:0000:0020:0000",  // Sub-band 5
"0000:0000:0000:FF00:0040:0000",  // Sub-band 6
"0000:0000:0000:00FF:0080:0000"   // Sub-band 7
```