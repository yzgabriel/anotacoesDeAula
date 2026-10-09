#ifndef __BOTAO_H__
#define __BOTAO_H__

#include <Arduino.h>

class Botao
{
    private:
        uint8_t _pinoBotao;
        bool _estadoAtualBotao = HIGH;
        bool _estadoAnteriorBotao = HIGH;
        bool _pressionou = false;
        bool _soltou = false; 
        bool _estadoUltimaAcao = HIGH;

        uint32_t _ultimaMudanca_ms = 0;
        uint32_t _tempoDebounce_ms = 20;

        uint32_t tempoDecorrido();

    public:
        Botao(uint8_t pino);

        void iniciar();
        void atualizar();
        bool pressionou();
        bool soltou();
        void setTempoDebounce(uint32_t tempo_ms);




};

#endif