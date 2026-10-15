#include <Arduino.h>

void funcaoBloqueante();
void funcaoNaoBloqueante();
void processarFrase(char* texto);
void aplicarCor();
int lerProximoNumero(char* &cursor);

int vermelho = 0;
int verde = 0;
int azul = 0;
int brilho = 0;

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
    vermelho = 255;
    azul = 0;
    verde = 0;
    brilho = 100;
  }
  else if(strcasecmp(comando, "VERDE") == 0)
  {
    vermelho = 0;
    azul = 0;
    verde = 255;
    brilho = 100;
  }
  else if(strcasecmp(comando, "AZUL") == 0)
  {
    vermelho = 0;
    azul = 255;
    verde = 0;
    brilho = 100;
  }
  else if(strcasecmp(comando, "BRANCO") == 0)
  {
    vermelho = 255;
    azul = 255;
    verde = 255;
    brilho = 100;
  }
  else if(strcasecmp(comando, "DESLIGA") == 0)
  {
    vermelho = 0;
    azul = 0;
    verde = 0;
    brilho = 0;
  }
  else if(strcasecmp(comando, "RGB") == 0)
  {
    if(parametro == NULL)
    {
      Serial.println("Use o comando: RGB r g b (0 a 255)");
      return;
    }

    char* cursor = parametro;

    int r = lerProximoNumero(cursor);
    int g = lerProximoNumero(cursor);
    int b = lerProximoNumero(cursor);

    vermelho = constrain(r, 0, 255);
    verde = constrain(g, 0, 255);
    azul = constrain(b, 0, 255);

  }
  else if(strcasecmp(comando, "BRILHO") == 0)
  {
    if(parametro = NULL)
    {
      Serial.println("Use o comando: BRILHO n (0 a 100)");
      return;
    }

    brilho = constrain(atoi(parametro), 0, 100);
  }
  else
  {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Comando: [%s] não existe", comando);
    Serial.println(buffer);
    return;
  }
  aplicarCor();
}

void aplicarCor()
{
  int r = vermelho * brilho / 100;
  int g = verde * brilho / 100;
  int b = azul * brilho / 100;

  rgbLedWrite(PIN_RGB_LED, r, g, b);

  char bufferMensagem[61];
  snprintf(bufferMensagem, sizeof(bufferMensagem),
            "Cor: R=%3d G=%3d B=%3d | Brilho: %3d %% | HEX: #%02X%02X%02X",
          vermelho, verde, azul, brilho, r, g, b);
  Serial.println(bufferMensagem);
}

//* cursor é uma referência (&) para um ponteiro (char*)
//* a função recebe a própria variável de quem chamou e não uma cópia
//* 
//* PARAMETRO     | ALTERA O TEXTO APONTADO | ALTERA PARA ONDE O PONTEIRO DE FORA APONTA
//* char* p       | sim(*p = '\0')          | não, porque ele é uma cópia do ponteiro
//* const char* p | não                     | não
//* char* &p      | sim                     | sim, é a própria variável passada como parâmetro

int lerProximoNumero(char* &cursor)
{
  if(cursor == NULL)
    return 0;

  int valor = atoi(cursor);

  char* espaco = strchr(cursor, ' ');
  cursor = (espaco != NULL) ? espaco + 1 : NULL;
  
  return valor;
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