#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;

/** TODO: Bug when MAX_SIZE_OF_WORD = 1 */

/* Variable declarations */
// Constants for ASCII values.
const char LOWER_CASE_A = 97;
const char SPACE = 32;
const char UPPER_CASE_A = 65;
const char ZERO = 48;

char* asciiList; // List to hold all the ASCII characters that are going to be used in the dictionary generation.
int AMOUNT_OF_CHARACTERS = 26; // The total amount of characters in the character list.

// Amount of ASCII characters in the various groupings.
const int AMOUNT_OF_ASCII = 128;
const int AMOUNT_OF_INVALID = 33;
const int AMOUNT_OF_CHARACTERS_LOWER = 26;
const int AMOUNT_OF_CHARACTERS_UPPER = 26;
const int AMOUNT_OF_CHARACTERS_NUMERIC = 10;
const int AMOUNT_OF_CHARACTERS_MISC = AMOUNT_OF_ASCII - AMOUNT_OF_INVALID - AMOUNT_OF_CHARACTERS_LOWER - AMOUNT_OF_CHARACTERS_UPPER - AMOUNT_OF_CHARACTERS_NUMERIC;

// Constants for the various character groups.
const int USE_LOWER = 0;
const int USE_LOWER_UPPER = 1;
const int USE_LOWER_UPPER_NUMERIC = 2;
const int USE_ALL = 3;

int MAX_SIZE_OF_WORD = 2; // The size of the biggest string generated (argument 1).

string* dictionaryList; // List of all the temporary dictionary files made.
int dictionaryListCounter = 0;
const string dictionaryName = "Dictionary.txt";

/* Function declarations */
void createAsciiList(int choiceCode);
void combineDictionaries();
void helpPrintOut();
void printArray(string arr[], int size);
void test(int iteration, int wordLength);

/* Main */
int main(int argc, char* argv[])
{
	if(argv[1] == NULL || argv[2] == NULL)
	{
		cerr << "Error: Please give arguments, or ? for help." << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		if(argv[1][0] == '?') // If the first argument is a question, display the help dialog and close the program.
		{
			helpPrintOut();
			exit(EXIT_SUCCESS);
		}
		else // Otherwise, get the values of the arguments and generate the dictionary.
		{
			int wordSize = atoi(argv[1]);
			int charSet = atoi(argv[2]);

			if(wordSize > 0)
			{
				MAX_SIZE_OF_WORD = wordSize;
			}
			else
			{
				cerr << "Error: Please input an int > 0 for max word size." << endl;
				exit(EXIT_FAILURE);
			}

			if(charSet >= 0)
			{
				createAsciiList(charSet);
			}
			else
			{
				cerr << "Error: Please input a valid character set number." << endl;
				exit(EXIT_FAILURE);
			}

			dictionaryList = new string[MAX_SIZE_OF_WORD];
			test(1, 2);
			combineDictionaries();
		}
	}
}

void createAsciiList(int choiceCode)
{
	switch(choiceCode)
	{
		case USE_LOWER:
			{
				AMOUNT_OF_CHARACTERS = AMOUNT_OF_CHARACTERS_LOWER;
				asciiList = new char[AMOUNT_OF_CHARACTERS];
				for(int a = LOWER_CASE_A, i = 0; i < AMOUNT_OF_CHARACTERS_LOWER; a++, i++)
				{
					asciiList[i] = a;
				}
				break;
			}
		case USE_LOWER_UPPER:
			{
				AMOUNT_OF_CHARACTERS = AMOUNT_OF_CHARACTERS_LOWER + AMOUNT_OF_CHARACTERS_UPPER;
				asciiList = new char[AMOUNT_OF_CHARACTERS_LOWER + AMOUNT_OF_CHARACTERS_UPPER];
				for(int a = LOWER_CASE_A, i = 0; i < AMOUNT_OF_CHARACTERS_LOWER; a++, i++)
				{
					asciiList[i] = a;
				}
				for(int a = UPPER_CASE_A, i = AMOUNT_OF_CHARACTERS_LOWER, j = 0; j < AMOUNT_OF_CHARACTERS_UPPER; a++, i++, j++)
				{
					asciiList[i] = a;
				}
				break;
			}
		case USE_LOWER_UPPER_NUMERIC:
			{
				AMOUNT_OF_CHARACTERS = AMOUNT_OF_CHARACTERS_LOWER + AMOUNT_OF_CHARACTERS_UPPER + AMOUNT_OF_CHARACTERS_NUMERIC;
				asciiList = new char[AMOUNT_OF_CHARACTERS];
				for(int a = LOWER_CASE_A, i = 0; i < AMOUNT_OF_CHARACTERS_LOWER; a++, i++)
				{
					asciiList[i] = a;
				}
				for(int a = UPPER_CASE_A, i = AMOUNT_OF_CHARACTERS_LOWER, j = 0; j < AMOUNT_OF_CHARACTERS_UPPER; a++, i++, j++)
				{
					asciiList[i] = a;
				}
				for(int a = ZERO, i = AMOUNT_OF_CHARACTERS_LOWER + AMOUNT_OF_CHARACTERS_UPPER, j = 0; j < AMOUNT_OF_CHARACTERS_NUMERIC; a++, i++, j++)
				{
					asciiList[i] = a;
				}
				break;
			}
		case USE_ALL:
			{
				AMOUNT_OF_CHARACTERS = AMOUNT_OF_CHARACTERS_LOWER + AMOUNT_OF_CHARACTERS_UPPER + AMOUNT_OF_CHARACTERS_NUMERIC + AMOUNT_OF_CHARACTERS_MISC;
				asciiList = new char[AMOUNT_OF_CHARACTERS];
				for(int a = LOWER_CASE_A, i = 0; i < AMOUNT_OF_CHARACTERS_LOWER; a++, i++)
				{
					asciiList[i] = a;
				}
				for(int a = UPPER_CASE_A, i = AMOUNT_OF_CHARACTERS_LOWER, j = 0; j < AMOUNT_OF_CHARACTERS_UPPER; a++, i++, j++)
				{
					asciiList[i] = a;
				}
				for(int a = ZERO, i = AMOUNT_OF_CHARACTERS_LOWER + AMOUNT_OF_CHARACTERS_UPPER, j = 0; j < AMOUNT_OF_CHARACTERS_NUMERIC; a++, i++, j++)
				{
					asciiList[i] = a;
				}
				for(int a = SPACE, i = AMOUNT_OF_CHARACTERS_LOWER + AMOUNT_OF_CHARACTERS_UPPER + AMOUNT_OF_CHARACTERS_NUMERIC, j = 0; j < AMOUNT_OF_CHARACTERS_MISC; a++, i++, j++)
				{
					switch(a)
					{
						case ZERO:
							{
								a += AMOUNT_OF_CHARACTERS_NUMERIC;
								break;
							}
						case LOWER_CASE_A:
							{
								a += AMOUNT_OF_CHARACTERS_LOWER;
								break;
							}
						case UPPER_CASE_A:
							{
								a += AMOUNT_OF_CHARACTERS_UPPER;
								break;
							}
					}
					asciiList[i] = a;
				}
				break;
			}
		default:
			{
				cerr << "Error: The character set number " << choiceCode << " is invalid." << endl;
				exit(EXIT_FAILURE);
			}
	}
}

