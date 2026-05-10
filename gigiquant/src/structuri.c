#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "structuri.h"

//Lista
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
//END Lista

//Coada

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

    while (curr!=NULL)
    {
        fprintf(output, "ziua %d - %.2f - %s\n", curr->zi, curr->diff, curr->piata);
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
// END Coada

//Stiva

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
//END Stiva

//Task 3 (Arbore)
TreeNode *creareRadacina() // FUNCTIE INITIALIZARE ARBORE(OLD) -- (NEW) FUNCTIE CONSTRUIRE ARBORE -- STERGE DUPA MODIF
{
    TreeNode *node = malloc(sizeof(TreeNode));
    node->stocks = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void addStock(TreeNode *node, const char *acronim, int index)
{
    StockLS *nou = malloc(sizeof(StockLS));
    strcpy(nou->acronim, acronim);
    nou->index = index;
    nou->next = node->stocks;
    node->stocks = nou;
}

void inserareInTree(TreeNode *root, const char *acronim, int index,
                        double prices[MAX_ZILE], int zi)
{
    TreeNode *curr = root;

    addStock(curr, acronim, index);

    for (int i = 1; i < zi; i++)
    {
        if (prices[i] < prices[i - 1])
        {
            if (curr->left == NULL)
                curr->left = creareRadacina(); // (NU UITA) REDENUMESTE FUNCTIA - NU MAI E DOAR DE RADACINA

            curr = curr->left;
        }
        else
        {
            if (curr->right == NULL)
                curr->right = creareRadacina(); // LA FEL SI AICI

            curr = curr->right;
        }

        addStock(curr, acronim, index);
    }
}
void getPath(double prices[MAX_ZILE], int zi, char path[MAX_ZILE])
{
    for (int i = 1; i < zi; i++)
    {
        if (prices[i] < prices[i - 1])
            path[i - 1] = 'L';
        else
            path[i - 1] = 'R';
    }

    path[zi - 1] = '\0';
}
void getOglindit(char path[MAX_ZILE], char mirror[MAX_ZILE])
{
    int len = strlen(path); // Variabila lungime string

    for (int i = 0; i < len; i++) 
    {
        if (path[i] == 'L')
            mirror[i] = 'R';
        else
            mirror[i] = 'L';
    }

    mirror[len] = '\0';
}
void freeMemoryStock(StockLS *list)
{
    while (list != NULL)
    {
        StockLS *tmp = list;
        list = list->next;
        free(tmp);
    }
}
void freeMemoryTree(TreeNode *root)
{
    if (root == NULL)
        return;

    freeMemoryTree(root->left);
    freeMemoryTree(root->right);
    freeMemoryStock(root->stocks);
    free(root);
}
