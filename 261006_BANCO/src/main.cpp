#include <Arduino.h>
#include "led.h"
#include "botao.h"

Led ledAmareloA(15);

Botao btn(13);

void setup()
{
  Serial.begin(9600);
  ledAmareloA.iniciar();
  btn.iniciar();
  btn.setTempoDebounce(2);
}

void loop() 
{
  if(btn.pressionou())
  {
    //ledAmareloA.piscaPisca(10);
    ledAmareloA.alternar();
    Serial.println("sim");
  }
  if(btn.soltou())
  {
    Serial.println("nao");
  }
  ledAmareloA.atualizar();
  btn.atualizar();
  
 // Serial.print(btn.pressionou());
}