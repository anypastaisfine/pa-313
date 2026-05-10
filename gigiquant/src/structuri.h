// Librarie care contine structuri si functiile asociate lor

#pragma once
#include <stdio.h>

#define MAX_LINE 2048
#define MAX_ACRO 32
#define MAX_STOCKS 64
#define MAX_ZILE 256

//Lista Simpla
typedef struct Node
{
    double valoare;
    double randament;
    struct Node *next;
} Nod;

void createList(Nod **head, Nod **tail, double val);
void freeList(Nod *head);

//Coada
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

//Stiva
typedef struct StNode {
    double val;
    struct StNode *next;
} StNod;

void push(StNod **top, double val);
double pop(StNod **top);
int isEmptyStiva(StNod *top);

//Arbore
typedef struct StockList {
    char acronim[MAX_ACRO];
    int index;
    struct StockList *next;
} StockLS;

typedef struct TreeNode {
    StockLS *stocks;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *creareRadacina(); //!!NUME VECHI - TREBUIE SCHIMBAT IN CEVA PENTRU CONSTRUITE ARBORE
void addStock(TreeNode *node, const char *acronim, int index);
void inserareInTree(TreeNode *root, const char *acronim, int index,
                        double prices[MAX_ZILE], int z);
void getPath(double prices[MAX_ZILE], int zi, char path[MAX_ZILE]);
void getOglindit(char path[MAX_ZILE], char mirror[MAX_ZILE]);
void freeMemoryStock(StockLS *list);
void freeMemoryTree(TreeNode *root);

