#include <iostream>
#include "huffman.hpp"
using namespace std;

int main() {
    string s1 , s2;
    cout << "enter the input file path";
    cin >> s1;

    cout << "enter the terminal file path";
    cin >> s2;

    huffman f(s1, s2);
    f.compress();
    cout << "Compressed successfully" << endl;

    return 0;
}
