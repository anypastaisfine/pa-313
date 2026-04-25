#include <stdlib.h>
#include "stiva.h"

void push(StNod **top, double val)
{
    StNod *nou = malloc(sizeof(StNod));
    nou->val = val;
    nou->next = *top;
    *top = nou;
}

double pop(StNod **top)
{
    if (*top == NULL) 
    {
    return 0;
    }

    StNod *temp = *top;

    double val = temp->val;
    *top = temp->next;

    free(temp);

    return val;
}

int isEmptyStiva(StNod *top)
{
    return top == NULL;
}