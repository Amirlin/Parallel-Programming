#include <stdio.h>
#include <omp.h>

int main()
{
    int tab[8] = {1, 3, 4, 6, 7, 8, 9, 121}, nb_even = 0, nb_odd = 0;

#pragma omp parallel for

    for (int i = 0; i < 8; i++)
    {
        if (tab[i] % 2 == 0)
            nb_even++;
        else
            nb_odd++;
    }
    printf("Nb even=%d\nNb odd=%d\n", nb_even, nb_odd);
}