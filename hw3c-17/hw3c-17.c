/* Name: hw3c-17.c

 * Description: Chinese Railroad System with Shortest-path algorithm
 *
 * Author: Kyunghwa Lim (12/05/2009)
 *
 * Modified by: Kyunghwa Lim (12/06/2009)
 *
 * Version: ALPHA
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* NUMBER OF MAX VERTEX */
#define VERTEXNUM 1024

/* NUMBER OF CITY */
#define CITYNUM 25

/* IF IS NOT A VERTEX */
#define NOTVERTEX -1

/* SET MAX DISTANCE */
#define MAXCOST 1000000

/* NODE */
typedef struct node
{
	int vertex;
	struct node* next; /* point next node */
} NODE;

/* HEAD NODE IN GRAPH LIST STRUCTURE */
typedef struct headtype
{
	int data;
	struct node* first; /* point first node */
} HT;

/* GRAPH STRUCTURE */
typedef struct graph
{
	HT adlist[VERTEXNUM]; /* array of headlist */
} GRAPH;

/* CITY INFORMATION STRUCTURE */
typedef struct city
{
	char name[32]; /* city's name */
	float north; /* city's longitude */
	float east; /* city's latitude */
} CITY;

/* TABLE STRUCTURE */
typedef struct table
{
	int visited;
	int dist;
	int path;
} TABLE;

/*
 * NAME: getint()
 * RECEIVE INT FUNCTION
 * ARGUMENTS: char* str
 * RETURNS: one int variable
 */
int getint(char* str)
{
	/* RETURN VALUE */
	int temp;

	gets(str);

	temp = atol(str); /* string to int */

	return temp;
}

/*
 * NAME: citylist()
 * PRINT CITYLIST FUNCTION
 * ARGUMENTS: CITY* city
 * RETURNS: 1 always
 */
int citylist(CITY* city)
{
	int i;

	/* show city's name */
	printf("City number:\n");

	for (i = 0; i < CITYNUM; i++)
	{
		printf("%d:%10s\t\t", i, city[i].name);

		/* change line every tree cities */
		if (i % 3 == 2)
		{
			printf("\n");
		}
	}

	printf("\n");

	return 1;
}

/*
 * NAME: creategraph()
 * CREATE GRAPH FUNCTION
 * ARGUMENTS: GRAPH* ga, int connect[CITYNUM][CITYNUM]
 * RETURNS: 1 always
 */
int creategraph(GRAPH* ga, int connect[CITYNUM][CITYNUM])
{
	int i, j;
	NODE* temp;

	/* PREPARATION */
	for (i = 0; i < CITYNUM; i++)
	{
		ga->adlist[i].data = i;
		ga->adlist[i].first = NULL;
	}

	/* put the information from connect array to graph */
	for (i = 0; i < CITYNUM; i++)
	{
		for (j = CITYNUM - 1; j >= 0; j--)
		{
			/* this two cities had no connection */
			if (connect[i][j] == MAXCOST || connect[i][j] == 0)
			{
				continue;
			}

			/* insert NODE to graph */
			temp = (NODE*) malloc(sizeof(NODE));
			temp->vertex = j;
			temp->next = ga->adlist[i].first;
			ga->adlist[i].first = temp;
		}
	}

	return 1;
}

/*
 * NAME: inittable()
 * Initialize table function
 * ARGUMENTS: int start, TABLE* table
 * RETURNS: 1 always
 */
int inittable(int start, TABLE* table)
{
	int i;

	/* Initialise table */
	for (i = 0; i < CITYNUM; i++)
	{
		table[i].visited = 0;
		table[i].dist = MAXCOST;
		table[i].path = NOTVERTEX;
	}

	/* set start vertex to itself distance to 0 */
	table[start].dist = 0;

	return 1;
}

/*
 * NAME: dijkstra()
 * dijkstra algorithm function
 * ARGUMENTS: TABLE* table, GRAPH* ga, int connect[CITYNUM][CITYNUM]
 * RETURNS: 1 always
 */
int dijkstra(TABLE* table, GRAPH* ga, int connect[CITYNUM][CITYNUM])
{
	int v, w; /* vertex number */
	int mincost; /* minimum distance of two cities */
	int i;
	NODE* temp;

	while (1)
	{
		/* PREPARATION
		 * set vertex v to -1
		 * set mincost to maxcost
		 */
		v = NOTVERTEX;
		mincost = MAXCOST;

		/* find smallest unvisited distance vertex */
		for (i = 0; i < CITYNUM; i++)
		{
			if (table[i].visited == 0 && table[i].dist < mincost)
			{
				v = i;
				mincost = table[i].dist;
			}
		}

		/* if all vertex was visited then finish */
		if (v == NOTVERTEX)
		{
			break;
		}

		/* set vertex to visited */
		table[v].visited = 1;

		/* for each W adjacent to V */
		for (temp = ga->adlist[v].first; temp != NULL; temp = temp->next)
		{
			w = temp->vertex;
			if (!table[w].visited)
			{
				/* update vertex W to table */
				if (table[v].dist + connect[v][w] < table[w].dist)
				{
					table[w].dist = table[v].dist + connect[v][w];
					table[w].path = v;
				}
			}
		}
	}

	return 1;
}

