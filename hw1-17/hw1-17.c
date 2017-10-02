/*
 * hw1-17.c
 *
 *  Created on: 20 Sep 2009
 *      Author: lin
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct people
{
	char name[32];
	int interest;
	char interests[10][32];
	int variable;
	int partner;
};
struct people man[50];
struct people woman[50];
char buffer[100000];
int man_over, woman_over;
int man_num = 0;
int woman_num = 0;
char buf[15][32];
int man_n;
int woman_n;
int partner = 0;
int main(void)
{
	void ne(void);
	void ma(void);
	void un(void);
	void pr(void);

	int turn = 1;
	char *p;
	int sign;

	printf("MENU\n");
	printf(
			"ne(wclient) : adding a new client with information of sex, name, # of interest, interests.....\n");
	printf("ma(tch) : try to match couples as FCFS\n");
	printf("un(match) : unmatch the particular client\n");
	printf("pr(int) : print list with matched and unmatched seperately\n");
	printf("qu(it) : quit the program\n\n");
	while (turn)
	{
		int x = 0;
		printf("comment = ");
		gets(buffer);
		for (p = strtok(buffer, " \t\r\n"); p; p = strtok(NULL, " \t\r\n"))
		{
			strcpy(buf[x], p);
			x++;
		}
		if (strcmp(buf[0], "ne") == 0)
			sign = 1;
		else if (strcmp(buf[0], "ma") == 0)
			sign = 2;
		else if (strcmp(buf[0], "un") == 0)
			sign = 3;
		else if (strcmp(buf[0], "pr") == 0)
			sign = 4;
		else if (strcmp(buf[0], "qu") == 0)
			sign = 5;
		else
			printf("Error input! No %s menu!\n", buf[0]);
		switch (sign)
		{
		case 1:
			ne();
			break;
		case 2:
			ma();
			break;
		case 3:
			un();
			break;
		case 4:
			pr();
			break;
		case 5:
			printf("Thank you for use this program!\n");
			turn = 0;
			break;
		default:
			printf("Error input! Please input again!\n");
			break;
		}
	}
	return 0;
}

void ne()
{
	int i;
	if (strcmp(buf[1], "m") == 0)
	{
		strcpy(man[man_num].name, buf[2]);
		man[man_num].interest = atoi(buf[3]);
		man[man_num].variable = -1;
		for (i = 0; i < man[man_num].interest; i++)
			strcpy(man[man_num].interests[i], buf[i + 4]);
		man_num++;
	} else
	{
		strcpy(woman[woman_num].name, buf[2]);
		woman[woman_num].interest = atoi(buf[3]);
		woman[woman_num].variable = -1;
		for (i = 0; i < woman[woman_num].interest; i++)
			strcpy(woman[woman_num].interests[i], buf[i + 4]);
		woman_num++;
	}
}

void ma()
{
	int w;
	int i, y, z;
	int list = 1;
	int forbreak = 0;
	man_n = 0;
	man_over = 0;
	woman_n = 0;
	woman_over = 0;
	for (w = 0; w < man_num + woman_num; w++)
	{
		if (list == 1)
		{
			manturn: if (man_n >= man_num)
				goto womanturn;
			if (man[man_n].variable == -1)
			{
				for (i = 0; i < woman_num; i++)
				{
					if (woman[i].variable == -1)
					{
						for (y = 0; y < man[man_n].interest; y++)
						{
							for (z = 0; z < woman[i].interest; z++)
							{
								if (strcmp(man[man_n].interests[y],
										woman[i].interests[z]) == 0)
								{
									man[man_n].partner = i;
									man[man_n].variable = 1;
									woman[i].partner = man_n;
									woman[i].variable = 1;
									partner++;
									forbreak = 1;
									man_n++;
									break;
								}
							}
							if (forbreak)
								break;
						}
					}
					if (forbreak)
						break;
				}
			} else
			{
				list = 0;
				man_n++;
			}
			if (forbreak)
				break;
		} else
		{
			womanturn: if (woman_n >= woman_num)
				goto manturn;
			if (woman[woman_n].variable == -1)
			{
				for (i = 0; i < man_num; i++)
				{
					if (man[i].variable == -1)
					{
						for (y = 0; y < woman[man_n].interest; y++)
						{
							for (z = 0; z < man[i].interest; z++)
							{
								if (strcmp(woman[woman_n].interests[y],
										man[i].interests[z]) == 0)
								{
									woman[woman_n].partner = i;
									woman[woman_n].variable = 1;
									man[i].partner = woman_n;
									man[i].variable = 1;
									partner++;
									forbreak = 1;
									woman_n++;
									break;
								}
							}
							if (forbreak)
								break;
						}
					}
					if (forbreak)
						break;
				}
			} else
			{
				list = 1;
				woman_n++;
			}
		}
		if (forbreak)
			break;
	}
}

void un()
{
	int i;
	for (i = 0; i < man_num; i++)
		if (strcmp(man[i].name, buf[1]) == 0)
		{
			man[i].variable = -1;
			woman[man[i].partner].variable = -1;
		}
	for (i = 0; i < woman_num; i++)
		if (strcmp(woman[i].name, buf[1]) == 0)
		{
			woman[i].variable = -1;
			man[woman[i].partner].variable = -1;
		}
}

void pr()
{
	int i;
	man_n = 0;
	woman_n = 0;
	if (partner != 0)
	{
		printf("matched list\nman  -partner- woman\n");
		for (i = 0; i < man_num; i++)
			if (man[i].variable == 1)
				printf("%s  |  %s\n", man[i].name, woman[man[i].partner].name);
	}
	printf("unmatched list(man)\n");

	while (man_n < man_num)
	{
		if (man[man_n].variable == -1)
		{
			printf("%s\n", man[man_n].name);
			man_n++;
		} else
			man_n++;
	}
	printf("\nunmatched list(woman)\n");
	while (woman_n < woman_num)
	{
		if (woman[woman_n].variable == -1)
		{
			printf("%s\n", woman[woman_n].name);
			woman_n++;
		} else
			woman_n++;
	}

	printf("\n");
}
