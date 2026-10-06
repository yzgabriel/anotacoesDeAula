#include "roboBrain.h"

float calcularDobro(float n1)
{
    float resultado = n1 * 2;
    return resultado;
}

int ehPar(int n1)
{
    bool resultado = n1 % 2 == 0 ? true : false;
    return resultado;
}

float calculadoraMagica(float n1, float n2, int operacao)
{
    switch (operacao)
    {
    case 1:
        return n1 + n2;
    case 2:
        return n1 - n2;
    case 3:
        return n1 * n2;
    default:
        return 0;
    }
}

int calcularFatorial(int n1)
{
    int resultado = 1;
    if (n1 > 0)
    {
        while (n1 > 1)
        {
            resultado = resultado * (n1);
            n1--;
        }
    }
    return resultado;
}