#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

class SLAU{
public:
    int n;
    vector<vector<double > > M;
    vector<double > y, x;
    /// 1) Прямой ход гаусса
    /// 2) Обратный ход гаусса
    /// 3) Находим X

    void solve(){
        /// 1)

        omp_set_num_threads(6);

       #pragma omp parallel for shared(M) schedule(static)
        for(int j=0; j<n; j++){ ///->
            for(int i=j+1; i<n; i++){/// |
                //cout<<"row: "<<i<<endl;
                double Q = M[i][j];
                for(int k=0; k<n; k++){ /// ->
                    //cout<<M[i][k]<<"+"<<M[j][k]<<"*("<<-Q<<")/"<<M[j][j]<<" ";
                    M[i][k] += M[j][k] * (-Q) / M[j][j];
                    //cout<<" = "<<M[i][k]<<endl;
                }
                y[i] += y[j] * (-Q) / M[j][j];
                //cout<<endl;
            }
        }

        /// 2)
        #pragma omp parallel for shared(M) schedule(static)
        for(int j=1; j<n; j++){ ///->
            for(int i=0; i<j; i++){/// |
                //cout<<"row: "<<i<<endl;
                double Q = M[i][j];
                for(int k=0; k<n; k++){ /// ->
                    //cout<<M[i][k]<<"+"<<M[j][k]<<"*("<<-Q<<")/"<<M[j][j]<<" ";
                    M[i][k] += M[j][k] * (-Q) / M[j][j];
                    //cout<<" = "<<M[i][k]<<endl;
                }
                y[i] += y[j] * (-Q) / M[j][j];
                //cout<<endl;
            }
        }

        /// 3)
        #pragma omp parallel for shared(M) schedule(static)
        for(int i=0; i<n; i++){
            x[i] = y[i] / M[i][i];

        }


    }

    void print(){
        for(auto i:M){
            for(auto j:i)
                cout<<j<<' ';
            cout<<endl;
        }
    }

};

int main(){
    SLAU q;
    q.n = 3;
    q.M={{1,2,3},{1,3,2},{3,2,1}};
    q.y={3,4,5};
    q.x={0,0,0};

    double t1 = omp_get_wtime();
    q.solve();
    double t2 = omp_get_wtime();

    cout<<t2-t1<<endl;

    for(auto i:q.x)
        cout<<i<<' ';

}
