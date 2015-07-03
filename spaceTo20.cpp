#include <iostream>
#include <string>
#define MAX 100

using namespace std;

//1.4
// trick - to traverse from backwards to allocate enough space for the new characters
void spaceTo20 (char* input) {
    size_t len = 0;
    size_t spaceCnt = 0;

    // first calculate the length & number of spaces
    for (size_t i =0; input[i] != '\0'; ++i) {
        if (input[i] == ' ') spaceCnt++;
        len++;
    }

    // each space -> 3 char spaces
    size_t length_with_spaces = len + 2 * spaceCnt;

    while (len >= 0) {
        if (input[len] == ' ') {
            //then translate
            //Q: Would the space in memory be automatically allocated if the index out of bounds (i.e. index > len) is specified?
            input[length_with_spaces--] = '0';
            input[length_with_spaces--] = '2';
            input[length_with_spaces--] = '%';
        } else {
            input[length_with_spaces--] = input[len];
        }
        len--;
    }

}

int main() {
    char chArray[MAX];
    gets(chArray);
    spaceTo20(chArray);
    cout<<"hi" << chArray<<endl;
    return 0;
}
