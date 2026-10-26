#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* apiPokemon = "https://pokeapi.co/api/v2/pokemon/";
const char* nomePokemon = "charizard";
String pedirParaApi(String codigo);



void iniciarWifi();

void setup() 
{
  Serial.begin(115200);
  iniciarWifi();
  
  String inserirNome;
  inserirNome = pedirParaApi(nomePokemon);

  JsonDocument doc;

  DeserializationError errorJson = deserializeJson(doc, inserirNome);

  String nome = doc["name"] | "Não informado";

  int id = doc["id"] | -1;

  float height = doc["height"] | -1.0f;

  float weight = doc["weight"] | -1.0f;

  nome.toLowerCase();

  Serial.printf("\n\rID : %i\n\r", id);
  Serial.printf("Nome: %s\n\r", nome.c_str());
  
  height >= 0
  ? Serial.printf("Altura: %.2f\n\r", height)
  : Serial.printf("Nao informado\n\r");

  weight >= 0
  ? Serial.printf("Peso: %.2f\n\r", weight)
  : Serial.printf("Nao informado\n\r");

}

void loop() 
{
  
}

void iniciarWifi()
{
  const char* nomeRedeWiFi = "SENAI EDUCACIONAL";
  const char* senhaRedeWiFi = "info@134";

  WiFi.begin(nomeRedeWiFi, senhaRedeWiFi);

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("#");
    delay(500);
  }
}

String pedirParaApi(String codigo)
{
  HTTPClient http;

  http.begin(apiPokemon + codigo);

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