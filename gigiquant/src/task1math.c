#include "lista.h"
#include <math.h>
#include <stdlib.h>
// Functii Calcul Task1
void addRandament(Nod *head)
{
    Nod *t1 = head;
    Nod *t2 = head->next;

    while (t2 != NULL)
    {
        t2->randament = (t2->valoare - t1->valoare) / t1->valoare;
        t1 = t2;
        t2 = t2->next;
    }
}
double aflaMiu(Nod *head, int N)
{
    double sumRnd = 0;
    Nod *current = head->next;

    while (current != NULL)
    {
        sumRnd += current->randament;
        current = current->next;
    }

    return (sumRnd / (N - 1));
}

double aflaVolatilitate(Nod *head, double miu, int N)
{
    double sumVol = 0;
    Nod *current = head->next;

    while (current != NULL)
    {
        sumVol += pow(current->randament - miu, 2);
        current = current->next;
    }

    return sqrt(sumVol / (N - 1));
}

double aflaSharpe(double miu, double wro, double Rf)
{
    return (miu - Rf) / wro;
}

double trunchiere(double x)
{

    return (long long)(x*1000)/1000.0;
}