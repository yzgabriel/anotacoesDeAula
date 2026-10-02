/*
 Projeto: Funcoes
  Descrição: Funcoes
  Autor: Gabriel Chinaglia
  Data: 02/10/2026
  Versão 0.1
*/

#include <Arduino.h>
#include "func.h"

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  for (int i = 0; i < 10; i++)
  {
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(obterNomeDaCor(i));
  }

  Serial.print("media entre 27.2 e 43.8 é : ");
  Serial.println( calcularMedia(27.2 , 43.8));

  if(verificarTemperatura(30, 35))
    Serial.println("Temperatura OK");
  if(verificarTemperatura(36, 35))
    Serial.println("Temperatura OK");
  else
    Serial.println("Temperatura Alta!");

  while (botaoEstaPressionado(0))
  {
    Serial.println("Botao pressionado");
  }

}


