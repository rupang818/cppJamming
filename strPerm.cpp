#include <iostream>
#include <string>

using namespace std;

//if one str is a permutation of another, it means the str1 can be rearranged to form str2
bool strPerm(string str1, string str2) {
    // brute force: O(n^2)
    /*
    for (size_t i =0; i<str1.length(); ++i) {
        for (size_t j =0; i<str2.length(); ++j) {
            if (str1[i] == str2[j]) {
                // if the match is found in str2, remove the letter but keep the rest of the substr
                string tmp_str = str2.substr(0,j-1);
                tmp_str.append(str2.substr(j+1, str2.length()));
                str2 = tmp_Str
                cout << "substring now is: " << tmp_str << endl;
                break;
            }
        }
    }
    return true; */

    // Solution 1: sort the string and compare the length
    sort(str1.begin(),str1.end());
    //cout << "This is str1: " << str1 <<endl;
    sort(str2.begin(),str2.end());
    //cout << "This is str2: " << str2 << endl;

    //int out = str1.compare(str2);
    //cout << "Comparison results: " << out << endl;
    if (str1.compare(str2) == 0) return true;
    else return false;
}

int main() {
    bool retval = strPerm("hello", "olleh");
    cout << retval <<endl;

    retval = strPerm("hallo", "halo");
     cout << retval <<endl;

    return 0;
}
