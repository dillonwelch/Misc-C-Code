//
// permutations.cpp: Generate all permutations of
// letters of words
//
// You can redirect the output to a file if you want
// to capture the list of permutations.
//
// Posted on gidforums by
//     davekw7x
//
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string str;
    //
    // Use cerr so that if the permutations are redirected
    // to a file, the user will still see the prompt
    //
    cerr << "Enter some stuff: ";
    getline(cin, str);
    cerr << endl;
    cout << "Permutations for " << str << endl;

    sort(str.begin(), str.end());
    int num = 0;
    do {
        ++num;
        cout << str << endl;
    } while (next_permutation(str.begin(), str.end()));
    //
    // Use cerr so that if the permutations are redirected
    // to a file, the user will still see the summary.
    //
    cerr << "Total number of permutations = " << num << endl;

    return 0;
}
