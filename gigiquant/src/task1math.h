#pragma once

#include "lista.h"
#include <math.h>

void addRandament(Nod *head);
double aflaMiu(Nod *head, int N);
double aflaVolatilitate(Nod *head, double miu, int N);
double aflaSharpe(double miu, double wro, double Rf);
double trunchiere(double x);