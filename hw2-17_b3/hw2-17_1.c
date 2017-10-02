/*
 ============================================================================
 Name        : hw2-17.c
 Author      : Lim Kyunghwa
 Version     : beta 2  update 1
 Copyright   : YUST
 Description : Airline Reservation
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EMAX 10
#define WAIT 10
#define MYDBFILE "hw2-data.txt"

typedef struct da
{
	char fname[32];
	char lname[32];
	char bd[32];
	char sn[32];
	char mobile[32];
	//char extra[32];
	struct da* next;
} DA;

typedef struct queue
{
	DA waiting[WAIT];
	int front;
	int rear;
	int size;
} QUEUE;

int isEmpty(DA* head)
{
	return head->next == NULL;
}

int isEmptyQ(QUEUE* wait)
{
	return wait->size == 0;
}

int isLast(DA* temp)
{
	return temp->next == NULL;
}

int isFullQ(QUEUE* wait)
{
	return wait->size == WAIT;
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

	if (strstr(temp->fname, str))
	{
		sign = 1;
	} else if (strstr(temp->lname, str))
	{
		sign = 1;
	} else if (strstr(temp->bd, str))
	{
		sign = 1;
	} else if (strstr(temp->sn, str))
	{
		sign = 1;
	} else if (strstr(temp->mobile, str))
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

int llprint(DA* t)
{

	printf("     Name: %s, %s\n", t->lname, t->fname);
	printf("   Mobile: %s\n", t->mobile);
	printf("       SN: %s\n", t->sn);
	printf("  Birthay: %s\n", t->bd);

	return 0;
}

char getChoise(char* str)
{
	printf("\n");
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

	sign = strcmp(custom1->lname, custom2->lname);
	if (sign == 0)
	{
		sign = strcmp(custom1->fname, custom2->fname);
	}
	if (sign == 0)
	{
		sign = strcmp(custom1->bd, custom2->bd);
	}
	if (sign == 0)
	{
		sign = strcmp(custom1->sn, custom2->sn);
	}
	if (sign == 0)
	{
		sign = strcmp(custom1->mobile, custom2->mobile);
	}

	return sign;
}

int writeData(DA* buffer, char* str)
{

	printf("Last Name:");
	gets(str);
	strcpy(buffer->lname, str);

	printf("First Name:");
	gets(str);
	strcpy(buffer->fname, str);

	printf("birthday(YYYYMMDD):");
	gets(str);
	strcpy(buffer->bd, str);

	printf("sn#:");
	gets(str);
	strcpy(buffer->sn, str);

	printf("mobile#:");
	gets(str);
	strcpy(buffer->mobile, str);

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

int insertWait(QUEUE* wait, DA* buffer)
{
	memcpy(&wait->waiting[(wait->rear + 1) % WAIT], buffer, sizeof(DA));
	wait->size++;
	wait->rear = (wait->rear + 1) % WAIT;

	return 1;
}

DA* dequeue(QUEUE* wait)
{
	DA* temp;

	temp = &wait->waiting[wait->front];
	wait->front = (wait->front + 1) % WAIT;
	wait->size--;

	return temp;
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
		llprint(temp->next);
		/*	printf("[%2d] name:%s %s  bd:%s  sn:%s  mobile:%s\n", index,
		 temp->next->fname, temp->next->lname,
		 temp->next->bd, temp->next->sn, temp->next->mobile);
		 */
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
		printf("Last Name[%s]:", temp->lname);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->lname, str);

		printf("First Name[%s]:", temp->fname);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->fname, str);

		printf("birthday[%s]:", temp->bd);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->bd, str);

		printf("sn#[%s]:", temp->sn);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->sn, str);

		printf("mobile#[%s]:", temp->mobile);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->mobile, str);
		printf("Your information:\n");
		llprint(temp);
		/*
		 printf("[fixed] name:%s %s  bd:%s  sn:%s  mobile:%s\n", temp->fname,
		 temp->lname, temp->bd, temp->sn, temp->mobile);
		 */
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

