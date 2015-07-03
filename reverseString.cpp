#include <iostream>
#include <string>

using namespace std;

string reverse(string str) {
    string reversed = "";

    for (size_t i=0; i<str.length(); ++i) {
        reversed = str[i] + reversed;
    }

    return reversed;
}

int main () {
    string out = reverse("hello");
    cout << out << endl;
    return 0;
}

