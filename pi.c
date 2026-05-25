#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

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

double CalcPi(long long n)
{
    double fH = 1.0 / (double)n;
    double fSum = 0.0;
    double fX;

    for (long long i = 0; i < n; i++)
    {
        fX = fH * ((double)i + 0.5);
        fSum += f(fX);
    }

    return fH * fSum;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uso: %s <n>\n", argv[0]);
        return 1;
    }

    long long n = atoll(argv[1]);

    double start = GetTime();

    double pi = CalcPi(n);

    double end = GetTime();

    printf("PI = %.15f\n", pi);
    printf("Tiempo = %f segundos\n", end - start);

    return 0;
}
