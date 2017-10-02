/*
 ============================================================================
 Name        : hw2p-17.c
 Author      : Lim Kyunghwa
 Version     : Release 2 update 2
 Copyright   : YUST
 Description : Airline Reservation
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct da
{
	char firstName[32];
	char lastName[32];
	char birthday[32];
	char id[32];
	char phone[32];
	struct da* next;
} DA;

int isEmpty(DA* head)
{
	return head->next == NULL;
}

int isLast(DA* temp)
{
	return temp->next == NULL;
}

char getch(char* str)
{
	char c;

	gets(str);

	c = tolower(str[0]);

	return c;
}

int getint(char* str)
{
	int i;

	gets(str);

	i = atol(str);

	return i;
}

int haveFound(DA* temp, char* str)
{

	int sign;

	if (strcmp(str, temp->firstName) == 0)
	{
		sign = 1;
	} else if (strcmp(str, temp->lastName) == 0)
	{
		sign = 1;
	} else if (strcmp(str, temp->birthday) == 0)
	{
		sign = 1;
	} else if (strcmp(str, temp->id) == 0)
	{
		sign = 1;
	} else if (strcmp(str, temp->phone) == 0)
	{
		sign = 1;
	} else
		sign = 0;

	return sign;
}

DA* find(DA* head, int index)
{
	DA* temp = head;

	int i;

	for (i = 1; i < index; i++)
		temp = temp->next;

	return temp;
}

int customCount(DA* head)
{
	DA* temp = head->next;
	int count = 0;

	if (isEmpty(head))
	{
		return 0;
	} else
	{
		while (temp)
		{
			count++;
			temp = temp->next;
		}
	}

	return count;
}

char getChoise(char* str)
{
	printf("Make a [R]eservation\n");
	printf("[C]ancel a reservation\n");
	printf("[M]odify a customer's information\n");
	printf("[L]ist reservations\n");
	printf("[S]earch reservations\n");
	printf("[Q]uit\n");
	printf("Insert Menu?\n");
	printf(">");

	return getch(str);
}

int compareCustom(DA* custom1, DA* custom2)
{
	int sign;

	sign = strcmp(custom1->lastName, custom2->lastName);
	if (sign == 0)
	{
		sign = strcmp(custom1->firstName, custom2->firstName);
	}
	if (sign == 0)
	{
		sign = strcmp(custom1->birthday, custom2->birthday);
	}
	if (sign == 0)
	{
		sign = strcmp(custom1->id, custom2->id);
	}
	if (sign == 0)
	{
		sign = strcmp(custom1->phone, custom2->phone);
	}

	return sign;
}

int writeData(DA* buffer, char* str)
{

	printf("Last Name:");
	gets(str);
	strcpy(buffer->lastName, str);

	printf("First Name:");
	gets(str);
	strcpy(buffer->firstName, str);

	printf("Birthday(YYYYMMDD):");
	gets(str);
	strcpy(buffer->birthday, str);

	printf("ID#:");
	gets(str);
	strcpy(buffer->id, str);

	printf("Telephone#:");
	gets(str);
	strcpy(buffer->phone, str);

	return (1);
}

DA* sorting(DA* head, DA* input)
{
	DA* temp = head;

	if (isEmpty(head))
	{
		return head;
	} else
	{
		while (temp)
		{
			if (isLast(temp))
				break;
			if (compareCustom(temp->next, input) > 0)
				break;
			temp = temp->next;
		}
	}
	return temp;
}

int insertCustom(DA* head, DA* buffer)
{
	DA* input = (DA*) malloc(sizeof(DA));
	DA* locate;

	memcpy(input, buffer, sizeof(DA));

	locate = sorting(head, input);

	input->next = locate->next;
	locate->next = input;

	return 1;
}

int deleteCustom(DA* head, char* str)
{
	DA* temp;
	DA* p;
	int index;

	printf("Input index of custom for delete:");
	index = getint(str);

	if (index > customCount(head) || index == 0)
	{
		printf("Error input!!\n");
	} else
	{
		temp = find(head, index);
		printf("Your information:\n");
		printf("[%2d] name:%s %s  birthday:%s  id:%s  phone:%s\n", index,
				temp->next->firstName, temp->next->lastName,
				temp->next->birthday, temp->next->id, temp->next->phone);
		printf("Are you sure delete it?(y/n):");
		if (getch(str) == 'y')
		{
			printf("Delete success!\n");
			p = temp->next;
			temp->next = p->next;
			free(p);
		} else
		{
			printf("Delete data was stopped!\n");
		}
	}

	return 1;
}

int modify(DA* head, DA* buffer, char* str)
{
	DA* temp = (DA*) malloc(sizeof(DA));
	DA* p;
	DA* temp1;
	int end = 0;
	int index;

	if (customCount(head) == 0)
	{
		printf("There is no data!\n");
		return 0;
	}
	printf("Input index of custom for modify:");
	index = getint(str);

	if (index > customCount(head) || index == 0)
	{
		printf("Error input!!\n");
		return 0;
	}

	temp1 = find(head, index);

	memcpy(temp, temp1->next, sizeof(DA));

	while (!end)
	{
		printf("Last Name[%s]:", temp->lastName);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->lastName, str);

		printf("First Name[%s]:", temp->firstName);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->firstName, str);

		printf("Birthday[%s]:", temp->birthday);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->birthday, str);

		printf("ID#[%s]:", temp->id);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->id, str);

		printf("Telephone#[%s]:", temp->phone);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->phone, str);
		printf("Your information:\n");
		printf("[fixed] name:%s %s  birthday:%s  id:%s  phone:%s\n",
				temp->firstName, temp->lastName, temp->birthday, temp->id,
				temp->phone);
		printf("Are you sure?(y/n):");
		if (getch(str) == 'y')
		{
			memcpy(buffer, temp, sizeof(DA));
			end = 1;
		}
	}

	p = temp1->next;
	temp1->next = p->next;
	free(p);

	insertCustom(head, buffer);
	free(temp);

	return 1;
}

int searchCustom(DA* head, char* str)
{

	DA* temp = head ->next;
	int index = 1;
	int count = 0;
	printf("Input data for searching:");
	gets(str);

	while (temp)
	{
		if (haveFound(temp, str))
		{
			printf("[%2d] name:%s %s  birthday:%s  id:%s  phone:%s\n", index,
					temp->firstName, temp->lastName, temp->birthday, temp->id,
					temp->phone);
			count++;
		}
		temp = temp->next;
		index++;
	}

	if (!count)
	{
		printf("There is no data about you\n");
	}

	return 1;
}

int printList(DA* head)
{
	DA* temp = head->next;
	int index = 1;
	while (temp)
	{
		printf("[%2d] name:%s %s  birthday:%s  id:%s  phone:%s\n", index++,
				temp->firstName, temp->lastName, temp->birthday, temp->id,
				temp->phone);
		temp = temp->next;
	}

	return (1);
}
int airlineservice(DA* head)
{
	int quit = 0;
	char choise;
	DA* buffer = (DA*) malloc(sizeof(DA));
	char str[32];

	printf("Welcome to my simple airline reservation !!!!\n\n");

	while (!quit)
	{

		choise = getChoise(str); /*  include menu  */
		switch (choise)
		{
		case 'r':
			writeData(buffer, str);
			insertCustom(head, buffer);
			break;
		case 'c':
			if (customCount(head) == 0)
			{
				printf("There is no data!\n");
				break;
			}
			deleteCustom(head, str);
			break;
		case 'm':
			modify(head, buffer, str);
			break;
		case 'l':
			printList(head);
			break;
		case 's':
			searchCustom(head, str);
			break;
		case 'q':
			quit = 1;
			break;
		default:
			printf("Error input!!\n");
			break;
		}
	}

	free(buffer);
	return (1);
}

