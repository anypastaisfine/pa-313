#pragma once
#include <stdio.h>

typedef struct QNode {
    int zi;
    double diff;
    char piata[20];
    struct QNode *next;
} QNod;

typedef struct {
    QNod *front, *rear;
} Queue;

void initQueue(Queue *q);
void enqueue(Queue *q, int zi, double diff, const char *piata);
void printQueue(Queue *q, FILE *output);
int isEmpty (Queue *q);
void deleteQueue(Queue *q);