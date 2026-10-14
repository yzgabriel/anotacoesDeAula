#include <Arduino.h>

void funcaoBloqueante();
void funcaoNaoBloqueante();
void processarFrase(const char* texto);

void setup() 
{
  Serial.begin(115200);

  //* O método readStringUntil espera no máximo por caracter esse tempo(ms) pelo '\n'
  Serial.setTimeout(2000);
  Serial.println();
}

void loop() 
{
  funcaoNaoBloqueante();

}

void funcaoNaoBloqueante()
{
  const int TAMANHO_MAX = 50; //* tamanho do vetor que inclui '\0'
  static char frase[TAMANHO_MAX];
  static int position = 0;
  
  while(Serial.available() > 0)
  {
    char c = Serial.read();

    if(c == '\r') continue;
    //* o continue pula o restante do while() naquela volta e passa para leitura
    //* do proximo caractere. O '\r' é lido e simplesmente descartado, sem entrar no vetor

    if(c == '\n')
    {
      frase[position] = '\0';
      if(position > 0) processarFrase(frase);
      position = 0;
    }

    else if(position < TAMANHO_MAX - 1)
    {
      frase[position] = c;
      position++;
    }
  }
}


//* VERMELHO, VERDE, AZUL, BRANCO, DESLIGA
//* RGB r g b (ex.: RGB 255 180 5)
//* BRILHO n (0 a 100%)
void processarFrase(char* texto)
{
  Serial.printf("Recebido: [%s]\n\r", texto);

  char* comando = texto;
  char* parametro = NULL; //* '\0'

  char* espaco =  strchr(texto, ' '); //* procura pelo primeiro espaço no texto
  if(espaco != NULL)
  {
    *espaco = '\0'; //* substitiu o espaço por um '\0'
    parametro = espaco + 1;
  }

  //* strcasecmp verifica a posicao lexica das palavras ignorando letras minusculas ou maiusculas
  if(strcasecmp(comando, "VERMELHO") == 0)
  {

  }
  else if(strcasecmp(comando, "VERDE") == 0)
  {
    
  }
  else if(strcasecmp(comando, "AZUL") == 0)
  {

  }
  else if(strcasecmp(comando, "BRANCO") == 0)
  {

  }
  else if(strcasecmp(comando, "DESLIGA") == 0)
  {

  }
  else if(strcasecmp(comando, "RGB") == 0)
  {

  }
  else if(strcasecmp(comando, "BRILHO") == 0)
  {

  }
  else
  {

  }
}

void funcaoBloqueante()
{
  //* available() diz quantos bytes já chegaram e estão esperando leitura
  if(Serial.available() > 0)
  {
    String texto = Serial.readStringUntil('\n'); //! FUNÇÃO BLOQUEANTE

    //* trim() remove do fim do texto os espaços, '\r', '\t', '\n', que alguns terminais enviam
    texto.trim();
    if(texto.length() == 0) return;

    Serial.printf("Seu nome eh %s\n\r", texto.c_str());

    String textoMaiusculas = texto;
    textoMaiusculas.toUpperCase();

    if(textoMaiusculas == "GABRIEL")
    Serial.println("Esse é seu nome correto.");
  }
}