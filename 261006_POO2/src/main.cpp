#include <Arduino.h>
#include "led.h"

Led ledAmareloA(4);
Led ledAmareloB(5);
Led ledAmareloC(6);
Led ledAmareloD(7);



void setup()
{
  ledAmareloA.iniciar();
  ledAmareloB.iniciar();
  ledAmareloC.iniciar();
  ledAmareloD.iniciar();

  ledAmareloA.ativarPiscar(400);
  ledAmareloB.ativarPiscar(800);
  ledAmareloC.ativarPiscar(1600);
  ledAmareloD.ativarPiscar(3200);
}

void loop() 
{
  ledAmareloA.atualizar();
  ledAmareloB.atualizar();
  ledAmareloC.atualizar();
  ledAmareloD.atualizar();
}