#ifndef botao_h
#define botao_h

#include <Arduino.h>
#include <Botao.h>
#include "led.h"

class Botao
{


    public:
    void BotaoCima();
    void BotaoBaixo();
    void BotaoPressionado();
};


#endif