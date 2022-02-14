
#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
    const int N = 100000;
    int Array[N];
    int max = INT_MIN;
    int min = INT_MAX;
    double start;
    double end;
    srand(time(NULL)); 
    for (int i = 0; i < N; i++) {
        Array[i] = rand() % 90 + 10;
    }

    start = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        if (max < Array[i]) {
            max = Array[i];
        }
        if (min > Array[i]) {
            min = Array[i];
        }
    }


    end = omp_get_wtime();

    cout << endl << "max=" << max;
    cout << endl << "mix=" << min;
    cout << endl << "runtime = " << end - start << endl;
}
