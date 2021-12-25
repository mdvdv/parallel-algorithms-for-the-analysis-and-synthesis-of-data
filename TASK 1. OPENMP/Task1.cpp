#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
    int length = atoi(argv[1]);
    double* array = new double[length];

    for (int i = 0; i < length; i++)
    {
        array[i] = (double(rand()) / RAND_MAX);
    }

    for (int number = 1; number <= 10; number++)
    {
        double max_value = array[0];
        double start_time = omp_get_wtime();

	#pragma omp parallel for num_threads(number) reduction(max:max_value)
        for (int index = 0; index < length; index++)
        {
            max_value = max(max_value, array[index]);
        }
	
	double total_time = (double)(omp_get_wtime() - start_time);
        printf("Thread Number: %d Execution Time: %.10f\n", number, total_time);
    }
    return 0;
}