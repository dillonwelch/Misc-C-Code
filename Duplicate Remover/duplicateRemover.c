/***********************************************************************************************************
 * duplicateRemover.c
 * Removes duplicates from a list of text, with one item per line.
 * Author: Dillon Welch
 * Date:
 * 1.0 - 07/29/2011
 * 1.1 - 08/01/2011 : Added quoteAdder(), edited printToFile(), added option as a global var, added
 *		      doesFileExist() and quitting if the file doesn't exist, added option 2 of 
 *		      concatenating ' and ', to each item in the list, memory leak fixes (freeLinkedList())
 *		      and tweaks to the menu process in main().
 * 1.2 - 10/14/2011 : Fixed quoteAdder() and added testForNewline()
 ***********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> 

/* Function prototypes */
char* quoteAdder(char *text);

int doesFileExist(char *fileName);
int duplicates(char *text);
int printToFile();
int testForNewline(char* text);

void addToEnd(char *text);
void display();
void freeLinkedList();

/* Constant global variables */
const char *DEFAULT_OUTPUT_FILE = "Output.txt"; // The name of the default output file.

const int LINE_LENGTH = 80; // Length of a line.

/* Global variables */
char *qholder;		// Holder for line in quoteAdder(), made global so it can be freed.
char *outputFileName;	// Name of the output file.

FILE *input;	// Stream for the input file.
FILE *output;	// Stream for the output file.

int option;     // The mode in which the program is run.

/* Structures */
struct Node // Individual entries in the linked list.
{
	char *line;		    // Value of a line in the file.
	struct Node *next;	// Pointer to the next entry.
}*head;

/***** Start of program *****/
/*
 * char* quoteAdder(char* text)
 * Turns text into 'text',
 * Used for making an SQL query.
 * Returns a pointer to the edited text. Reference is borrowed, you must copy the value to keep it.
 */
char* quoteAdder(char* text)
{
	int length = strlen(text);	// Length of passed in string.
	char* temp;			// String used to hold text + newline marker
	if(testForNewline(text) == 0)	// If text does not have an newline marker, add one to the end.
	{
		temp = malloc(sizeof(char) * (length + 1));
		strncpy(temp, text, length);
		*(temp + length) = '\n';
		length = strlen(temp);
	}
	else	// Set temp to original value if original value already has a newline, used to not juggle two char* variables.
	{
		temp = text;
	}
	qholder = malloc(sizeof(char) * (length + 4)); // Holder for the value of text, used to append the '.
	memset(qholder, '\0', length + 4);  // Zero out the allocated memory.
	*qholder = '\'';	                // Set ' to the beginning of holder.
	strncat(qholder, temp, length + 1);	// Concatenate text with holder.
	length = strlen(qholder);
	*(qholder + length - 1) = '\'';	// Add ' after text.
	*(qholder + length) = ',';	// Add , after text.
	*(qholder + length + 1) = '\0';  // Null terminate the array.
	if(temp != text)	// If memory was allocated for temp, free it.
	{
		free(temp);
	}
	return qholder;
}

/*
 * int doesFileExist(char *fileName)
 * Tests to see if a file exists.
 * Returns 0 if the file exists.
 * Returns non-zero if the file does not exist.
 */
int doesFileExist(char *fileName)
{
	int exists;
	struct stat fileInfo;

	exists = stat(fileName, &fileInfo);
	return exists;
}

/*
 * int duplicates(char *text)
 * Tests the linked list to see if it contains the value of text.
 * Returns 0 if the linked list is empty or it does not contain the value text.
 * Returns 1 if text is already in the linked list.
 */
int duplicates(char *text)
{
	struct Node *currentPointer;
	currentPointer = head;

	if(currentPointer == NULL)
	{
		return 0;
	}
	else
	{
		for(; currentPointer != NULL; currentPointer = currentPointer->next)
		{
			if(strncmp(currentPointer->line, text, strlen(text)) == 0)
			{
				return 1;
			}
		}
		return 0;
	}
	return 0;
}

/*
 * int printToFile()
 * Saves the linked list to outputFileName.
 * Returns 0 if the save was successful.
 * Returns 1 if the linked list was empty.
 */
