#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void createList(Nod **head, Nod **tail, double val)
{
    Nod *newNode = (Nod *)malloc(sizeof(Nod));
    if (!newNode)
    {
        printf("Eroare alocare memorie!\n");
        exit(1);
    }

    newNode->valoare = val;
    newNode->randament = 0.0;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        *tail = newNode;
    }
    else
    {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

void freeList(Nod *head)
{
    Nod *current;
    while (head != NULL)
    {
        current = head;
        head = head->next;
        free(current);
    }
}