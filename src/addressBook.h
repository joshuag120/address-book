/*
 * addressBook.h
 *
 *  Created on: Nov 24, 2021
 *      Author: jgianelli
 */

#ifndef ADDRESSBOOK_H_
#define ADDRESSBOOK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contact Contact;
typedef struct contact *pContact;
struct contact {
	char firstName[256];
	char lastName[256];
	char phoneNum[12];
	char email[256];
	Contact *pPrev;
	Contact *pNext;
};

Contact* FindPrevNode(Contact *pHead, int targInd);

Contact* FindNode(Contact *pContact, int targInd);

Contact* CreateContact(char *info);

Contact* InsertContact(pContact *ppFirst, Contact *pPrev, char *info);

Contact* DeleteContact(pContact *ppFirst, Contact *pContact);

void PrintContact(Contact *pHead, int targInd);

void PrintContactField(Contact *pHead, int targInd, char *field);

int NumNodes(Contact *pHead);

void LoadCSV(Contact **pHead, char *fileName);

void SaveCSV(Contact *pHead, char *fileName);

void PrintList(Contact *pHead);

#endif /* ADDRESSBOOK_H_ */
