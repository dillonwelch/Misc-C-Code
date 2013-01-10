#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

/*** Same as sort strings but the array size is not known... ***/
using namespace std;

const int INIT_SIZE = 10;

int compString(const void *a, const void *b);
int compStringCase(const void *a, const void *b);
void readStrings(vector<string>& words);
void printStrings(string *word, int numWords);

int main() {
  /*** Read in a list of strings of no more than MAX_SIZE words ***/
  vector<string> words;

  readStrings(words);

  int numWords = words.size();
  string* word = new string[numWords];
  vector<string>::iterator it = words.begin();  // Iterate through the vector list
  int i;
  for (i=0; it != words.end(); it++, i++) {
    word[i] = *it;
  }

  /*** sort the strings ***/
  /*** Using qsort:
       void qsort(void *base, size_t nmemb, size_t size,
                  int(*compar)(const void *, const void *));
       compar - is a function that takes two pointers to entries to compare
  ***/
  qsort(word, numWords, sizeof(string), compStringCase);

  /*** print the strings ***/
  printStrings(word, numWords);

  return 0;
}

/*** Returns <0 if a < b, 0 if a == b, >0 if a > b ***/
int compString(const void *a, const void *b) {
  string* strA = (string*) a;  // Convert to pointers to strings now
  string* strB = (string*) b;

  return strA->compare(*strB);
}

/*** Returns <0 if a < b, 0 if a == b, >0 if a > b 
 ***   This version is case insensitive
 ***/

inline char toUpper(char c) {
  return (c >= 'a' && c <= 'z') ? c+('A'-'a') : c;
}

int compStringCase(const void *a, const void *b) {
  int i;
  string* strA = (string*) a;  // Convert to pointers to strings now
  string* strB = (string*) b;

  
  // Letter by letter comparison - converting case as needed
  const char* cA = strA->c_str();
  const char* cB = strB->c_str();

  for (i = 0; cA[i] != 0 && cB[i] != 0 && toUpper(cA[i]) == toUpper(cB[i]); i++);

  if (cA[i] == 0) {
    if (cB[i] == 0) return 0;
    else
      return -1;
  } 

  if (cB[i] == 0) {
    // B is shorter
    return 1;
  }

  if (toUpper(cA[i]) < toUpper(cB[i])) 
    return -1;
  else
    return 1;
}

void printStrings(string *word, int numWords) {
  int i;
  for (i = 0; i < numWords; i++)
    cout << word[i] << endl;
}

/***
 * reads in strings from standard in until EOF
 *    GrowString is a created class that dynamically grows an array
 *    int& === pass by REFERENCE (C++ specific)
 ***/
void readStrings(vector<string>& words) {
  string word;
  cin >> word;
  while (!cin.eof()) {
    // Don't add blank lines
    if (word.length() > 0) 
      words.push_back(word);  // Add word to the vector

    cin >> word;
  }
}
