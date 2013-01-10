#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

const int MAX_SIZE = 1000;

int compString(const void *a, const void *b);
int compStringCase(const void *a, const void *b);
void readStrings(string *words, int& numWords);
void printStrings(string *word, int numWords);

int main() {
  /*** Read in a list of strings of no more than MAX_SIZE words ***/
  string word[MAX_SIZE];
  int numWords;

  readStrings(word, numWords);

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
 *   WARNING: Does NOT CHECK FOR array out of bounds!!!
 *    int& === pass by REFERENCE (C++ specific)
 ***/
void readStrings(string *words, int& numWords) {
  numWords = 0;
  while (!cin.eof()) {
    cin >> words[numWords];
    numWords++;
  }

  // Check if last entry is a blank line - and delete if so
  if (numWords > 0 && words[numWords-1].length() == 0) {
    numWords--;
  }
}
