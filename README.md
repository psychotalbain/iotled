# Projeto IoT: Controle de Equipamento via Internet

Este projeto implementa um sistema de controle de equipamentos elétricos (neste exemplo, um LED) utilizando a placa **NodeMCU (ESP8266)**, conectado à internet. O controle é feito via uma página web simples e por meio da plataforma **ThingSpeak**. Isso permite ligar ou desligar um LED (ou substituir o LED por um relé para controlar qualquer dispositivo) remotamente.

## Descrição

O código neste repositório conecta o NodeMCU a uma rede Wi-Fi e permite controlar o estado de um LED conectado ao pino **D1** da placa, via interface web ou pelo serviço **ThingSpeak**. Um cliente pode acessar o servidor local no NodeMCU para acionar o LED, ou enviar comandos pelo ThingSpeak.

### Componentes principais:
- **NodeMCU (ESP8266)**: Controlador que se conecta à internet e permite comunicação com ThingSpeak.
- **ThingSpeak**: Plataforma utilizada para enviar e receber dados de IoT.
- **LED/Relé**: Dispositivo que será controlado (um LED neste exemplo, mas pode ser substituído por um relé para controlar outros dispositivos).

### Funcionalidades:
- Conexão à rede Wi-Fi.
- Leitura de comandos do ThingSpeak para controlar o LED.
- Interface web local para controlar o LED.
- Exemplo de controle remoto de dispositivos via Internet.

## Instalação

1. **Instale as bibliotecas necessárias**:  
   Certifique-se de que as seguintes bibliotecas estão instaladas no seu Arduino IDE:
   - `ThingSpeak`
   - `ESP8266WiFi`
   - `ESP8266WebServer`

2. **Configuração da Rede Wi-Fi**:
   No arquivo de código, substitua as seguintes variáveis com as informações da sua rede:
   ```cpp
   const char* ssid = "SeuSSID";    // ID da sua rede Wi-Fi
   const char* senha = "SuaSenha";  // Senha da sua rede Wi-Fi
