//Librarie care contine operatiile matematice si prelucrarile specifice fiecarui task
#pragma once

#include "structuri.h"
#include <math.h>

//Task 1
void addRandament(Nod *head);
double aflaMiu(Nod *head, int N);
double aflaVolatilitate(Nod *head, double miu, int N);
double aflaSharpe(double miu, double wro, double Rf);
double trunchiere(double x);

//Task 2
void detArbitrage(FILE *input, FILE *output);
//Task 3
void detDiversificare(FILE *input, FILE *output);