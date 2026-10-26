#include <Arduino.h>
#include <ArduinoJson.h>



void setup() 
{
  Serial.begin(115200);
  
  uint32_t quantidade = 30UL;
  float temperatura1 = 2.8f;
  float temperatura2 = 37.89f;
  float temperatura3 = 130.5f;
  bool estaLigado = false;
  const char* nomeDispositivo = "ESP32-S3";
  int pinosUsados[] = {1, 4, 6, 13, 37, 41};

  //* O heap é a área da RAM usada para alocação dinâmica
  //* é reservada e liberada durante a execução, conforme a necessidade
  //*
  //* Outras áreas da RAM
  //* - Memória estática guarda variaveis globais e static
  //* - Pilha (stack) guarda variáveis locais das funções

  Serial.printf("Inicial - Heap livre: %u\n\r", ESP.getFreeHeap());
  Serial.printf("Inicial - Maior bloco de memória livre %u bytes\n\r", ESP.getMaxAllocHeap());

  JsonDocument doc;

  doc["quantidade"] = quantidade;
  doc["estaLigado"] = estaLigado;
  doc["nomeDispositivo"] = nomeDispositivo;

  //* ==============ARRAY / VETOR===============
  JsonArray pinos = doc["pinos"].to<JsonArray>();
  
  size_t tamanhoVetorPinos = sizeof(pinosUsados) / sizeof(pinosUsados[0]);
  
  //* Jeito 1 para todos os casos
  for(int i = 0; i < tamanhoVetorPinos; i++)
  {
    pinos.add(pinosUsados[i]);
  }

  //* Jeito 2 apenas para numeros ou booleanos
  pinos.clear();

  copyArray(pinosUsados,tamanhoVetorPinos, pinos);
  
  //* ========OBJETOS JSON============
  JsonObject temps = doc["temperaturas"].to<JsonObject>();
  temps["sensor1"] = temperatura1;
  temps["sensor2"] = temperatura2;
  temps["sensor3"] = temperatura3;

  Serial.printf("FINAL - Heap livre: %u\n\r", ESP.getFreeHeap());
  Serial.printf("FINAL - Maior bloco de memória livre %u bytes\n\r", ESP.getMaxAllocHeap());

  bool faltouMemoriaErro = doc.overflowed();

  if(!faltouMemoriaErro) return;

char buffer [512];

serializeJson(doc, buffer, sizeof(buffer));

Serial.println(buffer);

JsonDocument doc2; //* Usado para deserializar o Json recebido

JsonDocument filtro; //* Usado como modelo para o filtro de chaves JSON
filtro["estaLigado"] = true;
filtro["temperaturas"] = true;

DeserializationError ErroJson = deserializeJson(doc2, buffer, DeserializationOption::Filter(filtro));

Serial.println(doc2["estaLigado"].as<bool>() ? "Esta Ligado" : "Esta Desligadox");

Serial.printf("Temp1 : %6.2f\n Temp2 : %6.2f\n Temp3 : %6.2f\n\r",
                doc2["temperaturas"]["sensor1"].as<float>(),
                doc2["temperaturas"]["sensor2"].as<float>(),
                doc2["temperaturas"]["sensor3"].as<float>()
                    );

if(doc2["nomeDispositivo"].is<const char*>()){
  Serial.printf("Nome do dispositivo: %s", doc2["nomeDispositivo"].as<const char*>());
}

else
  Serial.println("Nome do dispositivo não encontrado");

}

void loop()
{

}