int printToFile()
{
	int counter = 1;	      // The amount of items that have been printed.
	int amountPerLine = 5;	      // The amount of items to be printed on a line.
	struct Node *currentPointer;  // Variable to iterate through the linked list with.
	currentPointer = head;

	// If there is at least one element in the linked list, open up a file
	// and save each element of the linked list to it.
	if(currentPointer != NULL)
	{
		output = fopen(outputFileName, "w+");
		if(option == 2) // Making an SQL query, so append a ( to enclose.
		{
			fprintf(output, "(");
		}

		for(; currentPointer != NULL; currentPointer = currentPointer->next)
		{
			if(currentPointer->next == NULL && option == 2)         // Making an SQL query, so append a ) to enclose.
			{
				int length = strlen(currentPointer->line);
				*(currentPointer->line + length - 1) = ')';
				*(currentPointer->line + length) = '\0';    
			}
			fprintf(output, currentPointer->line);		        // Print the line to the file.
			if(counter % amountPerLine == 0 && option == 2)		// Making an SQL query, so format it so there are 5 to a line.
			{
				fprintf(output, "\n");
			}
			counter++;
		}
		fclose(output);
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
 * int testForNewline(char* text)
 * Tests to see if text has an Newline marker.
 * Returns 0 if it does not.
 * Returns 1 if it does.
 */
int testForNewline(char* text)
{
	int i = 0;
	int length = strlen(text);
	for(; i < length; i++)	// While there are still supposed to be values in text.
	{
		if(*(text + i) == '\0' || *(text + i) == '\n')	// If there is an endline or newline, return 1.
		{
			return 1;
		}
	}
	return 0;	// If there is no endline or newline, return 0 so quoteAdder() will add one.
}

/*
 * void addToEnd(char *text)
 * Adds a node to the end of the linked list, or creates the head if it is empty.
 */
void addToEnd(char *text)
{
	if(duplicates(text) == 0) // If the entry isn't already in the linked list.
	{
		struct Node *temp1, *temp2; // temp1 is the new entry, temp2 is for cycling through the linked list.
	
		temp1=(struct Node *)malloc(sizeof(struct Node)); // Create the new entry and give it the value of text.
		temp1->line = strdup(text);

		temp2 = head; // Start at the beginning of the linked list.

		if(head == NULL) // If the linked list is empty, start it.
		{
			head = temp1;
			head->next = NULL;
		}
		else
		{
			while(temp2->next != NULL) // While we are not at the last entry of the linked list.
			{
				temp2 = temp2->next;
			}
		
			temp1->next = NULL;  // Set this as the last entry in the linked list.
			temp2->next = temp1; // Set the pointer in the previously last entry to the new entry.
		}
	}
}

/*
 * void display()
 * Prints each element of the linked list.
 */
void display()
{
	struct Node *currentPointer;
	currentPointer = head;

	if(currentPointer == NULL)
	{
		printf("List is empty.\n");
	}
	else
	{
		printf("Display the elements in the list:\n");
		for(; currentPointer != NULL; currentPointer = currentPointer->next)
			printf("%s\n", currentPointer->line);
	}
}

/*
 * void freeLinkedList()
 * Frees all memory associated with the linked list.
 */
void freeLinkedList()
{
	struct Node *currentPointer;
	currentPointer = head;
	while(currentPointer != NULL)
	{
		if(currentPointer->line != NULL)
			free(currentPointer->line);
		struct Node *next = currentPointer->next;
		free(currentPointer);
		currentPointer = next;
	}
	head = NULL;
}

int main(int argc, char* argv[])
{
	char *inputFileName = calloc(LINE_LENGTH + 1, sizeof(char));	// Name of the file to be opened.
	outputFileName = calloc(LINE_LENGTH + 1, sizeof(char));         // Name of the file to be saved to. 
	option = 0; // Menu option
	
	char line[LINE_LENGTH];	// Variable to store each line of the file.

	printf("Please input the name of the input file.\n");
	scanf("%s", inputFileName);

	if(strcmp(inputFileName, "Test") == 0) // Test input
	{
		strcpy(inputFileName, "Input.txt");
		strcpy(outputFileName, DEFAULT_OUTPUT_FILE);
		option = 2;
	}
	else // Regular input
	{
		if(doesFileExist(inputFileName) != 0) // If the input file does not exist, exit.
		{
			fprintf(stderr, "The file does not exist. Please run the program and try again.\n");
			exit(EXIT_FAILURE);
		}

		printf("Please input the name of the output file. Type in -1 to save to the default file (Output.txt).\n");
		scanf("%s", outputFileName);
		if(strcmp(outputFileName, "-1") == 0) // If -1, use the default file.
		{
			strcpy(outputFileName, DEFAULT_OUTPUT_FILE);
		}

		printf("Please type in the number for the option you wish to run.\n");
		printf("1: Basic duplicate remover, saved as one entry per line.\n");
		printf("2: 1 + Adds ' to the front and end as well as , after the ending ' and open/close parenthesis. Saved as five entries per line.\n");
		scanf("%d", &option);
	}

	input = fopen(inputFileName, "r");	// Open the file to be read.
	
	while(fgets(line, LINE_LENGTH, input) != NULL)	// Read through each line of the file
	{
		if(option == 1)
		{
			char *test = line;	// Gave me errors when I didn't save as a char*.
			addToEnd(test);		// Add the line to the linked list if it isn't a duplicate.
		}
		else if(option == 2) // Concatenate ' and ', to beginning and end of the value
		{
			char *holder = line;
			holder = strdup(quoteAdder(holder));
			addToEnd(holder);
			
			free(qholder); // Free the memory allocated for this line.
			free(holder);
		}
	}

	if (printToFile() == 0) // If the save was successful.
	{
		printf("The values were saved to %s.\n", outputFileName);
	}
	else
	{
		fprintf(stderr, "The linked list was empty.\n");
	}
	freeLinkedList();
	fclose(input);
	free(inputFileName);
	free(outputFileName);
	return 0;
}
