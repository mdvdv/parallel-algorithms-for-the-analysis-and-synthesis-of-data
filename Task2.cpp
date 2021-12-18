#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    int** a = new int* [n];
    int** b = new int* [n];
    int** c = new int* [n];

    for (int i = 0; i < n; ++i)
    {
        a[i] = new int[m];
        b[i] = new int[m];
        c[i] = new int[m];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            a[i][j] = (double(rand()) / RAND_MAX);
            b[i][j] = (double(rand()) / RAND_MAX);
        }
    }

    for (int number = 1; number <= 10; number++)
    {
        double start_time = omp_get_wtime();

        for (int i = 0; i < number; i++)
        {
            for (int j = 0; j < m; j++)
            {
                c[i][j] = 0;
            }
        }

        #pragma omp parallel for num_threads(number)
        for (int k = 0; k < m; k++)
        {
            for (int j = 0; j < m; j++)
            {
                for (int i = 0; i < n; i++)
                {
                    c[i][j] = c[i][j] + a[i][k] * b[k][j];
                }
            }
        }

        double total_time = (double)(omp_get_wtime() - start_time);
        printf("Thread Number: %d Execution Time: %.10f\n", number, total_time);
    }
    return 0;
}