/*
 ============================================================================
 Name        : hw2b-17.c
 Author      : Lim Kyunghwa
 Version     : beta 1
 Copyright   : YUST
 Description : Airline Reservation with binary search tree
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EMAX 10
#define MYDBFILE "hw2-data.txt"

int num = 0;
int ret = 0;
typedef struct da
{
	char name[32];
	char bd[32];
	char sn[32];
	char mobile[32];
	//char extra[32];
	struct da* left;
	struct da* right;
} DA;

typedef struct queue
{
	DA* front;
	DA* rear;
	int size;
} QUEUE;

int isEmpty(DA* head)
{
	return head->right == NULL;
}

int isEmptyQ(QUEUE* wait)
{
	return wait->size == 0;
}

int isLast(DA* temp)
{
	return temp->right == NULL;
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

	if (strstr(temp->name, str))
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
		temp = temp->right;

	return temp;
}

int dataCopy(DA* t1, DA* t2)
{
	strcpy(t1->name, t2->name);
	strcpy(t1->bd, t2->bd);
	strcpy(t1->sn, t2->sn);
	strcpy(t1->mobile, t2->mobile);

	return 1;
}
/*int customCount(DA* head)
 {
 DA* temp = head->right;
 int count = 0;

 if (isEmpty(head))
 {
 return 0;
 } else
 {
 while (temp)
 {
 count++;
 temp = temp->right;
 }
 }

 return count;
 }*/

int llprint(DA* t)
{

	printf("     Name: %s\n", t->name);
	printf("   Mobile: %s\n", t->mobile);
	printf("       SN: %s\n", t->sn);
	printf("  Birthay: %s\n", t->bd);

	return 0;
}

