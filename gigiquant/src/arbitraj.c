#include <stdlib.h>
#include <math.h>
#include "arbitraj.h"

void detArbitrage(StNod **P1, StNod **P2, StNod **P3, Queue *out,
                  char *name_p1, char *name_p2, char *name_p3)
{
    int zi = 1;

    while (!isEmptyStiva(*P1) && !isEmptyStiva(*P2) && !isEmptyStiva(*P3))
    {
        double a = pop(P1);
        double b = pop(P2);
        double c = pop(P3);

        if (a == b && b == c)
        {
            // Nu exista arbitraj. Codul nu face nimic.
        }
        else if (a == b && a != c)
        {
            enqueue(out, zi, fabs(c - a), "Paris");
        }
        else if (a == c && a != b)
        {
            enqueue(out, zi, fabs(b - a), "Berlin");
        }
        else if (b == c && b != a)
        {
            enqueue(out, zi, fabs(a - b), "Londra");
        }
        zi++;
    }
}