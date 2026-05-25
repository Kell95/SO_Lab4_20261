#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>

typedef struct
{
    long long start;
    long long end;
    double partial_sum;
    double h;
} ThreadData;

double GetTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

double f(double x)
{
    return 4.0 / (1.0 + x * x);
}

void *CalcPartialPi(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    double sum = 0.0;
    double x;

    for (long long i = data->start; i < data->end; i++)
    {
        x = data->h * ((double)i + 0.5);
        sum += f(x);
    }

    data->partial_sum = sum;

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: %s <n> <num_hilos>\n", argv[0]);
        return 1;
    }

    long long n = atoll(argv[1]);
    int num_threads = atoi(argv[2]);

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    double h = 1.0 / (double)n;

    long long block = n / num_threads;

    double start = GetTime();

    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].start = i * block;

        if (i == num_threads - 1)
            thread_data[i].end = n;
        else
            thread_data[i].end = (i + 1) * block;

        thread_data[i].h = h;
        thread_data[i].partial_sum = 0.0;

        pthread_create(&threads[i], NULL, CalcPartialPi, &thread_data[i]);
    }

    double total_sum = 0.0;

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].partial_sum;
    }

    double pi = h * total_sum;

    double end = GetTime();

    printf("PI = %.15f\n", pi);
    printf("Tiempo = %f segundos\n", end - start);

    return 0;
}
