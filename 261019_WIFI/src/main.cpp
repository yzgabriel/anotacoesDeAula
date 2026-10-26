#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>

const char* nomeRedeWiFi = "SENAI EDUCACIONAL";
const char* senhaRedeWiFi = "info@134";
const char* enderecoApiClima = "https://wttr.in/Sao+Caetano+do+Sul?m&lang=pt&format=";

String pedirParaApiClima(String codigo);


LiquidCrystal_I2C lcd(0x27,20,4); 

//*================SERVIDOR NTP=======================
const char* SERVIDOR_NTP_1 = "a.st1.ntp.br";
const char* SERVIDOR_NTP_2 = "pool.ntp.org";
const char* FUSO_HORARIO = "<-03>3";
const char* DIAS_SEMANA_PTBR[] = {"Domingo",
                                  "Segunda-feira",
                                  "Terca-feira",
                                  "Quarta-feira",
                                  "Quinta-feira",
                                  "Sexta-feira"};


void setup() 
{
   Serial.begin(115200);
   WiFi.begin(nomeRedeWiFi, senhaRedeWiFi);
    lcd.init();
    lcd.backlight();

   Serial.print("\n\nIniciando conexão WiFi.......\n\r");

   while(WiFi.status() != WL_CONNECTED)
  {
   Serial.print("#");
   delay(500);
  }
   Serial.print("\n\rConectado com sucessso!\n\r");
   Serial.printf("Endereço IPv4: %s\n\r", WiFi.localIP().toString().c_str());
   Serial.printf("Endereço MASC: %s\n\r", WiFi.macAddress().c_str());

   //*Configuração de Fuso horario, servidores NTP e inicia a sicronização
  configTzTime(FUSO_HORARIO, SERVIDOR_NTP_1, SERVIDOR_NTP_2);

  struct tm agora;

  Serial.print("\n\rSicronizando servidor NTP");

  while(!getLocalTime(&agora)) //* Parametro é o endereço (&) da estrutura que ira receber os dados
  {
    Serial.print(".");
    delay(500);
  } 
  Serial.print("\n\rHora Sicronizada com sucesso");



  String cidade;
   String clima;
   int temperatura;
   int sensacaoTermica;
   

   clima = pedirParaApiClima("%C");
   temperatura = pedirParaApiClima("%t").toInt();
   sensacaoTermica = pedirParaApiClima("%f").toInt();
   cidade = pedirParaApiClima("%l");

   Serial.printf("Condição Climática para hoje: %s\n\r", clima.c_str());
   Serial.printf("Temperatura Atual %dC de sensação Térmica %dC", temperatura, sensacaoTermica);

   lcd.setCursor(0,0);
   lcd.printf("%s", cidade.c_str());
   lcd.setCursor(0,1);
   lcd.printf("Temperatura: %dC", temperatura);
   lcd.setCursor(0,2);
   lcd.printf("Sensacao: %dC", sensacaoTermica);
}

void loop() 
{
  struct tm agora;

  if(getLocalTime(&agora))
  {
    Serial.printf("Hoje é %s, %02d/%02d/%d - %02d:%02d:%02d\n\r",
                  DIAS_SEMANA_PTBR[agora.tm_wday],
                  agora.tm_mday,
                  1 + agora.tm_mon,
                  1900 + agora.tm_year,
                  agora.tm_hour,
                  agora.tm_min,
                  agora.tm_sec);

                  time_t epoch_time = mktime(&agora);
                  Serial.printf("Timestamp: %d\n\r", epoch_time);
                  delay(1000);
  }


    lcd.setCursor(0,3);
    lcd.printf("Horario: %02d:%02d:%02d",
                  agora.tm_hour,
                  agora.tm_min,
                  agora.tm_sec);
        
}


String pedirParaApiClima(String codigo)
{
  HTTPClient http;

  http.begin(enderecoApiClima + codigo);

  int codigoHTTP = http.GET(); //* Retorna o código HTTP ex : 200 -> OK | 404 -> página não encontrada
String resposta = "";

  if (codigoHTTP == 200)
  {
      resposta = http.getString(); //* Retorna o conteudo HTML da página
  }
  else
  {
      Serial.printf("Deu erro. Código: %d", codigoHTTP);
  }

  http.end();
  return resposta;


}
