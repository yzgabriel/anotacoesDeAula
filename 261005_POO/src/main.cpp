#include <Arduino.h>
#include "led.h"

Led ledVermelho(41);
Led ledAmarelo(2);
Led ledVerde(1);
Led ledBranco(42);


void setup() 
{
    ledVermelho.iniciar();    
    ledVermelho.piscar(100);
    ledVermelho.ativarPiscar();

    ledAmarelo.iniciar();
    ledAmarelo.piscar(600);
    ledAmarelo.ativarPiscar();

    ledVerde.iniciar();    
    ledVerde.piscar(400);
    ledVerde.ativarPiscar();

    ledBranco.iniciar();
    ledBranco.piscar(1000);
    ledBranco.ativarPiscar();
}

void loop()
{
    ledVermelho.atualizar();
    ledAmarelo.atualizar();
    ledVerde.atualizar();
    ledBranco.atualizar();
}
