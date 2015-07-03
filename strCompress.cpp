#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

// 1.5
size_t countConsecutive (char c, string input, size_t start_index) {
    size_t i = start_index;
    size_t count = 0;

    while (input[i] == c) {
        count++;
        i++;
    }

    return count;
}

string strCompress(string input) {
    size_t i = 0;
    size_t offset;

    string compressed;

    while (i < input.length()) {
        offset = countConsecutive(input[i], input, i);

        compressed[i] = input[i];
        compressed[i+1] = offset;      // Q: why doesn' this automatically typecast?
        //compressed += input[i] + offset;
        cout << "compressed[i]: " << compressed[i] << endl;
        cout << "compressed[i+1]: " << compressed[i+1] << endl;
        //cout << "COMPRESSED: " << compressed << endl;

        i += offset;
    }
    return compressed;
}

int main() {
    string in("aabcccccaaa");
    string out = strCompress(in);
    cout << out << endl;
    return 0;
}
