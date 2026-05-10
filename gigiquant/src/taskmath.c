#include "taskmath.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Functii Calcul Task1
void addRandament(Nod *head)
{
    Nod *t1 = head;
    Nod *t2 = head->next;

    while (t2 != NULL)
    {
        t2->randament = (t2->valoare - t1->valoare) / t1->valoare;
        t1 = t2;
        t2 = t2->next;
    }
}
double aflaMiu(Nod *head, int N)
{
    double sumRnd = 0;
    Nod *current = head->next;

    while (current != NULL)
    {
        sumRnd += current->randament;
        current = current->next;
    }

    return (sumRnd / (N - 1));
}

double aflaVolatilitate(Nod *head, double miu, int N)
{
    double sumVol = 0;
    Nod *current = head->next;

    while (current != NULL)
    {
        sumVol += pow(current->randament - miu, 2);
        current = current->next;
    }

    return sqrt(sumVol / (N - 1));
}

double aflaSharpe(double miu, double wro, double Rf)
{
    return (miu - Rf) / wro;
}

double trunchiere(double x)
{

    return (long long)(x*1000)/1000.0;
}

//END Task 1

//Functii Calcul Task 2
void detArbitrage(FILE *input, FILE *output)
{
    char line[MAX_LINE]; 
    char name[3][64]; // matrice de 3 piete, fiecare de maximum 64 de caractere

    double **val = calloc(3, sizeof(double *));
    int n[3] = {0, 0, 0}; //

    int market = -1;

    while (fgets(line, sizeof(line), input))
    {
        line[strcspn(line, "\n")] = '\0'; // REZOLVAT TO TASK!

        if (strlen(line) == 0)
            continue;

        double x;

        if (sscanf(line, "%lf", &x) == 1)
        {
            if (market >= 0 && market < 3)
            {
                val[market] = realloc(val[market], (n[market] + 1) * sizeof(double));
                val[market][n[market]++] = x;
            }
        }
        else
        {
            market++;
            if (market < 3)
                strcpy(name[market], line);
        }
    }

    int minN = n[0];
    if (n[1] < minN) minN = n[1];
    if (n[2] < minN) minN = n[2];

    Queue q;
    initQueue(&q);

    for (int zi = 1; zi <= minN; zi++)
    {
        double a = val[0][n[0] - zi];
        double b = val[1][n[1] - zi];
        double c = val[2][n[2] - zi];

        if (a == b && b == c)
        {
            continue;
        }
        else if (a == b && a != c)
        {
            enqueue(&q, zi, fabs(c - a), name[2]);
        }
        else if (a == c && a != b)
        {
            enqueue(&q, zi, fabs(b - a), name[1]);
        }
        else if (b == c && b != a)
        {
            enqueue(&q, zi, fabs(a - b), name[0]);
        }
    }

    printQueue(&q, output);

    deleteQueue(&q);

    for (int i = 0; i < 3; i++)
        free(val[i]);

    free(val);
}
// END Task 2

//Functii Task 3
void detDiversificare(FILE *input, FILE *output)
{
    char line[MAX_LINE];

    char acronims[MAX_STOCKS][MAX_ACRO];
    double prices[MAX_STOCKS][MAX_ZILE];

    int stockCount = 0;
    int zi = 0;

    fgets(line, sizeof(line), input);

    char *token = strtok(line, ",\n");
    while (token != NULL)
    {
        strcpy(acronims[stockCount++], token);
        token = strtok(NULL, ",\n");
    }

    while (fgets(line, sizeof(line), input))
    {
        int col = 0;

        token = strtok(line, ",\n");
        while (token != NULL && col < stockCount)
        {
            prices[col][zi] = atof(token);
            col++;
            token = strtok(NULL, ",\n");
        }

        zi++;
    }

    TreeNode *root = creareRadacina();

    for (int i = 0; i < stockCount; i++)
    {
        double oneStock[MAX_ZILE];

        for (int d = 0; d < zi; d++)
            oneStock[d] = prices[i][d];

        inserareInTree(root, acronims[i], i, oneStock, zi);
    }

    char path[MAX_STOCKS][MAX_ZILE];
    char mirror[MAX_STOCKS][MAX_ZILE];

    for (int i = 0; i < stockCount; i++)
    {
        double oneStock[MAX_ZILE];

        for (int d = 0; d < zi; d++)
            oneStock[d] = prices[i][d];

        getPath(oneStock, zi, path[i]);
        getOglindit(path[i], mirror[i]);
    }
    // Newline linii-1 - (REZOLVAT) PROBLEMA Output
   int first = 1;

for (int i = 0; i < stockCount; i++)
{
    for (int j = i + 1; j < stockCount; j++)
    {
        if (strcmp(path[j], mirror[i]) == 0)
        {
            if (!first)
                fprintf(output, "\n");

            fprintf(output, "%s-%s", acronims[i], acronims[j]);

            first = 0;
        }
    }
}

    freeMemoryTree(root);
}
//END Task 3