int listMakeEmpty(DA* head)
{
	head ->next = NULL;

	return (1);
}

int main(void)
{
	DA* head = (DA*) malloc(sizeof(DA));

	listMakeEmpty(head);

	airlineservice(head);

	free(head);

	return EXIT_SUCCESS;
}
/*
 int insertCustom(DA* head, DA* new)
 {
 DA* temp;

 temp = head;

 if (temp == NULL)
 {
 new->next = NULL;
 head = new;

 } else if (temp->next == NULL)
 {
 if (strcmp(temp->firstName, new->firstName) > 0)
 {
 head = new;
 new->next = temp;
 } else
 {
 new->next = NULL;
 temp->next = new;
 }
 } else
 {
 while (temp != NULL)
 {
 if (temp->next == NULL)
 {
 new->next = NULL;
 temp->next = new;
 } else if (strcmp(temp->next->firstName, new->firstName) > 0)
 {

 new->next = temp->next;
 temp->next = new;
 } else
 {
 temp = temp->next;
 }
 }
 }
 return (1);
 }

 int writeData(DA* head)
 {
 char str[32];

 DA* new = (DA*) malloc(sizeof(DA));
 printf("Last Name:");
 gets(str);
 strcpy(new->lastName, str);

 printf("First Name:");
 gets(str);
 strcpy(new->firstName, str);

 printf("Birthday(YYYYMMDD):");
 gets(str);
 strcpy(new->birthday, str);

 printf("ID#:");
 gets(str);
 strcpy(new->id, str);

 printf("Telephone#:");
 gets(str);
 strcpy(new->phone, str);

 insertCustom(head, new);

 return (1);
 }

 int deleteCustom(DA* head, int index)
 {
 DA* temp = head;
 int i;
 char str[32];

 if (temp->next == NULL)
 {
 head = NULL;
 free(temp);
 } else
 {
 if (index == 1)
 {
 head = temp->next;
 free(temp);
 } else
 {
 for (i = 0; i < delete ; i++)
 temp++;
 if (temp->next->next == NULL)
 {
 temp->next = NULL;
 } else
 {
 temp->next = temp->next->next;
 }
 }
 }

 return (1);
 }

 int modifyCustom(DA* head)
 {
 DA* buff = (DA*) malloc(sizeof(DA));
 DA* temp = head;
 int i;
 int index;
 char str[32];
 printf("Input index:");
 gets(str);

 index = atol(str) - 1;
 for (i = 1; i < index; i++)
 {
 temp = temp->next;
 }

 memcpy(buff, temp, sizeof(DA));
 deleteCustom(head,index);
 writeNewData(head, buff);

 return (1);
 }
 int printList(DA* head)
 {
 int index = 1;
 DA* temp = head;

 while (temp != NULL)
 {
 printf("[%2d] name:%s %s  birthday:%s  id:%s  phone:%s\n", index,
 temp->firstName, temp->lastName, temp->birthday, temp->id,
 temp->phone);
 index++;
 temp = temp->next;
 }

 return (1);
 }
 int searchCustom(DA* head)
 {
 char str[32];
 int index = 1;
 DA* temp = head;

 if (temp == NULL)
 {
 printf("There is no data!\n");
 return 0;
 }

 printf("Input information for searching~\n");
 printf(">");
 gets(str);

 while (temp != NULL)
 {
 if (strcmp(str, temp->firstName) == 0)
 break;
 else if (strcmp(str, temp->lastName) == 0)
 break;
 else if (strcmp(str, temp->birthday) == 0)
 break;
 else if (strcmp(str, temp->id) == 0)
 break;
 else if (strcmp(str, temp->phone) == 0)
 break;
 else
 index++;
 temp = temp->next;
 }

 if (temp == NULL)
 {
 printf("There is no data about you\n");
 return 0;
 }

 printf("[%2d] name:%s %s  birthday:%s  id:%s  phone:%s\n", index,
 temp->firstName, temp->lastName, temp->birthday, temp->id,
 temp->phone);

 return (1);
 }

 DA* find(char c, DA* head)
 {
 DA* temp = head->next;
 int index = 0;

 while (temp != NULL && temp->data != c)
 {
 temp->index = index++;
 temp = temp->next;
 }

 return temp;
 }

 DA* findPre(char c, DA* head)
 {
 DA* temp = head;

 while (temp->next != 0 && temp->next->data != c)
 {
 temp = temp->next;
 }

 return temp;
 }


 int insert(DA* head, DA* buffer)
 {
 DA* temp = head->next;
 DA* input = (DA*) malloc(sizeof(DA));

 input ->data = buffer->data;
 //printf("%c11\n",input->data);
 //printf("%d\n",isEmpty(head));
 if (isEmpty(head))
 {
 head->next = input;
 input->next = NULL;
 //printf("%c11\n",input->data);

 } else if (isLast(temp))
 {
 if (head->next->data > input->data)
 {
 input->next = head->next;
 head->next = input;
 } else
 {
 head->next->next = input;
 }
 } else
 {
 while (temp != NULL)
 {
 if (isLast(temp))
 {
 temp ->next = input;
 input->next = NULL;
 break;
 } else if (temp->data > input->data)
 {
 input->next = head->next;
 head->next = input;
 break;

 } else if (temp->next->data > input->data)

 {
 input->next = temp ->next;
 temp->next = input;
 break;
 } else
 {
 temp = temp->next;
 }
 }
 }
 //printf("%d\n",isEmpty(head));
 return (1);
 }
 */
/*
 int insertCustom(DA* head, DA* buffer)
 {
 DA* temp = head;

 if (isEmpty(head))
 {
 head->next = input;
 input->next = NULL;

 } else if (isLast(temp))
 {
 if (compareCustom(head->next, input))
 {
 input->next = head->next;
 head->next = input;
 } else
 {
 head->next->next = input;
 input->next = NULL;
 }
 } else
 {
 while (temp != NULL)
 {
 if (isLast(temp))
 {
 temp ->next = input;
 input->next = NULL;
 break;
 } else if (compareCustom(temp, input))
 {
 input->next = head->next;
 head->next = input;
 break;
 } else if (compareCustom(temp->next, input))
 {
 input->next = temp ->next;
 temp->next = input;
 break;
 } else
 {
 temp = temp->next;
 }
 }
 }

 return (1);
 }
 */
