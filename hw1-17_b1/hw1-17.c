/*
 ============================================================================
 Name        : hw1-17.c
 Author      : Lim Kyunghwa
 Version     : beta
 Copyright   : YUST-data structure
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct da
{
	char name[32];
	char gender;
	int noi; /* number of interest  */
	int iop; /* index of partner  */
	char interest[10][32];
} DA;

int process(char* str, DA* new)
{
	char temp[15][32];
	int i = 0;
	int j;
	char *p;

	for (p = strtok(str, " \t\r\n"); p; p = strtok(NULL, " \t\r\n"))
	{
		strcpy(temp[i], p);
		i++;
	}

	if (strcmp(temp[0], "ne") == 0)
	{
		strcpy(new->name, temp[2]);
	} else
	{
		strcpy(new->name, temp[1]);
	}

	new->gender = temp[1][0];
	new->noi = atol(temp[3]);
	new->iop = -1;

	for (j = 0; j < new->noi; j++)
	{
		strcpy(new->interest[j], temp[j + 4]);
	}

	return (1);
}

int newclient(DA* f, DA* m, int* fc, int* mc, DA* new)
{
	if (new->gender == 'f')
	{
		memcpy(f + (*fc)++, new, sizeof(DA));
	} else if (new->gender == 'm')
	{
		memcpy(m + (*mc)++, new, sizeof(DA));
	} else
		printf("Error\n");

	return (1);
}

int matchclient(DA* f, DA* m, int fc, int mc)
{
	int i, j, x, y;

	for (i = 0; i < fc; i++)
	{
		if (f[i].iop != -1)
			continue;

		for (j = 0; j < mc; j++)
		{
			if (m[j].iop != -1)
				continue;
			for (x = 0; x < f[i].noi; x++)
			{
				for (y = 0; y < m[j].noi; y++)
				{
					if (strcmp(f[i].interest[x], m[j].interest[y]) == 0)
					{
						f[i].iop = j;
						m[j].iop = i;
						break;
					}
				}
				if (f[i].iop != -1)
					break;
			}
			if (f[i].iop != -1)
				break;
		}
	}
	return (1);
}

int unmatchclient(DA* f, DA* m, int fc, int mc, DA* new)
{
	int i;

	for (i = 0; i < fc; i++)
	{
		if (strcmp(f[i].name, new->name) == 0)
		{
			m[f[i].iop].iop = -1;
			f[i].iop = -1;
		}
	}

	for (i = 0; i < mc; i++)
	{
		if (strcmp(m[i].name, new->name) == 0)
		{
			f[m[i].iop].iop = -1;
			m[i].iop = -1;
		}
	}

	return (1);
}

int printlist(DA* f, DA* m, int fc, int mc)
{
	int i, j;

	printf("female list\n");

	for (i = 0; i < fc; i++)
	{
		printf(" [%2d] name:<%s>  noi:<%d> ", i, f[i].name, f[i].noi);

		for (j = 0; j < f[i].noi; j++)
		{
			printf("%s ", f[i].interest[j]);
		}

		if (f[i].iop != -1)
		{
			printf("partner:[%s]", m[f[i].iop].name);
		}

		printf("\n");
	}

	printf("male list\n");

	for (i = 0; i < mc; i++)
	{
		printf(" [%2d] name:<%s> noi:<%d> ", i, m[i].name, m[i].noi);

		for (j = 0; j < m[i].noi; j++)
		{
			printf("%s ", m[i].interest[j]);
		}

		if (m[i].iop != -1)
		{
			printf("partner:[%s]", f[m[i].iop].name);
		}

		printf("\n");
	}

	return (1);
}

int mminit(int* fc, int* mc)
{
	*fc = 0;
	*mc = 0;
	return (1);
}

int mmmenu(DA* f, DA* m, int* fc, int* mc)
{
	int quit = 0;
	char str[128];
	DA* new = (DA*)malloc(sizeof(DA));

	/* Menu list  */
	printf("ne: new client <f/m> <noi> <interest>....\n");
	printf("ma: match client <name>\n");
	printf("un: unmatch\n");
	printf("pr: print list\n");
	printf("qu: quit program\n");

	while (!quit)
	{
		printf("> ");

		gets(str);

		if (strncmp(str, "ne", 2) == 0)
		{
			process(str, new);
			newclient(f, m, fc, mc, new);
		} else if (strncmp(str, "ma", 2) == 0)
		{
			matchclient(f, m, *fc, *mc);
		} else if (strncmp(str, "un", 2) == 0)
		{
			process(str, new);
			unmatchclient(f, m, *fc, *mc, new);
		} else if (strncmp(str, "pr", 2) == 0)
		{
			printlist(f, m, *fc, *mc);
		} else if (strncmp(str, "qu", 2) == 0)
		{
			quit = 1;
		} else
			printf("Error\n");

	}

	free(new);
	return (0);
}
int main(void)
{
	DA f[50];
	DA m[50];
	int fc = 0;
	int mc = 0;

	mminit(&fc, &mc);

	mmmenu(f, m, &fc, &mc);

	return (0);
}
