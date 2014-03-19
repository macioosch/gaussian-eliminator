#include <iostream>
#include <iomanip>
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

int gauss(double **t, int m, int n, double *w)
{
    for (int k=0; k<m; ++k) {
        // increase stability by some row-swapping
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
            double multiplier = t[i][k] / t[k][k];
            for (int j=k; j<n; ++j)
                t[i][j] -= t[k][j] * multiplier;
            t[i][k] = 0;
        }
    }

    for (int i=m-1; i>=0; --i) {
        w[i] = t[i][n-1] / t[i][i];
        for (int j=n-2; j>i; --j)
            w[i] -= w[j] * t[i][j] / t[i][i];
    }

    return 0;
}

int main()
{
    const int m=2, n=3;
    double **t, *w;

    w = new double[m];
    t = new double*[m];
    for (int i=0; i<m; ++i)
        t[i] = new double[n];

    t[0][0]=-1; t[0][1]= 1; t[0][2]=-1;
    t[1][0]=-2; t[1][1]= 1; t[1][2]= 2;

    cout << setprecision(4);

    gauss(t, m, n, w);

    cout << "t:\t";
    for (int i=0; i<m; ++i) {
        for (int j=0; j<n; ++j)
            cout << t[i][j] << "\t";
        cout << endl << "\t";
    }

    cout << endl << "w:\t";
    for (int i=0; i<m; ++i)
        cout << w[i] << "\t";
    cout << endl;

    return 0;
}
