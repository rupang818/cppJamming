#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

//1.6
int** rotateMatrix(int** input_matrix, int x, int y) {
    // X x Y = 3 x 4
    int** output_matrix = new int*[x];

    for (int i = y - 1; i >= 0; --i) {
        output_matrix[i] = new int[y];

        for (int j = 0; j < x; ++j) {
          /*  cout << "source : (" << j << "," << y-i-1 << ")" << endl;
            cout << "target : (" << i << "," << j << ")" << endl;
            cout << endl;*/
            output_matrix[i][j] = input_matrix[j][y - i - 1];
/*cout << "input_matrix[" << j << "][" << y-i-1 << "]="  << input_matrix[j][y - i - 1] << endl;
            cout << "output_matrix[" << i << "][" << j << "]=" << output_matrix[i][j] <<endl;*/
        }
    }

    return output_matrix;
}

int main () {
    // 3x4 matrix
    int x = 3;
    int y = 4;
    int dummy_val =  0;
    int** input = new int*[y];

    cout << "Initial Matrix: " << endl;
    for(int i =0; i < x; ++i) {
        input[i] = new int[x];
        for (int j=0; j<y; ++j) {
            input[i][j] = dummy_val++;
        }
    }

    for(int m =0; m < y; ++m) {
        cout << "   ";
        for (int n=0; n<x; ++n) {
            cout << input[n][m] << " ";
        }
        cout <<endl;
    }


    cout << "Rotated Matrix: " << endl;
    int** retVal = rotateMatrix(input, x, y);
    for (int k=0; k < x; ++k) {
        cout << "   ";
        for (int l=0; l < y; ++l) {
            cout << retVal[l][k] << " ";
        }
        cout << endl;
    }

    cout << "Suzanne's matrix: " << endl;
    int** retVal2 = rotateMatrix(retVal, y, x);
    for (int o=0; o < y; ++o) {
        cout << "   ";
        for (int p=0; p < x; ++p) {
            cout << retVal2[p][o] << " ";
        }
        cout << endl;
    }
    return 0;
}
