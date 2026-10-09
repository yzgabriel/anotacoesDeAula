#include "led.h"

Led::Led(uint8_t pino) : _pinoLed(pino) //lista de inicializacao
{

}

void Led::iniciar()
{
    pinMode(_pinoLed, OUTPUT);
    digitalWrite(_pinoLed, LOW);
}

void Led::atualizar()
{
        digitalWrite(_pinoLed, _estadoLed);

}

void Led::ligar()
{
    _estadoLed = HIGH;
}

void Led::desligar()
{
    _estadoLed = LOW;
}

void Led::alternar()
{
    _estadoLed = !_estadoLed;
}

void Led::alternarPisca()
{
    _estadoLed = !_estadoLed;
}

uint8_t Led::getPinoLed()
{
    return _pinoLed;
}

void Led::setEstadoLed(bool estadoLed)
{
    _estadoLed = estadoLed;
}

bool Led::getEstadoLed()
{
    return (_estadoLed);
}

void Led::piscaPisca(uint32_t quantidade)
{
  int intervalo = 1000;
  unsigned long tempoAnterior = 0;
  unsigned long tempoAgora = millis();
  for(int i = 0; i < quantidade; i++ )
  {
    if(tempoAgora - tempoAnterior >= intervalo)
    {
      tempoAnterior = tempoAgora;
      ligar();
    }
    
    if(tempoAgora - tempoAnterior >= intervalo)
    {
      tempoAnterior = tempoAgora;
      desligar();
    }
  }
}