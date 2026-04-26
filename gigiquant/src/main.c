#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "lista.h"
#include "task1math.h"

#include "arbitraj.h"
#include "coada.h"
#include "stiva.h" 

//Functie selectie data input
int getDataFile(const char *path)
{
    const char *l=strstr(path, "data");
    if (l==NULL)
    {
        return -1;
    }

    l+=4;

    int nr=0;
    while(*l>='0' && *l<='9')
    {
        nr=nr*10+(*l-'0');
        l++;
    }
    return nr;
}



int main(int argc, char *argv[])
{
    if(argc<3) // Checker input error if triggered
    {
        printf("Folosesc: %s input output\n", argv[0]);
        return 1;
    }
    

    // Input & Ouput generalizat
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Eroare citire fisier input!\n");
        return 1;
    }

    FILE *output=fopen(argv[2], "w");
    if(output==NULL)
    {
        printf("Eroare citire fisiere output!\n");
        fclose(input);
        return 1;
    }

    //Branching pe Task
    int dataFileNr=getDataFile(argv[1]);

    //Branch Sharpe Ration
    if(dataFileNr>=1 && dataFileNr<=5)
    {
        int N;
        fscanf(input, "%d", &N);
        Nod *head = NULL;
        Nod *tail= NULL;
        for (int i = 0; i < N; i++)
        {
            double val;
            fscanf(input, "%lf", &val);
            createList(&head, &tail, val); // Popularea listei cu N valori dorite 
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


        fprintf(output, "%.3f\n", miu);
        fprintf(output, "%.3f\n", wro);
        fprintf(output, "%.3f\n", sharpeRatio);
        freeList(head); // Memory leak CHECKED.
    }   
    //Branch Arbitraj
    else if(dataFileNr>=6 && dataFileNr<=10)
    {
        char line[100];
        char name_p1[50], name_p2[50], name_p3[50];
        double *b_val1=NULL; 
        double *b_val2=NULL;
        double *b_val3=NULL;
        int n1=0, n2=0, n3=0;

       int market = 0;

    while (fgets(line, sizeof(line), input))
        {
            double val;

            if (sscanf(line, "%lf", &val) == 1)
                {
                    if (market == 1)
                    {
                        b_val1 = realloc(b_val1, (n1 + 1) * sizeof(double));
                        b_val1[n1++] = val;
                    }
                    else if (market == 2)
                    {
                        b_val2 = realloc(b_val2, (n2 + 1) * sizeof(double));
                        b_val2[n2++] = val;
                    }
                    else if (market == 3)
                    {
                        b_val3 = realloc(b_val3, (n3 + 1) * sizeof(double));
                        b_val3[n3++] = val;
                    }
                }
            else
                {
                    line[strcspn(line, "\n")] = '\0';

                    market++;

                    if (market == 1)
                        strcpy(name_p1, line);
                    else if (market == 2)
                        strcpy(name_p2, line);
                    else if (market == 3)
                        strcpy(name_p3, line);
                }
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
        //Eliberare memorie CHECKED
        free(b_val1);
        free(b_val2);
        free(b_val3);   
        //Determinare Arbitraj
        Queue q;
        initQueue(&q);
        
        detArbitrage(&P1, &P2, &P3, &q, name_p1, name_p2, name_p3);

        // Output
        printQueue(&q, output);
        
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
    fclose(output);
    return 0;
}
