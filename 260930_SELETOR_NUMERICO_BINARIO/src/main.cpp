/*
 Projeto: Seletor Numerico Binario
  Descrição: Seleciona um valor, e o valor exibe o valor em binario e o binario nos leds.
  Autor: Gabriel Chinaglia
  Data: 01/10/2026
  Versão 0.1
*/

#include <Arduino.h>  
#include <LiquidCrystal_I2C.h>  
#include <Botao.h>  
  
LiquidCrystal_I2C lcd(0x27, 20, 4);  
Botao btnCima(12);  
Botao btnBaixo(13);  
Botao btnEnter(14);  
  
const int pinLedA = 18;
const int pinLedB = 16;
const int pinLedC = 7;
const int pinLedD = 4;

const int pinLeds[4] = {pinLedA, pinLedB, pinLedC, pinLedD};  
static bool estadosLeds[4] = {0, 0, 0, 0};  
static int contador = 0;  
int numeroSelecionado = 0;
static bool binarios[4] = {0, 0, 0, 0};
   
void telaInicial();  
void atualizarDisplay();  
void iniciarLeds(); 
void atualizarEstadoLeds();
   
void setup()   
{   
    lcd.init();   
    lcd.backlight();   
    Serial.begin(9600);   
   
    btnCima.iniciar();   
    btnBaixo.iniciar();   
    btnEnter.iniciar();   
    
    iniciarLeds();  
    telaInicial();   
    atualizarDisplay();   
}   
   
void loop()   
{   
    btnCima.atualizar();   
    btnBaixo.atualizar();   
    btnEnter.atualizar();   
   
    if (btnCima.pressionou())   
    {   
        if (contador < 15)   
        {   
            contador++;   
            atualizarDisplay();   
        }   
    }   
   
    if (btnBaixo.pressionou())   
    {   
        if (contador > 0)   
        {   
            lcd.setCursor(9, 1);
            lcd.print(" ");
            contador--;   
            atualizarDisplay();   
        }   
    }     
    if (btnEnter.pressionou())
    {
      numeroSelecionado = contador;
      for(int i = 0; i < 4; i++)
      {
        binarios[i] = contador % 2;
        contador = contador / 2;
      }
      contador = numeroSelecionado;
      atualizarEstadoLeds();
    }
    atualizarDisplay();
}
    
void telaInicial()    
{    
    lcd.setCursor(0, 0);    
    lcd.print("SELECIONE O VALOR:");    
    lcd.setCursor(0, 1);    
    lcd.print("VALOR: ");    
    lcd.setCursor(0, 2);
    lcd.print("BINARIO: ");
    lcd.setCursor(0, 3);     
    lcd.print("ENTER = CONFIRMAR");      
}      
      
void atualizarDisplay()      
{      
    lcd.setCursor(8 ,1); 
    lcd.print(contador); 
    lcd.setCursor(9, 2);
    for(int i = 3; i >= 0; i--) 
    {
      lcd.print(binarios[i]);
    }
    
}    
void iniciarLeds()    
{    
  for (int i = 0; i < 4; i++)    
    pinMode(pinLeds[i], OUTPUT);    
}
void atualizarEstadoLeds()
{
      for(int i = 3; i >= 0; i--)
      {
        estadosLeds[i] = binarios[i];
        digitalWrite(pinLeds[i], estadosLeds[i]);
      }
}