int fixWait(QUEUE* wait, DA* buffer, char* str)
{
	DA* temp = (DA*) malloc(sizeof(DA));
	int end = 0;
	int index;
	int p;

	if (isEmptyQ(wait))
	{
		printf("There is no data!\n");
		return 0;
	}

	printf("Input index of custom for modify:");
	index = getint(str);

	if (index > wait->size || index == 0)
	{
		printf("Error input!\n");
		return 0;
	}
	p = (wait->front + index - 1) % WAIT;
	memcpy(temp, &wait->waiting[p], sizeof(DA));

	while (!end)
	{
		printf("Last Name[%s]:", temp->lname);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->lname, str);

		printf("First Name[%s]:", temp->fname);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->fname, str);

		printf("birthday[%s]:", temp->bd);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->bd, str);

		printf("sn#[%s]:", temp->sn);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->sn, str);

		printf("mobile#[%s]:", temp->mobile);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->mobile, str);
		printf("Your information:\n");
		llprint(temp);
		/*
		 printf("[fixed] name:%s %s  bd:%s  sn:%s  mobile:%s\n", temp->fname,
		 temp->lname, temp->bd, temp->sn, temp->mobile);
		 */
		printf("Are you sure?(y/n):");
		if (getch(str) == 'y')
		{
			memcpy(&wait->waiting[p], temp, sizeof(DA));
			end = 1;
		}
	}
	return 1;
}

int fixList(DA* head, QUEUE* wait, DA* buffer, char* str)
{
	char c;
	printf("Input modify list(r-reserved/w-waiting):");
	c = getch(str);
	switch (c)
	{
	case 'r':
		modify(head, buffer, str);
		break;
	case 'w':
		fixWait(wait, buffer, str);
		break;
	default:
		printf("Error input!\n");
		break;
	}
	return 1;
}
int searchCustom(DA* head, QUEUE* wait, char* str)
{

	DA* temp = head ->next;
	int index = 1;
	int count = 0;
	int point;
	int i;

	printf("Input data for searching:");
	gets(str);
	printf("===================\n");
	printf("|  Reserved List  |\n");
	printf("===================\n");

	while (temp)
	{
		if (haveFound(temp, str))
		{
			printf("[%2d] name:%s %s  birthday:%s  sn:%s  mobile:%s\n", index,
					temp->lname, temp->fname, temp->bd, temp->sn, temp->mobile);
			count++;
		}
		temp = temp->next;
		index++;
	}

	if (!isEmptyQ(wait))
	{
		printf("===================\n");
		printf("|   Waiting List  |\n");
		printf("===================\n");
		point = wait->front;
		for (i = 0; i < wait->size; i++, point++)
		{
			point %= WAIT;
			if (haveFound(&wait->waiting[point], str))
			{

				printf("[%2d] name:%s %s  birthday:%s  sn:%s  mobile:%s\n", i
						+ 1, wait->waiting[point].lname,
						wait->waiting[point].fname, wait->waiting[point].bd,
						wait->waiting[point].sn, wait->waiting[point].mobile);
			}
		}
	}

	if (!count)
	{
		printf("There is no data about you\n");
	}

	return 1;
}

int printList(DA* head, QUEUE* wait)
{
	DA* temp = head->next;
	int index = 1;
	int point;
	int i;

	if (customCount(head) == 0)
		return 0;

	printf("===================\n");
	printf("|  Reserved List  |\n");
	printf("===================\n");
	while (temp)
	{
		printf("[%2d] name:%s %s  birthday:%s  sn:%s  mobile:%s\n", index++,
				temp->lname, temp->fname, temp->bd, temp->sn, temp->mobile);
		temp = temp->next;
	}

	if (!isEmptyQ(wait))
	{

		printf("===================\n");
		printf("|   Waiting List  |\n");
		printf("===================\n");
		for (i = 0, point = wait->front; i < wait->size; i++, point++)
		{
			point %= WAIT;
			printf("[%2d] name:%s %s  birthday:%s  sn:%s  mobile:%s\n", i + 1,
					wait->waiting[point].lname, wait->waiting[point].fname,
					wait->waiting[point].bd, wait->waiting[point].sn,
					wait->waiting[point].mobile);
		}
	}

	return (1);
}

int airlineservice(DA* head, QUEUE* wait)
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
			if (customCount(head) < EMAX)
				insertCustom(head, buffer);
			else if (!isFullQ(wait))
				insertWait(wait, buffer);
			else
				printf("The waiting list is full!\n");
			break;
		case 'c':
			if (customCount(head) == 0)
			{
				printf("There is no data!\n");
				break;
			}
			deleteCustom(head, str);
			if (!isEmptyQ(wait))
			{
				memcpy(buffer, dequeue(wait), sizeof(DA));
				insertCustom(head, buffer);
			}
			break;
		case 'm':
			fixList(head, wait, buffer, str);

			break;
		case 'l':
			printList(head, wait);
			break;
		case 's':
			searchCustom(head, wait, str);
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

