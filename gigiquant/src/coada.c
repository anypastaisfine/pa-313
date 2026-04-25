#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coada.h"

void initQueue(Queue *q)
{
    q->front = q->rear = NULL;
}

void enqueue(Queue *q, int zi, double diff, const char *piata)
{
    QNod *nou = malloc(sizeof(QNod));
    if(!nou)
    {
        printf("Eroare alocare memorie coada!\n");
        exit(1);
    }
    nou->zi = zi;
    nou->diff = diff;
    strcpy(nou->piata, piata);
    nou->next = NULL;

    if (q->rear == NULL)
    {
        q->front = q->rear = nou;
        return;
    }

    q->rear->next = nou;
    q->rear = nou;
}

void printQueue(Queue *q, FILE *output)
{
    QNod *curr = q->front;
    if(q->front == NULL)
    {
        printf("Coada este goala\n");
        return;
    }

    while (curr)
    {
        printf("ziua %d - %f - %s\n", curr->zi, curr->diff, curr->piata);
        curr = curr->next;
    }
}

int isEmpty (Queue *q)
{
    return (q->front == NULL );
}

void deleteQueue(Queue *q)
{
    QNod *aux;
        while (!isEmpty (q))
        {
            aux=q->front ;
            q->front =q->front->next ;
            free (aux);
        }
    q->rear=NULL;
}
