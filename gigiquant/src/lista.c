#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void createList(Nod **head, double val)
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
    }
    else
    {
        Nod *current = *head;
        while (current->next != NULL)
            current = current->next;

        current->next = newNode;
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