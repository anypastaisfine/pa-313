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

//Inceput calcul Randament la moment t()
Nod* t1=head; // Nodul pentru Pt-1 (din formula)
Nod* t2=head->next; // Nodul pentru Pt (din formula)
int i;
for(i=1; i<N; i++)
{
t2->randament=(t2->valoare-t1->valoare)/t1->valoare; // Calcul randament
t1=t2;
t2=t2->next;
}
// Inceput calcul Randament mediu
double sumRnd=0;
t1=head->next;
while(t1!=NULL)
{
    sumRnd=sumRnd+t1->randament;
    t1=t1->next;
}

double miu=sumRnd/(N-1); // Calcul miu


//Inceput calcul volatilitate (deviatie medie)
double sumVol=0;
t1=head->next;
while(t1!=NULL)
{
    sumVol=sumVol+pow(t1->randament-miu, 2);
    t1=t1->next;
}
double root=sumVol/(N-1);
double wro=sqrt(root);


int Rf=0;
double sharpeRatio=(miu-Rf)/wro;

sharpeRatio=sharpeRatio*1000;
sharpeRatio=trunc(sharpeRatio);
sharpeRatio=sharpeRatio/1000;
//Scriere SharpeRatio intr-un fisier output
FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Eroare creare fisier de output!\n");
        return 1;
    }
wro=wro*1000;
wro=trunc(wro);
wro=wro/1000;

miu=miu*1000;
miu=trunc(miu);
miu=miu/1000;

fprintf(output, "%.3f\n", miu);
fprintf(output, "%.3f\n", wro);
fprintf(output, "%.3f\n", sharpeRatio);
fclose(output);
freeList(head); // Memory leak CHECKED.
return 0;
}