/* Function definitions */
void combineDictionaries()
{
	ofstream writeFile;
	writeFile.open(dictionaryName.c_str());
	bool firstLine = true;
	for(int i = 0; i < MAX_SIZE_OF_WORD; i++)
	{
		ifstream readFile;
		readFile.open(dictionaryList[i].c_str());
		
		while(readFile.good())
		{
			if(!firstLine)
			{
				writeFile << "\n";
			}
			else
			{
				firstLine = false;
			}
			string line;
			getline(readFile, line);
			writeFile << line;
		}

		readFile.close();
		if(remove(dictionaryList[i].c_str()) != 0)
		{
			cerr << "Error deleting file " + dictionaryList[i] << endl;
		}
	}
}

void helpPrintOut()
{
	cout << "Argument 1: Max word size in the dictionary (integer > 0)." << endl;
	cout << "For example, 4 would create a dictionary with all combinations with \n*, **, ***, and ****." << endl << endl;
	cout << "Argument 2: Character set to create combinations out of (0 <= # <= 3)." << endl;
	cout << "0 - Lower case letters only." << endl;
	cout << "1 - Lower case and upper case letters." << endl;
	cout << "2 - Lower case letters, upper case letters, and numbers." << endl;
	cout << "3 - All valid ASCII characters." << endl << endl;
	cout << "For example, program_name 4 2 would create a dictionary file with \nall combinations of lower case letters, upper case letters, and \nnumbers of size 1, 2, 3, and 4." << endl;
}

void printArray(string arr[], int size)
{
	for(int a = 0; a < size; a++)
	{
		cout << arr[a] << endl;
	}
}

void test(int iteration, int wordLength)
{
	if(iteration == 1)
	{
		// Make the initial list, and write a-z to it.
		string newFileName = "Dictionary 1.txt";
		dictionaryList[dictionaryListCounter] = newFileName;
		dictionaryListCounter++;
		ofstream writeFile;
		writeFile.open(newFileName.c_str());

		bool firstLine = true;
		//for(int i = 0, a = START_CHAR; i < AMOUNT_OF_CHARACTERS; i++, a++)
		for(int i = 0; i < AMOUNT_OF_CHARACTERS; i++)
		{
			if(!firstLine)
			{
				writeFile << "\n";
			}
			else
			{
				firstLine = false;
			}
			writeFile << asciiList[i];
		}
		writeFile.close();

		// If we have 1+ letters to go, call it again.
		if(iteration < wordLength)
		{
			test(iteration + 1, wordLength);
		}
	}
	else
	{
		// Open up the previous list, and make the new one.
		string iterationString;
		stringstream out;
		int oldIteration = iteration - 1;
		out << oldIteration;
		iterationString = out.str();
		string oldFileName = "Dictionary " + iterationString + ".txt";
		stringstream out2;
		out2 << iteration;
		iterationString = out2.str();
		string newFileName = "Dictionary " + iterationString + ".txt";

		dictionaryList[dictionaryListCounter] = newFileName;
		dictionaryListCounter++;
		
		ifstream readFile;
		readFile.open(oldFileName.c_str());
		ofstream writeFile;
		writeFile.open(newFileName.c_str());	
	
		// Take each line in the previous file, and make a new string with a letter appended to the end, then write it to the new file.
		// For example: aa -> aaa, aab, aac, aad...
		
		bool firstLine = true;
		for(int i = 0; i < pow(AMOUNT_OF_CHARACTERS, iteration - 1); i++)
		{
			string line;
			getline(readFile, line);
			//for(int a = LOWER_CASE_A; a <= LOWER_CASE_Z ; a++)
			for(int a = 0; a < AMOUNT_OF_CHARACTERS; a++)
			{	
				if(!firstLine)
				{
					writeFile << "\n";
				}
				else
				{
					firstLine = false;
				}
				string s = line;
				string result =  s.append(1, asciiList[a]);
				writeFile << result;
			}
		}

		readFile.close();
		writeFile.close();

		// If we have 1+ letters to go, call it again.
		if(iteration < wordLength)
		{
			test(iteration + 1, wordLength);
		}

	}
}
