
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void trig_matr(float **arr, float **masr, int n)
{
    int k = 0, ind;
    while (k < n)
    {
        float t = arr[k][k];
        if(t == 0)
        {
            for(int i = 0; i < n; i++)
                if(arr[i][k] != 0)
                {
                    ind = i;
                    break;
                }
            for(int i = 0; i < n; i++)
            {
                float t = arr[k][i], t1 = masr[k][i];
                arr[k][i] = arr[ind][i], masr[k][i] = masr[ind][i];
                arr[ind][i] = t, masr[ind][i] = t1;
            }
            t = arr[k][k];
        }
        for (int i = 0; i < n; i++)
        {
            arr[k][i] /= t;
            masr[k][i] /= t;
        }
        for (int i = k + 1; i < n; i++)
        {
            float t = arr[i][k];
            for (int j = 0; j < n; j++)
            {
                arr[i][j] -= arr[k][j] * t;
                masr[i][j] -= masr[k][j] * t;
            }
        }
        k++;
    }
    for (k = n - 1; k > 0; k--)
    {
        for(int j = k - 1; j >= 0; j--)
        {
            float t = arr[j][k];
            arr[j][k] -= arr[k][k] * t;
            for(int i = n-1; i >= 0; i--)
            {
                masr[j][i] -= masr[k][i] * t;
            }
        }
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int n;
    float **arr, **masr, **arr_copy;

    printf("Введите кол-во строк и столбцов: ");
    scanf("%d", &n);

    arr = (float**) malloc(n*sizeof(float*));
    masr = (float**) malloc(n*sizeof(float*));
    arr_copy= (float**) malloc(n*sizeof(float*));


    for (int i = 0; i < n; ++i){
        arr[i] = (float*) malloc(n*sizeof(float));
        masr[i] = (float*) malloc(n*sizeof(float));
        arr_copy[i] = (float*) malloc(n*sizeof(float));
    }
    printf("Введите элементы матрицы: \n");

    for (int i = 0; i < n; i++)

        for (int j = 0; j < n; j++)

        {
            if(i == j)
                masr[i][j] = 1;
                  else masr[i][j] = 0;

            scanf("%f", &arr[i][j]);
            arr_copy[i][j] = arr[i][j];
        }

    trig_matr(arr, masr, n);
    printf("\nОбратная матрица: \n");

     for(int i = 0; i < n; i++)
      {
        for(int j = 0; j < n; j++)
            printf("%f ", masr[i][j]);
        printf("\n");
      }

    float **c = (float**) malloc(n*sizeof(float*));

    for (int i = 0; i < n; i++)
    {
        c[i] = (float*) malloc(n*sizeof(float));

        for (int j = 0; j < n; j++)

        {
            c[i][j] = 0;

            for (int k = 0; k < n; k++)
                c[i][j] += arr_copy[i][k] * masr[k][j];

            if (fabs(c[i][j]) < 0.000001)
                c[i][j] = 0;
        }

    }
    printf("\nПеремножение матриц: \n");
    for(int i = 0; i < n; i++)
    {
        for(int j=0; j<n; j++)
        {
            printf("%f ", c[i][j]);
        }
        printf("\n");
    }



    return 0;
}
