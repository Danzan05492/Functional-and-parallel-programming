#include <iostream>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <omp.h>
using namespace std;

int main()
{
    setlocale(.1251, "RUS");

    // Первая матрица
    int n;
    int m;
    cin >> n;
    cin >> m;
    srand(time(NULL));
    int** a = new int* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[m];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            a[i][j] = rand() % 10;
        }
    }
    // Вторая матрица
    int z;
    int w;
    cin >> z;
    cin >> w;
    srand(time(NULL));
    int** b = new int* [z];
    for (int i = 0; i < z; i++)
    {
        b[i] = new int[w];
    }
    for (int i = 0; i < z; i++)
    {
        for (int j = 0; j < w; j++)
        {
            b[i][j] = rand() % 10;
        }
    }
    ////////////////////////////////////////////////////
    double startTime = omp_get_wtime();
    if (m == z)
    {
        int** result = new int* [n];
        double startTime = omp_get_wtime();
        for (int i = 0; i < n; i++)
        {
            result[i] = new int[z];
        }
#pragma omp parallel for
        for (int i = 0; i < n; i++)
            for (int j = 0; j < w; j++)
            {
                int c = 0;

                for (int k = 0; k < z; k++)
                {
                    c += a[i][k] * b[k][j];
                }
                result[i][j] = c;
            }
        double stopTime = omp_get_wtime();
        double elapsed = stopTime - startTime;
        //cout << "Время выполнения: " << elapsed << endl;
        printf("%.7f\n", elapsed);
        ///////////////////////////////////////////////////////////////
        double startTimeb = omp_get_wtime();
        if (m == z)
        {
            int** resultb = new int* [n];
            for (int i = 0; i < n; i++)
            {
                resultb[i] = new int[z];
            }
            for (int i = 0; i < n; i++)
                for (int j = 0; j < w; j++)
                {
                    int c = 0;
                    for (int k = 0; k < z; k++)
                    {
                        c += a[i][k] * b[k][j];
                    }
                    resultb[i][j] = c;
                }
            double stopTimeb = omp_get_wtime();
            double elapsedb = stopTimeb - startTimeb;
            //cout << "Время выполнения: " << elapsed << endl;
            printf("%.7f\n", elapsedb);
            ////////////////////////////////////////////////////////////////////////

            if (result)
            {
                /*
                cout << "Результат умножения матрицы A на матрицу B:" << endl;
                cout << "-------------------------------------------" << endl;
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < w; j++)
                    {
                        cout << result[i][j] << " ";
                    }
                    cout << endl;
                }
                */
                for (int i = 0; i < n; i++)
                {
                    delete[] result[i];
                }
                delete[] result;
            }
            else
            {
                cout << "Умножение таких матриц невозможно!!!" << endl;
            }
            cout << endl;
            if (resultb)
            {
                /*
                cout << "Результат умножения матрицы A на матрицу B:" << endl;
                cout << "-------------------------------------------" << endl;
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < w; j++)
                    {
                        cout << result[i][j] << " ";
                    }
                    cout << endl;
                }
                */
                for (int i = 0; i < n; i++)
                {
                    delete[] resultb[i];
                }
                delete[] resultb;
            }
            else
            {
                cout << "Умножение таких матриц невозможно!!!" << endl;
            }
            system("pause");
            return 0;
        }
    }
}