int print(DA* temp)
{
	if (temp != NULL)
	{
		print(temp->left);
		printf(" name:%s  birthday:%s  sn:%s  mobile:%s\n", temp->name,
				temp->bd, temp->sn, temp->mobile);
		print(temp->right);
	}

	return 1;
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

	sign = strcmp(custom1->name, custom2->name);
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

	printf("Name:");
	gets(str);
	strcpy(buffer->name, str);

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

DA* findtree(char* str, DA* tree)
{

	if (tree == NULL)
		return NULL;
	if (strcmp(str, tree->name) < 0)
		return findtree(str, tree->left);
	else if (strcmp(str, tree->name) > 0)
		return findtree(str, tree->right);
	else
		return tree;
}

DA* findmin(DA* tree)
{
	if (tree == NULL)
		return NULL;
	else if (tree->left == NULL)
		return tree;
	else
		return findmin(tree->left);
}

DA* findmax(DA* tree)
{
	if (tree != NULL)
		while (tree->right != NULL)
			tree = tree->right;
	return tree;
}
/*
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
 if (compareCustom(temp->right, input) > 0)
 break;
 temp = temp->right;
 }
 }
 return temp;
 }*/

/*int insertCustom(DA* head, DA* buffer)
 {
 DA* input = (DA*) malloc(sizeof(DA));
 DA* locate;

 memcpy(input, buffer, sizeof(DA));

 locate = sorting(head, input);

 input->right = locate->right;
 locate->right = input;

 return 1;
 }*/

DA* insert(DA* buffer, DA* tree)
{
	if (tree == NULL)
	{
		tree = (DA*) malloc(sizeof(DA));
		dataCopy(tree, buffer);
		tree->left = NULL;
		tree->right = NULL;
	} else if (compareCustom(buffer, tree) < 0)
		tree->left = insert(buffer, tree->left);
	else if (compareCustom(buffer, tree) > 0)
		tree->right = insert(buffer, tree->right);

	return tree;
}

int insertCustom(DA* head, DA* buffer)
{

	if (!num)
	{
		memcpy(head, buffer, sizeof(DA));
		head->left = NULL;
		head->right = NULL;
	} else
		insert(buffer, head);

	num++;

	return 1;
}

int insertWait(QUEUE* wait, DA* buffer)
{
	DA* input = (DA*) malloc(sizeof(DA));
	memcpy(input, buffer, sizeof(DA));
	if (isEmptyQ(wait))
	{
		wait->front->right = input;
		wait->rear->right = input;
		input->right = NULL;
	} else
	{
		wait->rear->right->right = input;
		wait->rear->right = wait->rear->right->right;
		input->right = NULL;
	}
	wait->size++;
	return 1;
}

DA* dequeue(QUEUE* wait)
{
	DA* temp;
	temp = wait->front->right;
	wait->front->right = temp->right;
	wait->size--;
	return temp;
}

DA* delete(char* str, DA* tree)
{

	DA* temp;
	if (tree == NULL)
		printf("There is no data about you!\n");
	else if (strcmp(str, tree->name) < 0)
	{
		tree->left = delete(str, tree->left);
	} else if (strcmp(str, tree->name) > 0)
	{
		tree->right = delete(str, tree->right);
	} else if (tree->left && tree->right)
	{

		temp = findmin(tree->right);
		dataCopy(tree, temp);
		tree->right = delete(tree->name, tree->right);
	} else
	{
		temp = tree;
		if (tree->left == NULL)
			tree = tree->right;
		else if (tree->right == NULL)
			tree = tree->left;
		free(temp);
	}
	return tree;
}

DA* deleteCustom(DA* head, char* str)
{
	DA* temp;
	char c[32];
	printf("Input your name for delete:");
	gets(str);
	temp = findtree(str, head);
	if (temp)
	{
		printf("Your information:\n");
		llprint(temp);
	} else
		return NULL;
	printf("Are you sure delete it?(y/n):");
	if (getch(c) == 'y')
	{
		head = delete(str, head);
		num--;
	} else
	{
		printf("Delete data was stopped!\n");
		return head;
	}

	/*	printf("Input index of custom for delete:");
	 index = getint(str);

	 if (index > num || index == 0)
	 {
	 printf("Error input!!\n");
	 } else
	 {
	 temp = find(head, index);
	 printf("Your information:\n");
	 llprint(temp->right);
	 printf("[%2d] name:%s %s  bd:%s  sn:%s  mobile:%s\n", index,
	 temp->right->fname, temp->right->lname,
	 temp->right->bd, temp->right->sn, temp->right->mobile);
	 printf("Are you sure delete it?(y/n):");
	 if (getch(str) == 'y')
	 {
	 printf("Delete success!\n");
	 p = temp->right;
	 temp->right = p->right;
	 free(p);
	 } else
	 {
	 printf("Delete data was stopped!\n");
	 }*/

	return head;
}

DA* fixtree(DA* head, DA* buffer, char* str)
{
	DA* temp = (DA*) malloc(sizeof(DA));
	DA* temp1;
	int end = 0;

	if (num == 0)
	{
		printf("There is no data!\n");
		return 0;
	}
	printf("Input name of custom for modify:");
	gets(str);

	/*if (index > num || index == 0)
	 {
	 printf("Error input!!\n");
	 return 0;
	 }*/

	temp1 = findtree(str, head);

	if (temp1 == NULL)
	{
		printf("There is no data about you!\n");
		return 0;
	}
	dataCopy(temp, temp1);
	head = delete(str, head);
	while (!end)
	{
		printf("Name[%s]:", temp->name);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->name, str);

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

	insertCustom(head, buffer);
	free(temp);

	return head;
}

int fixWait(QUEUE* wait, DA* buffer, char* str)
{
	DA* temp = (DA*) malloc(sizeof(DA));
	DA* temp1;
	int end = 0;
	int index;

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
	temp1 = find(wait->front, index);

	memcpy(temp, temp1->right, sizeof(DA));

	while (!end)
	{
		printf("Name[%s]:", temp->name);
		gets(str);
		if (str[0] != 0)
			strcpy(temp->name, str);

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
			memcpy(temp1->right, temp, sizeof(DA));
			end = 1;
		}
	}
	return 1;
}

DA* modify(DA* head, QUEUE* wait, DA* buffer, char* str)
{
	char c;
	printf("Input modify list(r-reserved/w-waiting):");
	c = getch(str);
	switch (c)
	{
	case 'r':
		return fixtree(head, buffer, str);
		break;
	case 'w':
		fixWait(wait, buffer, str);
		break;
	default:
		printf("Error input!\n");
		break;
	}
	return head;
}
int searchtree(DA* head, char* str)
{
	DA* temp;
	printf("Input data for searching:");
	gets(str);

	temp = findtree(str, head);
	if (temp)
	{
		printf("===================\n");
		printf("|  Reserved List  |\n");
		printf("===================\n");
		llprint(temp);
	}
	/*while (temp)
	 {
	 if (haveFound(temp, str))
	 {
	 if (count == 0)
	 {
	 printf("===================\n");
	 printf("|  Reserved List  |\n");
	 printf("===================\n");
	 }
	 printf("[%2d] name:%s   birthday:%s  sn:%s  mobile:%s\n", index,
	 temp->name, temp->bd, temp->sn, temp->mobile);
	 count++;
	 }
	 temp = temp->right;
	 index++;
	 }*/

	return 1;
}

