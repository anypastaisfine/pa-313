#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "structuri.h"
#include "taskmath.h"


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
    if (argc < 3)
        return 1;

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
        return 1;

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        fclose(input);
        return 1;
    }

    int dataSet = getDataFile(argv[1]);

    if (dataSet >= 1 && dataSet <= 5)
    {
        int N;
        fscanf(input, "%d", &N);

        Nod *head = NULL;
        Nod *tail = NULL;

        for (int i = 0; i < N; i++)
        {
            double val;
            fscanf(input, "%lf", &val);
            createList(&head, &tail, val);
        }

        addRandament(head);

        double miu = aflaMiu(head, N);
        double wro = aflaVolatilitate(head, miu, N);
        double sharpeRatio = aflaSharpe(miu, wro, 0);

        miu = trunchiere(miu);
        wro = trunchiere(wro);
        sharpeRatio = trunchiere(sharpeRatio);

        fprintf(output, "%.3f\n", miu);
        fprintf(output, "%.3f\n", wro);
        fprintf(output, "%.3f\n", sharpeRatio);

        freeList(head);
    }
    else if (dataSet >= 6 && dataSet <= 10)
    {
        detArbitrage(input, output);
    }
    else
    {
        detDiversificare(input, output);
    }
    // Spatiu TASK 4
    fclose(input);
    fclose(output);

    return 0;
}