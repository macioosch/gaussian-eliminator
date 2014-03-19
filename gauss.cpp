#include <iostream>
using namespace std;

void swap_arrays(double r1[], double r2[], int n)
{
    double tmp;
    for (int i=0; i<n; ++i) {
        tmp = r1[i];
        r1[i] = r2[i];
        r2[i] = tmp;
    }
}

int gauss(double* t[], int m, int n, double w[])
{
    for (int k=0; k<m; ++k) {
        int i_max = k;
        double max_square = t[i_max][k]*t[i_max][k];
        for (int i=k+1; i<m; ++i) // 1 not 0 on purpose
            if (t[i][k]*t[i][k] > max_square) {
                i_max = i;
                max_square = t[i_max][k]*t[i_max][k];
            }
        if (t[i_max][k] == 0)
            return -1;
        swap_arrays(t[k], t[i_max], n);
        for (int i=k+1; i<m; ++i) {
            for (int j=k; i<n; ++j)
                t[i][j] = t[i][j] - t[k][j] * t[i][k] / t[k][k];
            t[i][k] = 0;
        }
    }
}

int main()
{
    const int m=2, n=3;
    double t[m][n], w[m];

    t[0][0]=1; t[0][1]=1; t[0][2]=1;
    t[1][0]=3; t[1][1]=1; t[1][2]=2;

    gauss(t, m, n, w);

    cout << "w: ";
    for (int i=0; i<m-1; ++i)
        cout << w[i] << ", ";
    cout << w[m-1] << endl;

    return 0;
}
