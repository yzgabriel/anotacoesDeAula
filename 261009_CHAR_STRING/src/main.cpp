#include <Arduino.h>
#include <string.h> //* strlen, strcpy, strcat, strcmp, strchr
#include <stdlib.h> //* atoi

void textoTipoC();
void textoTipoString();

void setup() 
{
  Serial.begin(9600);
  Serial.println();
  textoTipoC();
  textoTipoString();
}

void loop() 
{

}

void textoTipoC()
{
  //* Texto literal
  //* Use const char* quando o texto não será alterado
  const char* cidade = "Sao Paulo";
  const char outraCidade[] = "Sao Caetano";
  Serial.println(cidade);
  Serial.println(outraCidade);

  //* Descobrindo o tamanho do texto
  //* strle conta quantos caracteres antes do '\0'
  int tamanhoTextoCidade = strlen(cidade);
  int tamanhoTextoOutraCidade = strlen(outraCidade);

  Serial.print("Comprimento do texto em caracteres: ");
  Serial.println(tamanhoTextoOutraCidade);

  Serial.print("Tamanho do conteudo do ponteiro: ");
  Serial.println(tamanhoTextoCidade);

  //* Descobrindo tamanho ocupado

  int tamanhoVariavel = sizeof(outraCidade);
  int tamanhoPonteiro = sizeof(cidade);

  //* Quando usando o sizeof em uma string sempre retornará
  //* um byte a mais do que a quantidade de caracteres por
  //* causa do '\0' que finaliza o texto
  Serial.print("Tamanho da Variavel em bytes: ");
  Serial.println(tamanhoVariavel);

  //* Quando usamos o sizeof em ponteiros retorna sempre 4bytes
  //* pois o conteúdo dele é um endereço de memoria como 0xFF00C245
  Serial.print("Tamanho do ponteiro: ");
  Serial.println(tamanhoPonteiro);

  //* o caractere '\0' é colocado automaticamente quando escrevemos
  //* um texto entre aspas duplas " ".
  char vetorTexto[8] = {'G', 'a', 'b', 'r', 'i', 'e', 'l', '\0'};
  Serial.println (vetorTexto);

  //* Comparar texto
  const char* cidade1 = "Porto Alegre";
  const char* cidade2 = "Porto Alegre";

  if(strcmp(cidade1, cidade2) == 0)
    Serial.println("As strings são iguais");
  else 
    Serial.println("As strings são diferentes");

  //* strcmp analiza a ordem léxica das palavras, se a primeira palavra vem antes
  //* que a segunda o valor retornado será menor que zero se a primeira vem após
  //* a segunda o retorno será maior que zero.

  //* ==========================
  //* TEXTO EDITAVEL COM char()
  //* ==========================

  char nomeAluno[8] = "Gabriql";
  Serial.println(nomeAluno);

  nomeAluno[5] = 'e';
  Serial.println(nomeAluno);

  //* Copiando outro texto para dentro do vetor
  //! Cuidado, o vetor precisa ter espaço suficiente

  strcpy(nomeAluno, "Tadeu");
  Serial.print(nomeAluno);

  //* Concatenando texto ao final
  char frase[40] = "Ola ";
  strcat(frase, "Mundo cruel!");
  Serial.println(frase);

  //* Procurando um caractere no texto

  char* posicaoLetra = strchr(frase, 'M');

  if(posicaoLetra != NULL)
  {
    Serial.println("Letra encontrada");
    Serial.println(posicaoLetra);
  }
  else
    Serial.println("Letra não encontrada");

  
  //* Convertendo texto numérico para inteiro
  char idadeTexto[] = "39"; //* [0x33 , 0x57, 0x00]
  int idade = atoi(idadeTexto);

  //* Montando texto
  char buffer[100];
  char* local = "Sala de aula";
  float temperatura = 26.4;
  int umidade = 72;

  snprintf(buffer, size_t(buffer), "%s | Temp: %f C | Umid: %d %% \n\r" , local, temperatura, umidade);
  Serial.print(buffer);


  //* snprintf monta o texto dentro de um vetor do char
  //* isso é muito útil quando depois você quer:
  //* - enviar por MQTT
  //* - salvar em variavel
  //* - Mandar para o diplay
  //* - Imprimir na Serial
  //* 
  //* ESPECIFICADORES
  //* 
  //*     %d ou %i    -int
  //*     %u          -unsigned nt
  //*     %ld         -long
  //*     %lu         -unsigned long
  //*     %f          -float
  //*     %e          -notação científica
  //*     %g          -float, formato mais curto
  //*     %c          -char
  //*     %s          -char*
  //*     %x ou %X    -hexadecimal minúsculo/maiúsculo
  //*     %o          -octal
  //*     %p          -ponteiro
  //*     %%          -o próprio %
  //* 
  //* Flags, largura e precisão
  //* 
  //*     %5d         -imprime com largura miníma de 5, alinhado a direita  [    3] [  100] [10000]
  //*     %-2         -imprime com largura miníma de 2, alinhado a esquerda
  //*     %04d        -completa com zeros ex. 0022
  //*     %+d         -sempre mostra o sinal ex. +5
  //*     %.2f        -2 casas decimais
  //*     %4.2f       -largura de 4 com  2 casas
  //*     %02x        -hexadecimal com 2 digitos
  //*     %#x         -prefixo 0x
  //*     %.3s        -só os primeiros 3 caracteres da string
  //*     %*d         -largura passada como argumento ex. snprintf(buffer, sizeof(buffer), "%*d", 5, 42) [   42]


}

void textoTipoString()
{

}