/*
 * NAME: printpath()
 * print path from Origin to Destination function
 * ARGUMENTS: int vertex, TABLE* table, CITY* city
 * RETURNS: 1 always
 */
int printpath(int vertex, TABLE* table, CITY* city)
{
	if (table[vertex].path != NOTVERTEX)
	{
		printpath(table[vertex].path, table, city);
		printf(" -> ");
	}
	printf("[%s]", city[vertex].name);
	return 1;
}

/*
 * NAME: read()
 * READ FILE FUNCTION
 * ARGUMENTS: CITY* city, GRAPH* ga, int connect[CITYNUM][CITYNUM], char* argv
 * RETURNS: 1 always
 */
int readfile(CITY* city, int connect[CITYNUM][CITYNUM], char* argv)
{
	FILE *fp, *fopen();
	char temp[32];
	int i, j;
	float num[4]; /* to save four number, temp variable */
	int w; /* distance between two cities */

	/* open file and read it */
	if (fp = fopen(argv, "r"))
	{

		/* read one part of city's information */
		for (i = 0; i < CITYNUM; i++)
		{
			fscanf(fp, "%s %f°%f'N %f°%f'E", temp, &num[0], &num[1], &num[2],
					&num[3]);
			strcpy(city[i].name, temp);
			city[i].north = num[0] + num[1] / 60;
			city[i].east = num[2] + num[3] / 60;
		}

		/* read connection of two cities */
		for (i = 0; i < CITYNUM; i++)
		{
			for (j = 0; j < CITYNUM; j++)
			{
				fscanf(fp, "%d", &w);
				if (w == -1)
				{
					w = MAXCOST;
				}
				connect[i][j] = w;
			}
		}
	}

	fclose(fp);

	return 1;
}

/*
 * NAME: menu()
 * PRINT MENU FUNCTION
 * ARGUMENTS:
 * RETURNS: 1 always
 */
int menu(void)
{
	/* Show menu */
	printf("+++++++ MENU ++++++\n");
	printf("1. Shortest-path algorithm with Dijkstra\n");
	printf("2. Quit\n");

	return 1;
}

/*
 * NAME: kernel()
 * PROGRAM KERNEL FUNCTION
 * ARGUMENTS: GRAPH* ga, char* argv
 * RETURNS: 1 always
 */
int kernel(char* argv)
{
	int n; 		/* number of choosed menu */
	int q = 0; 		/* use for quit */
	char str[32]; 		/* use for get string */
	CITY city[CITYNUM]; 	/* array of city */
	int connect[CITYNUM][CITYNUM];	/* TABLE OF linked between two citys */
	int start,end;		/* number of city  start and end */
	TABLE table[CITYNUM];		/* table for start city */
	GRAPH ga;		/* CREATE A GRAPH */

	/* read data from file named argv
	 * save city's name to CITY array
	 * save connection to connect array
	 */
	readfile(city, connect, argv);

	/* use data from file to make a new graph */
	creategraph(&ga, connect);

	/* DO THIS UNTIL QUIT */
	while (!q)
	{
		/* SHOWS MAIN MENU */
		menu();

		/* INPUT NUMBER FOR CHOOSE MENU */
		printf("Input:");
		n = getint(str);

		switch (n)
		{
		/* Shortest-path algorithm with Dijkstra */
		case 1:
			/* show city list */
			citylist(city);

			/* Input start number of city */
			printf("input number for start:");
			start = getint(str);

			/* IF Input Error Selection */
			if (start >= CITYNUM || start < 0)
			{
				printf("Error Input!\n");
				break;
			}

			/* PREPARATION */
			inittable(start, table);

			/* show city list */
			citylist(city);

			/* Input end number of city */
			printf("input number for end:");
			end = getint(str);

			/* IF Input Error Selection */
			if (end >= CITYNUM || end < 0)
			{
				printf("Error Input!\n");
				break;
			}

			/* function of dijkstra algorithm */
			dijkstra(table, &ga, connect);

			/* print passed cities */
			printf("Shortest-path algorithm with Dijkstra:\n");
			printf("Begin -> ");
			printpath(end, table, city);
			printf(" -> End\n");

			/* print total route */
			printf("Total route = %d\n", table[end].dist);
			break;

			/* exit program */
		case 2:
			q = 1;
			break;

			/* IF Input Error select */
		default:
			printf("Error Input!!\n");
			break;
		}
	}

	return 1;
}

/*
 * NAME: main()
 * PROGRAM MAIN FUNCTION
 * ARGUMENTS: int argc, char* argv[]
 * RETURNS: 1 for found file, 0 for no file
 */
int main(int argc, char *argv[])
{
	/* CREATE A GRAPH */

	/* IF NO FILE */
	if (argv[1] == NULL)
	{
		printf("No file\n");
		printf("EX: ./hw3-17 chcities-location.txt\n");

		return 0;
	}
	else
	{
		/* START KERNEL FUNCTION */
		kernel(argv[1]);
	}

	return 0;
}
