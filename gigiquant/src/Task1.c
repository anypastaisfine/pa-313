#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Noduri lista simplu-inlantuita
typedef struct Node
{
    double valoare;
    double randament;
    struct Node *next;
} Nod;
void createList(Nod **head, double val);
void freeList(Nod *head);
void addRandament(Nod *head);
double aflaMiu(Nod *head, int N);
double aflaVolatilitate(Nod *head, double miu, int N);
double aflaSharpe(double miu, double wro, double Rf);
double trunchiere(double x);


int main(int argc, char *argv[])
{
    // Functia citeste valorile si numarul de observatii dintr-un fisier
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Eroare citire fisier!\n");
        return 1;
    }
    // Numarul de observatii date
    int N;
    fscanf(input, "%d", &N);
    Nod *head = NULL;
    for (int i = 0; i < N; i++)
    {
        double val;
        fscanf(input, "%lf", &val);
        createList(&head, val); // Popularea listei cu N valori dorite 
    }
    fclose(input);

addRandament(head);

double miu = aflaMiu(head, N);
double wro = aflaVolatilitate(head, miu, N);

int Rf = 0;
double sharpeRatio = aflaSharpe(miu, wro, Rf);

//Inceput Trunchiere Date Output
miu=trunchiere(miu);

wro=trunchiere(wro);

sharpeRatio=trunchiere(sharpeRatio);

//Scriere SharpeRatio intr-un fisier output
FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Eroare creare fisier de output!\n");
        return 1;
    }
fprintf(output, "%.3f\n", miu);
fprintf(output, "%.3f\n", wro);
fprintf(output, "%.3f\n", sharpeRatio);
fclose(output);
freeList(head); // Memory leak CHECKED.
return 0;
}

// Functirea creare lista
void createList(Nod **head, double val)
{
    Nod *newNode = (Nod *)malloc(sizeof(Nod));
    if (!newNode)
    {

        printf("Eroarea alocare memorie(1)!\n"); // Err(1) = Nu s-a creat capul listei.
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
        {
            current = current->next;
        }
        current->next = newNode;
    }
}
// Functie eliberare lista din memorie
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
// Functie Calcul Randamente (Task1)
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