int searchwait(QUEUE* wait, char* str)
{
	DA* temp;
	int i = 0;
	int count = 0;
	if (!isEmptyQ(wait))
	{

		for (temp = wait->front->right; temp != 0; temp = temp->right)
		{
			if (haveFound(temp, str))
			{
				count++;
				if (count != 0)
				{
					printf("===================\n");
					printf("|   Waiting List  |\n");
					printf("===================\n");
				}
				printf("[%2d] name:%s  birthday:%s  sn:%s  mobile:%s\n", i + 1,
						temp->name, temp->bd, temp->sn, temp->mobile);

			}
			i++;
		}
	}
	return 1;
}
int printtree(DA* head)
{

	if (num == 0)
		return 0;
	printf("===================\n");
	printf("|  Reserved List  |\n");
	printf("===================\n");
	print(head);

	return (1);
}

int printwait(QUEUE* wait)
{
	DA* temp;
	int i;

	if (!isEmptyQ(wait))
	{

		printf("===================\n");
		printf("|   Waiting List  |\n");
		printf("===================\n");
		for (temp = wait->front->right, i = 0; temp != 0; temp = temp->right, i++)
		{
			printf("[%2d] name:%s  birthday:%s  sn:%s  mobile:%s\n", i + 1,
					temp->name, temp->bd, temp->sn, temp->mobile);
		}
	}
	return 1;
}
int airlineservice(DA* head, QUEUE* wait)
{
	int quit = 0;
	char choise;
	DA* buffer = (DA*) malloc(sizeof(DA));
	DA* temp;
	char str[32];

	printf("Welcome to my simple airline reservation !!!!\n\n");

	while (!quit)
	{

		choise = getChoise(str); /*  include menu  */
		switch (choise)
		{
		case 'r':
			if(!num)
				head = (DA*)malloc(sizeof(DA));
			writeData(buffer, str);
			if (num < EMAX)
				insertCustom(head, buffer);
			else
				insertWait(wait, buffer);
			break;
		case 'c':
			if (num == 0)
			{
				printf("There is no data!\n");
				break;
			}
			head = deleteCustom(head, str);

			if (!isEmptyQ(wait))
			{
				temp = dequeue(wait);
				memcpy(buffer, temp, sizeof(DA));
				free(temp);
				insertCustom(head, buffer);
			}
			break;
		case 'm':
			head = modify(head, wait, buffer, str);
			break;
		case 'l':
			printtree(head);
			printwait(wait);
			break;
		case 's':
			searchtree(head, str);
			searchwait(wait, str);
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
	wait->front = (DA*) malloc(sizeof(DA));
	wait->rear = (DA*) malloc(sizeof(DA));
	wait->size = 0;

	head->left = NULL;
	head->right = NULL;

	if (fp = fopen(MYDBFILE, "r"))
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s", one.name);
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

int savefile(DA* temp, FILE *fp)
{
	if (temp != NULL)
	{
		ret++;
		fprintf(fp, "%s\n", temp->name);
		fprintf(fp, "%s\n", temp->bd);
		fprintf(fp, "%s\n", temp->sn);
		fprintf(fp, "%s\n", temp->mobile);
		savefile(temp->left, fp);
		savefile(temp->right, fp);

	}
	return 1;
}

int lldbfout(DA* head, QUEUE* wait)
{
	FILE *fp, *fopen();
	DA* temp;

	if (fp = fopen(MYDBFILE, "w"))
	{
		//		fclose(fp);
		savefile(head, fp);
		if (!isEmptyQ(wait))
		{
			fp = fopen(MYDBFILE, "a");
			temp = wait->front;
			for (temp = wait->front->right; temp != 0; temp = temp->right)
			{
				fprintf(fp, "%s\n", temp->name);
				fprintf(fp, "%s\n", temp->bd);
				fprintf(fp, "%s\n", temp->sn);
				fprintf(fp, "%s\n", temp->mobile);

				ret++;
			}
			fclose(fp);
		}
		//	fprintf(fp, "\n");

		printf("Info> %d records recorded\n", ret);
	} else
	{
		printf("Error> File(%s) Writing Error\n", MYDBFILE);
	}
	return (ret);
}

/*
 int lldbfout(DA* head, QUEUE* wait)
 {
 FILE *fp, *fopen();
 DA* temp;
 int ret = 0;

 if (fp = fopen(MYDBFILE, "w"))
 {
 for (temp = head->right; temp != 0; temp = temp->right)
 {
 fprintf(fp, "%s\n", temp->name);
 fprintf(fp, "%s\n", temp->bd);
 fprintf(fp, "%s\n", temp->sn);
 fprintf(fp, "%s\n", temp->mobile);
 //fprintf(fp, "%s\n", temp->extra);

 ret++;
 }

 if (!isEmptyQ(wait))
 {
 temp = wait->front;
 for (temp = wait->front->right; temp != 0; temp = temp->right)
 {
 fprintf(fp, "%s\n", temp->name);
 fprintf(fp, "%s\n", temp->bd);
 fprintf(fp, "%s\n", temp->sn);
 fprintf(fp, "%s\n", temp->mobile);

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
