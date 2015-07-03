#include <iostream>
#include <string>

using namespace std;

void rowColZero(int** matrix, int x, int y) {
    bool* col = new bool[x];
    bool* row = new bool[y];

    for (int i =0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (matrix[i][j] == 0) {
//                cout << "TRUE: (" << i << "," << j << ")" << endl;
                col[i] = true;
                row[j] = true;
            }
        }
    }

    for (int k=0; k < x; k++) {
        for (int l=0; l < y; l++) {
            if (col[k] == true || row[l] == true) {
                matrix[k][l] = 0;
            }
        }
    }
}

int main() {
    // 3x4 matrix
    int x = 3;
    int y = 4;
    int dummy_val =  0;
    int** input = new int*[y];

    cout << "Initial Matrix: " << endl;
    for(int i =0; i < x; ++i) {
        input[i] = new int[x];
        for (int j=0; j<y; ++j) {
            input[i][j] = rand()%8;
        }
    }

    for(int m =0; m < y; ++m) {
        cout << "   ";
        for (int n=0; n<x; ++n) {
            cout << input[n][m] << " ";
        }
        cout <<endl;
    }
//hi ii love suzanne
    /* i love her more */
    rowColZero(input,x,y);
    cout << "After: " << endl;
    for(int m =0; m < y; ++m) {
        cout << "   ";
        for (int n=0; n<x; ++n) {
            cout << input[n][m] << " ";
        }
        cout <<endl;
    }


    return 0;
}
