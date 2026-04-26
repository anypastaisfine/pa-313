#pragma once
typedef struct Node
{
    double valoare;
    double randament;
    struct Node *next;
} Nod;

void createList(Nod **head, Nod **tail, double val);
void freeList(Nod *head);