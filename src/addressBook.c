/*
 * addressBook.c
 *
 *  Created on: Nov 24, 2021
 *      Author: jgianelli
 */

#include "addressBook.h"

Contact* FindPrevNode(Contact *pContact, int targInd) {
	/*
	 * Finds and returns pointer to previous node than the index given (targInd).
	 */
	if (targInd == 0) {
		return NULL;
	} else {
		for (int i = 1; i < targInd; i++) {
			pContact = pContact->pNext;
		}
	}
	return pContact;
}

Contact* FindNode(Contact *pContact, int targInd) {
	/*
	 * Finds and returns pointer to node specified by targInd.
	 */
	if (targInd > NumNodes(pContact)) { // Handles case where targIndex is greater than number of nodes in list
		return NULL;
	}
	for (int i = 0; i < targInd; i++) { // Loop to go through and find node.
		pContact = pContact->pNext;
	}
	return pContact;
}

Contact* CreateContact(char *info) {
	Contact *pNewContact = (Contact*) malloc(sizeof(Contact)); // New contact created with malloc

	if (pNewContact) { // If the new contact is created successfully
		/*
		 * Copies all information given to the designated fields using strtok()
		 */
		strcpy(pNewContact->lastName, strtok(info, ","));
		strcpy(pNewContact->firstName, strtok(NULL, ","));
		strcpy(pNewContact->email, strtok(NULL, ","));
		strcpy(pNewContact->phoneNum, strtok(NULL, ","));

		pNewContact->pPrev = NULL;
		pNewContact->pNext = NULL;

	}
	return pNewContact; // Returns new contact
}

Contact* InsertContact(Contact **ppFirst, Contact *pPrev, char *info) {
	Contact *pContactNew; // NULL pointer to new contact (filled below)

	pContactNew = CreateContact(info); // CreateContact() is only called here to save complexity on author's end.

	if (pPrev) { // Inserting not at beginnning
		pContactNew->pPrev = pPrev;
		pContactNew->pNext = pPrev->pNext;
		pPrev->pNext = pContactNew;
		if (pContactNew->pNext) { // If not last contact
			pContactNew->pNext->pPrev = pContactNew;
		}
	} else { // Inserting at beginning
		pContactNew->pPrev = NULL;
		pContactNew->pNext = (*ppFirst);
		if ((*ppFirst)) {
			(*ppFirst)->pPrev = pContactNew;
		}
		(*ppFirst) = pContactNew;
	}
	return pContactNew;
}

Contact* DeleteContact(pContact *ppFirst, Contact *pContact) {
	Contact *pContactReturn;

	if (pContact == NULL) {
		return NULL; // Safety check
	}

	if (pContact == (*ppFirst)) { // Delete first contact
		if (pContact->pNext) {
			pContactReturn = pContact->pNext;
			(*ppFirst) = pContactReturn;
			pContactReturn->pPrev = NULL;
		} else { // Only 1 contact in list
			pContactReturn = NULL;
			(*ppFirst) = NULL;
		}
	} else { // Not deleting head contact
		if (pContact->pNext) { // Not last contact in list
			pContactReturn = pContact->pNext;
			pContactReturn->pPrev = pContact->pPrev;
			pContact->pPrev->pNext = pContactReturn;
		} else { // Deleting last contact in list
			pContactReturn = pContact->pPrev;
			pContactReturn->pNext = NULL;
		}
	}
	free(pContact); // Frees pContact in memory to fully delete
	return (pContactReturn);
}

void PrintContact(Contact *pHead, int targInd) {
	Contact *g = FindNode(pHead, targInd); // Contact pointer at node specified by targInd
	char contactInfo[1024];
	/*
	 * I use sprintf() to create string that has all information to be displayed
	 */
	sprintf(contactInfo, "%s,%s,%s,%s\n", g->lastName, g->firstName, g->email,
			g->phoneNum);
	printf("%s", contactInfo);
}

void PrintContactField(Contact *pHead, int targInd, char *field) {
	Contact *h = FindNode(pHead, targInd);
	/*
	 * If statement stack to handle different possible fields
	 */
	if (strcmp(field, "lastName") == 0) {
		printf("%s\n", h->lastName);
	}
	if (strcmp(field, "firstName") == 0) {
		printf("%s\n", h->firstName);
	}
	if (strcmp(field, "email") == 0) {
		printf("%s\n", h->email);
	}
	if (strcmp(field, "phoneNumber") == 0) {
		printf("%s\n", h->phoneNum);
	}
}

void LoadCSV(Contact **pHead, char *fileName) {
	FILE *pFile;
	pFile = fopen(fileName, "r"); // Opens file specified by fileName
	char *buf = calloc(BUFSIZ, sizeof(char*)); // Buffer to handle input from file
	char *csv = calloc(BUFSIZ, sizeof(char*)); // Buffer to save valid input and use to split up later
	int i = 0; // Counter to save number of fields to create
	if (pFile) {
		while (fscanf(pFile, "%s", buf) != EOF) {
			if (i != 0) {
				strcat(buf, "\n");
				strcat(csv, buf);
			}
			i++;
		}
	}
	char csvInfo[i-1][1024]; // 2D array to save strings (contact info) individually
	char *info = strtok(csv, "\n");
	strcat(info, "\0");
	/*
	 * Loop to take raw string data and parse into separate strings to then apply to InsertContact()
	 */
	if (info != NULL) {
		for (int k = 0; k < i-1; k++) {
			strcpy(csvInfo[k], info);
			info = strtok(NULL, "\n");
			strcat(info, "\0");
		}
	}
	/*
	 * Loop to now create an appropriate number of contacts with the correct information
	 */
	Contact *c = NULL;
	if (csvInfo != NULL) {
		for (int j = 0; j < i-1; j++) {
			c = FindPrevNode((*pHead), j);
			c = InsertContact(pHead, c, csvInfo[j]);
		}
	}
	fclose(pFile);
	free(buf);
	free(csv);
}

void SaveCSV(Contact *pHead, char *fileName) {
	FILE *pFile;
	pFile = fopen(fileName, "w");
	/*
	 * Opens file for writing (overriding file with existing fileName) and prints to file each contact row by row
	 */
	fprintf(pFile, "lastName,firstName,email,phoneNumber\n"); // Header for grade script
	while (pHead) {
		fprintf(pFile, "%s,%s,%s,%s\n", pHead->lastName,
				pHead->firstName, pHead->email, pHead->phoneNum);
		pHead = pHead->pNext;
	}
	fclose(pFile);
}

int NumNodes(Contact *pHead) {
	/*
	 * Simple function to count number of nodes given the head of the list
	 */
	int i = 0;
	while (pHead) {
		i += 1;
		pHead = pHead->pNext;
	}
	return i;
}

void PrintList(Contact *pHead) {
	/*
	 * Helper function to print out all contact fields
	 */
	while (pHead) {
		printf("%s,%s,%s,%s\n", pHead->lastName, pHead->firstName, pHead->email,
				pHead->phoneNum);
		pHead = pHead->pNext;
	}
}

