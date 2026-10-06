#ifndef led_h
#define led_h

#include <Arduino.h>

class Led
{
    private:

    uint8_t _pinoLed;
    bool _estadoLed = 0;
    bool _estaPiscando = 0;
    uint32_t _tempoAnteriorAcionamento_ms;
    uint32_t _intervaloPiscarAmarelo_ms = 200;
    uint32_t _intervaloPiscarVermelho_ms = 1000;

};

#endif
