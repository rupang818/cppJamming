#include <iostream>

using namespace std;

public bool uniqueChars(string input) {
    // using additional data structure - can tally the result in a hash (i.e. key = char, value = # of occur)
    // O(n)
    bool char_list = new boolean[256]; //because there are 256 unique characters

    for (int i=0; i < input.length(); ++i) {
        int value = input.charAt(i);
        if (char_list[value]) return false;
        char_list[value] = true;
    }

    return true;


    // NOT using additional data structure - O(n^2)
    for (int i=0; i <input.length(); ++i) {
        for (int j=i+1; j < input.length(); ++j) {
            if (input[i] == input[j])
                return false;
        }
    }
    return true;
}

int main() {

    return 0;
}
