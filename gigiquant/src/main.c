#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "lista.h"
#include "task1math.h"

#include "arbitraj.h"
#include "coada.h"
#include "stiva.h" 

int main(int argc, char *argv[])
{
    // Functia citeste valorile si numarul de observatii dintr-un fisier
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Eroare citire fisier!\n");
        return 1;
    }

    //Cod Branching Task1 || Task2
    char check[50];
    fscanf(input,"%s",check);
    rewind(input);

    //Ramura Sharpe Ratio
    if(isdigit(check[0]))
    {
        int N;
        fscanf(input, "%d", &N);
        Nod *head = NULL;
        for (int i = 0; i < N; i++)
        {
            double val;
            fscanf(input, "%lf", &val);
            createList(&head, val); // Popularea listei cu N valori dorite 
        }

        addRandament(head);

        double miu = aflaMiu(head, N);
        double wro = aflaVolatilitate(head, miu, N);

        double Rf = 0;
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
        freeList(head); // Memory leak CHECKED.
        fclose(output);
    }   
    //Ramura Arbitraj
    else
    {
        char name_p1[50], name_p2[50], name_p3[50];
        double tmp;
        double b_val1[1000], b_val2[1000], b_val3[1000];
        int n1=0, n2=0, n3=0;

        //P1
        fscanf(input, "%s",name_p1);
        while(fscanf(input, "%lf", &tmp)==1)
        {
            b_val1[n1++]=tmp;
            char k=fgetc(input);
            if(k==EOF)
            {
                break;
            }
            if(k<'0' || k>'9')
            {
                ungetc(k, input);
                break;
            }
            ungetc(k, input);
        }
        // P2
        fscanf(input, "%s",name_p2);
        while(fscanf(input, "%lf", &tmp)==1)
        {
            b_val2[n2++]=tmp;
            char k=fgetc(input);
            if(k==EOF)
            {
                break;
            }
            if(k<'0' || k>'9')
            {
                ungetc(k, input);
                break;
            }
            ungetc(k, input);
        }

        // P3
        fscanf(input, "%s",name_p3);
        while(fscanf(input, "%lf", &tmp)==1)
        {
            b_val3[n3++]=tmp;
            char k=fgetc(input);
            if(k==EOF)
            {
                break;
            }
            if(k<'0' || k>'9')
            {
                ungetc(k, input);
                break;
            }
            ungetc(k, input);
        }

        // Populare stive
        StNod *P1= NULL;
        StNod *P2= NULL;
        StNod *P3= NULL;

        for(int i = n1-1; i>=0; i--)
        {
            push(&P1, b_val1[i]);
        }

        for(int i = n2-1; i>=0; i--)
        {
            push(&P2, b_val2[i]);
        }

        for(int i = n3-1; i>=0; i--)
        {
            push(&P3, b_val3[i]);
        }

        //Determinare Arbitraj
        Queue q;
        initQueue(&q);
        
        detArbitrage(P1, P2, P3, &q);

        // Output
        FILE *output = fopen(argv[2], "w");
        if (output == NULL)
            {
                printf("Eroare creare fisier de output!\n");
                return 1;
            }
        printQueue(&q, output);
        
        fclose(output);
        
        // Clean-up memorie
        deleteQueue(&q);
            
        while (!isEmptyStiva(P1))
            pop(&P1);
        while (!isEmptyStiva(P2))
            pop(&P2);
        while (!isEmptyStiva(P3))
            pop(&P3);
    }
    fclose(input);
    return 0;
}