int llinsert(DA* one, DA* head)
{
	DA* buffer = (DA*) malloc(sizeof(DA));
	memcpy(buffer, one, sizeof(DA));

	buffer->next == NULL;

	insertCustom(head, buffer);

	free(buffer);

	return 1;
}

int waitinsert(DA* one, QUEUE* wait)
{
	DA* buffer = (DA*) malloc(sizeof(DA));
	memcpy(buffer, one, sizeof(DA));

	insertWait(wait, buffer);

	free(buffer);

	return 1;
}

int lldbfin(DA* head, QUEUE* wait)
{
	FILE *fp, *fopen();
	DA one;
	int ret = 0;

	wait->front = 0;
	wait->rear = -1;
	wait->size = 0;

	if (fp = fopen(MYDBFILE, "r"))
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s", one.lname);
			if (feof(fp))
				break;

			fscanf(fp, "%s", one.fname);
			if (feof(fp))
				break;

			fscanf(fp, "%s", one.bd);
			if (feof(fp))
				break;

			fscanf(fp, "%s", one.sn);
			if (feof(fp))
				break;

			fscanf(fp, "%s", one.mobile);
			if (feof(fp))
				break;

			if (ret < EMAX)
				llinsert(&one, head);
			else
				waitinsert(&one, wait);
			ret++;
		}

		printf("Info> %d records inserted\n", ret);
		fclose(fp);

	} else
	{
		printf("Info> File(%s) Not Found\n", MYDBFILE);
	}

	return (ret);
}

int lldbfout(DA* head, QUEUE* wait)
{
	FILE *fp, *fopen();
	DA* temp;
	int ret = 0;
	int i;
	int x;

	if (fp = fopen(MYDBFILE, "w"))
	{
		for (temp = head->next; temp != 0; temp = temp->next)
		{
			fprintf(fp, "%s\n", temp->lname);
			fprintf(fp, "%s\n", temp->fname);
			fprintf(fp, "%s\n", temp->bd);
			fprintf(fp, "%s\n", temp->sn);
			fprintf(fp, "%s\n", temp->mobile);
			//fprintf(fp, "%s\n", temp->extra);

			ret++;
		}

		if (!isEmptyQ(wait))
		{
			x = wait->front;
			for (i = 0; i < wait->size; i++, x++)
			{
				x %= WAIT;
				fprintf(fp, "%s\n", wait->waiting[x].lname);
				fprintf(fp, "%s\n", wait->waiting[x].fname);
				fprintf(fp, "%s\n", wait->waiting[x].bd);
				fprintf(fp, "%s\n", wait->waiting[x].sn);
				fprintf(fp, "%s\n", wait->waiting[x].mobile);

				ret++;
			}
		}
		//	fprintf(fp, "\n");
		fclose(fp);
		printf("Info> %d records recorded\n", ret);
	} else
	{
		printf("Error> File(%s) Writing Error\n", MYDBFILE);
	}
	free(temp);
	return (ret);
}
/*
 int makelist(DA* head, QUEUE* wait, DA* temp, int count)
 {
 int i = 0;
 head->next = &temp[i];
 for (i = 0; i < count % 10 - 1; i++)
 {
 temp[i].next = &temp[i + 1];
 }
 temp[i].next = NULL;

 if (count > 10)
 {
 for (i = 0; i < count - 10; i++)
 {
 memcpy(&wait->waiting[i], &temp[i + 10], sizeof(DA));
 }

 wait->size = i;
 wait->front = 0;
 wait->rear = i - 1;
 } else
 {
 wait->size = 0;
 wait->front = 0;
 wait->rear = -1;
 }

 return 1;
 }
 */
int main( vosn)
{
	DA* head = (DA*) malloc(sizeof(DA));
	QUEUE* wait = (QUEUE*) malloc(sizeof(QUEUE));

	lldbfin(head, wait);

	airlineservice(head, wait);

	lldbfout(head, wait);

	return EXIT_SUCCESS;
}
