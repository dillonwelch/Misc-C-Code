#include <iostream>
#include <string>
#include <stdlib.h>

/*** Same as sort strings but the array size is not known... ***/
using namespace std;

const int INIT_SIZE = 10;

class GrowString {
  string* word;
  int capacity;
  int numElements;

public:
  /*** Constructor: Create initial array for storing information ***/
  GrowString() { 
    word = new string[INIT_SIZE]; capacity = INIT_SIZE; numElements = 0;
  }

  /*** Destructor: Free allocated memory ***/
  ~GrowString() { delete[] word; }

  /*** Accessor: Direct access to the array - not proper O-O style!! ***/
  string* getArray() { return word; }

  int getNumElements() { return numElements; }

  void add(string w) {
    if (numElements >= capacity) {
      // Reached capacity, increase size
      ensureCapacity(numElements * 2);
    }

    word[numElements] = w;
    numElements++;
  }

  void ensureCapacity(int x) {
    if (capacity >= x) 
      // Already have this capacity
      return;

    // Increase capacity of a new array and copy contents over
    capacity = x;
    string* word2 = new string[capacity];
    
    int i;
    for (i = 0; i < numElements; i++) 
      word2[i] = word[i];
  
    delete[] word;
    word = word2;
  }
};

int compString(const void *a, const void *b);
int compStringCase(const void *a, const void *b);
void readStrings(GrowString& words);
void printStrings(string *word, int numWords);

int main() {
  /*** Read in a list of strings of no more than MAX_SIZE words ***/
  GrowString words;

  readStrings(words);
  string* word = words.getArray();
  int numWords = words.getNumElements();

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
void readStrings(GrowString& words) {
  string word;
  cin >> word;
  while (!cin.eof()) {
    // Don't add blank lines
    if (word.length() > 0) 
      words.add(word);

    cin >> word;
  }
}
