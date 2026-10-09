#include "botao.h"


Botao::Botao(uint8_t pino) : _pinoBotao(pino)
{

}

void Botao::iniciar()
{
    pinMode(_pinoBotao, INPUT_PULLUP);
}

void Botao::atualizar()
{
    _pressionou = false;
    _soltou = false;

    _estadoAtualBotao = digitalRead(_pinoBotao);

    if(_estadoAtualBotao != _estadoAnteriorBotao)
    {
        _ultimaMudanca_ms = millis();
        _estadoAnteriorBotao = _estadoAtualBotao;
        return;
    }
    if(tempoDecorrido() < _tempoDebounce_ms)
        return;
    if (_estadoUltimaAcao == _estadoAtualBotao)
    return;

    _estadoUltimaAcao = _estadoAtualBotao;

    _estadoAtualBotao 
    ? _soltou = true 
    : _pressionou = true;
    

    
    // if(_estadoAtualBotao != _estadoAnteriorBotao)
    // {
    //     _estadoAnteriorBotao = _estadoAtualBotao;
    //     _ultimaMudanca_ms = millis();
    // }
    
    // else if(tempoDecorrido() > _tempoDebounce_ms)
    // {
    //     const bool acaoExecutada = _estadoUltimaAcao == _estadoAtualBotao;
    //     if (!acaoExecutada)
    //     {
    //         _estadoUltimaAcao = _estadoAtualBotao;


    //         _estadoAtualBotao 
    //         ? _soltou = true 
    //         : _pressionou = true;
    //     }
    // }
}

bool Botao::pressionou()
{
    return _pressionou;
} 

bool Botao::soltou()
{
    return _soltou;
}

uint32_t Botao::tempoDecorrido()
{
    return millis() - _ultimaMudanca_ms;
}

void Botao::setTempoDebounce(uint32_t tempo_ms)
{
    _tempoDebounce_ms = tempo_ms;
}