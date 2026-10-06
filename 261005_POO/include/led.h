#include <arduino.h>
#ifndef LED_H
#define LED_H

class Led
{
public:
    uint8_t _pino;
    bool _estado = 0;
    uint32_t  _tempoAnterior = 0;
    uint32_t  _intervalo = 500;
    bool _piscando = 0;
    
    Led(uint8_t pino);
    void iniciar();
    void ligar();
    void desligar();
    void piscar(uint32_t intervalo);
    void ativarPiscar();
    void desativarPiscar();
    void atualizar();


};



#endif