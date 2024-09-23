//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Instituicao......: FACULDADE ESTACIO
// Curso............: ANALISE E DESENVOLVIMENTO DE SISTEMAS
// Aluno............: RAFAEL BUENO DOS SANTOS
// Periodo..........: 
// Projeto..........: IOT - INTERNET DAS COISAS
// Descricao........: LIGAR OU DESLIGAR UM EQUIPAMENTO PELA INTERNET ATRAVES DE UM ARDUINO/NODEMCU
//                    AQUI SIMULANDO PARA LIGAR UM LED (QUE PODE SER SUBSTITUIDO POR UM RELÊ PARA ACIONAR
//                    QUALQUER OUTRO DISPOSITIVO ELETRICO
// Data.............: AGOSTO/2024
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<ThingSpeak.h>
#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>

unsigned long channel_num= 403718;      // Numero do canal configurado dentro do site ThingSpeak
const char* ssid = "VIVOFIBRA-RAFA";    // ID da conexão de internet
const char* senha = "M1NH4C4S4#";       // Senha

int led;                                // Variavel que vai definir o estado que o led vai estar

WiFiClient cliente;                     // Cliente WiFi que se conecta ao servidor do ThingSpeak 
ESP8266WebServer servidor_web(80);      // Cria o servidor web no NodeMcu

void setup() {
  // put your setup code here, to run once:
  pinMode(D1,OUTPUT);                   // Inicializar o pino que será utilizado do NodeMcu para conectar o Led
  digitalWrite(D1,0);                   // Setar o pino em que esta o led como desligado
  Serial.begin(115200);
  WiFi.begin(ssid,senha);               // Autenticamos no servidor para ser conectar a internet
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());      // Imprime o IP do servidor local
  servidor_web.on("/", conectar);      //  "/" é em relação a raiz. Conectamos o servidor web interno
  ThingSpeak.begin(cliente);           // Conecta o cliente ao servidor do ThingSpeak
  servidor_web.begin();                // Inicia o servidor web local
}

void loop() {
  // put your main code here, to run repeatedly:
  servidor_web.handleClient();                     // Chama a função para atender ao usuario
  led=ThingSpeak.readFloatField(channel_num,3);    // Lê o dado do campo 3 do ThingSpeak e seta o led de acordo
  if(led==1)
  {
    digitalWrite(D1,1);
  }
  else if(led==0)
  {
    digitalWrite(D1,0);
  }
}

void conectar()
{
   servidor_web.send(200,"text/html", pagina());
}

String pagina(void)
{

 String ptr = "<!DOCTYPE html> <html>\n";

 ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
 ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
 ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
 ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
 ptr +=".button-on {background-color: #1abc9c;}\n";
 ptr +=".button-on:active {background-color: #16a085;}\n";
 ptr +=".button-off {background-color: #34495e;}\n";
 ptr +=".button-off:active {background-color: #2c3e50;}\n";
 ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
 ptr +="</style>\n";
 ptr +="</head>\n";

 ptr +="<body>\n";
 ptr +="<h1>Conexao ao servidor ThingSpeak </h1>\n";
 ptr +="<h3>Usuario -> NodeMcu -> ThingSpeak </h3>\n";
 ptr +="<h4>Acionamento do pino D1</h4>\n";
 ptr +="<a class=\"button button-on\"  href=\"https://api.thingspeak.com/update?api_key=J0XM0G7YMCFOEV9L&field3=1\">ON</a>\n";
 ptr +="<a class=\"button button-off\" href=\"https://api.thingspeak.com/update?api_key=J0XM0G7YMCFOEV9L&field3=0\">OFF</a>\n";
 ptr +="</body>\n";
 ptr +="</html>\n";
 return ptr;

}
