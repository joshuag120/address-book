/*
 * main.c
 *
 *  Created on: Nov 24, 2021
 *      Author: jgianelli
 */

#include "addressBook.h"

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);

	/*
	 * pHead instantiated to NULL, will later be updated to reflect the head of the linked list.
	 * pContact instantiated to NULL, will later be updated constantly to reflect the current contact
	 * in list depending on index.
	 */
	Contact* pHead = NULL;
	Contact* pContact = NULL;

	int menu = 0; // menu boolean to handle quit case
	char usrSelection[10]; // buffer to handle user input for switch case statement below (size arbitrary)
	char info[1024]; // buffer to take in user input other than single character (contact info, filename, etc)
	int indInput; // index integer holds usrSelection with atoi function in some cases.
	puts("Ready");
	while (!menu) {
		fgets(usrSelection, 10, stdin);
		switch(usrSelection[0]) { // checks the first element of the usrSelection array
		case 'a':
			//ADD A NEW CONTACT
			indInput = atoi(fgets(info, 1023, stdin));
			fgets(info, 1023, stdin); //gets info for contact
			info[strlen(info)-1] = '\0';
			pContact = FindPrevNode(pHead, indInput); // FindPrevNode returns pointer to Contact at previous node from given indInput
			pContact = InsertContact(&pHead, pContact, info); // InsertContact then takes head address, previous pointer and contact info
			break;
		case 'd':
			//DELETE A CONTACT
			indInput = atoi(fgets(info, 1023, stdin));
			pContact = FindNode(pHead, indInput); // FindNode returns the pointer directly at the specified input
			pContact = DeleteContact(&pHead, pContact); // DeleteContact deletes specified node from index found with above function
			break;
		case 'g':
			indInput = atoi(fgets(info, 1023, stdin));
			PrintContact(pHead, indInput); // Prints contact at specified index, "getting" the total contact field
			break;
		case 'f':
			indInput = atoi(fgets(info, 1023, stdin));
			fgets(info, 1023, stdin);
			info[strlen(info)-1] = '\0';
			PrintContactField(pHead, indInput, info); // Prints specified field at specified index, only "getting" select field
			break;
		case 'n':
			printf("%d\n", NumNodes(pHead)); // NumNodes returns integer with number of nodes present in list
			break;
		case 'l':
			fgets(info, 1023, stdin);
			info[strlen(info)-1] = '\0';
			LoadCSV(&pHead, info); // Loads csv file inputted by user, assumes the file exists in the program directory
			break;
		case 's':
			fgets(info, 1023, stdin);
			info[strlen(info)-1] = '\0';
			SaveCSV(pHead, info); // Takes current address book and saves all contacts to csv file with name specified
			break;
		case 'q':
			menu = 1; // Exits the menu while loop terminating the program
			puts("Complete");
			break;
		case 'p':
			PrintList(pHead); // Helper function to print out all contacts in address book.
			break;
		default:
			break;
		}
	}
	return EXIT_SUCCESS;
}
