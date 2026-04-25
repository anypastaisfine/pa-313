#pragma once
#include <stdlib.h>

typedef struct StNode {
    double val;
    struct StNode *next;
} StNod;

void push(StNod **top, double val);
double pop(StNod **top);
int isEmptyStiva(StNod *top);