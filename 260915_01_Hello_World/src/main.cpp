#include <Arduino.h>

int pinLedAmarelo = 42;
int pinLedVerde = 2;
int pinLedVermelho = 1  ;

  
int  estadoLedAmarelo = 0;
int  estadoLedVerde = 0;
int  estadoLedVermelho = 1;


int const intervaloLedVerde = 3;
int const intervaloLedVermelho = 5;

static int contador = 0;
int umSegundo = 1000;


void setup()
{
  
  Serial.begin(9600);
  pinMode(pinLedAmarelo, OUTPUT);
  pinMode(pinLedVerde, OUTPUT);
  pinMode(pinLedVermelho, OUTPUT);
}

void loop()
{
  
  unsigned long tempoAtual = millis();
  static unsigned long tempoInicial = 0;
  
  if(tempoAtual >= tempoInicial + umSegundo)
  {
    contador = contador + 1;
    if(contador >= 10) contador = 0;
    Serial.print(contador);
    tempoInicial = tempoAtual;
  }
  if(contador < intervaloLedVerde)
  {
    estadoLedVermelho = LOW;
    estadoLedVerde = HIGH;
}
  else if(contador < intervaloLedVermelho)
  {
    estadoLedVerde = LOW;
    estadoLedAmarelo = HIGH;
  }
  else
  {
    estadoLedAmarelo = LOW;
    estadoLedVermelho = HIGH;
  }
  digitalWrite(pinLedVermelho, estadoLedVermelho);
  digitalWrite(pinLedAmarelo, estadoLedAmarelo);
  digitalWrite(pinLedVerde, estadoLedVerde);
}
