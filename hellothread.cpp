#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

struct t_data
{
   int licznik;
   double start;
   double rozmiar;
   double czesc;
};

double f(double x)
{
   const double PI = 3.14159265358979323846;
   const double E = 2.718281828459045235360;
   double func = pow(x, E * PI);
   return func;
}

double prostokatuj(double start, int i, double rozmiar)
{
   double dx = start + i * rozmiar;
   double fx = f(dx + (rozmiar / 2));
   return fx * rozmiar;
}

void *worker(void *arg)
{
   struct t_data *args = (struct t_data *)arg;
   args->czesc = prostokatuj(args->start, args->licznik, args->rozmiar);
   printf("id=%lu result=%f \n", pthread_self(), args->czesc);
}

int main(int argc, char *argv[])
{
   if (argc != 4)
   {
      printf("\nWrong number of arguments. Should be: \n\n./hellothread start rozmiar N \n");
      return 0;
   }

   int N = atoi(argv[3]);
   pthread_t tid[N];
   struct t_data args[N];

   for (int i = 0; i < N; i++)
   {
      args[i].start = atof(argv[1]);
      args[i].rozmiar = atof(argv[2]);
      args[i].licznik = i;
      pthread_create(&tid[i], NULL, &worker, &args[i]);
   }

   double wynik;
   for (int i = 0; i < N; i++)
   {
      pthread_join(tid[i], NULL);
      wynik += args[i].czesc;
   }
   printf("id=%lu result=%f \n", pthread_self(), wynik);
   pthread_exit(NULL);
}