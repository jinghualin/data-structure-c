/* Name: hw3b-17.c

 * Description: Chinese Railroad System with Depth First Search, Breadth First Search ,
 * 				Depth First Search with Origin to Destination and Minimum Spanning Tree
 *
 * Author: Kyunghwa Lim (11/28/2009)
 *
 * Modified by: Kyunghwa Lim (11/29/2009)
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

/* CITY INFORMATION STRUCTURE */
typedef struct city
{
	char name[32]; /* city's name */
	float north; /* city's longitude */
	float east; /* city's latitude */
} CITY;

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
 * NAME: read()
 * READ FILE FUNCTION
 * ARGUMENTS: CITY* city, GRAPH* ga, int connect[CITYNUM][CITYNUM], char* argv
 * RETURNS: 1 always
 */
int readfile(CITY* city, GRAPH* ga, int connect[CITYNUM][CITYNUM], char* argv)
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
	//	printf("1. Depth First Search\n");
	//	printf("2. Breadth First Search\n");
	//	printf("3. Depth First Search with Origin to Destination\n");
	printf("1. Minimum Spanning Tree\n");
	printf("2. Quit\n");

	return 1;
}

/*
 * NAME: prim()
 * MINIMUM SPANNING TREE WITH PRIM'S ALGORITHM
 * ARGUMENTS: CITY* city, int graph[CITYNUM][CITYNUM]
 * RETURNS: sum of route
 */
int prim(CITY* city, int graph[CITYNUM][CITYNUM])
{
	/* lowcost[i] record the shortest distance of i，
	 * -1 for large, 0 for visited
	 */
	int lowcost[CITYNUM];

	/* visit[i] record start from lowcost[i]， 0 for visited */
	int visit[CITYNUM];

	/* for loop index */
	int i, j;

	/* the shortest distance */
	int min;

	/* the shortest distance of city number */
	int minid;

	/* sum of all distance */
	int sum = 0;

	/* index */
	int index = 1;
	/* default form city 0， initialize from city 1 */
	for (i = 1; i < CITYNUM; i++)
	{
		/* initialize all distance one city to city 0 */
		lowcost[i] = graph[0][i];
		/* set all city to city 0 */
		visit[i] = 0;
	}

	/* city 0 is visited */
	visit[0] = 0;

	/* loop 24 because it has 25 city */
	for (i = 1; i < CITYNUM; i++)
	{
		/* initialize shortest distance and city id */
		min = 999999;
		minid = 0;

		/* find shortest distance */
		for (j = 1; j < CITYNUM; j++)
		{
			/* shorter than shortest distance, not visited and can visit */
			if (lowcost[j] < min && lowcost[j] != 0 && lowcost[j] > 0)
			{
				min = lowcost[j];
				minid = j;
			}
		}
		/* print city name of start and finish */
		printf("[%2d] %10s - %10s\n", index++, city[visit[minid]].name,
				city[minid].name);

		/* plus distance */
		sum += min;

		/* set city of minid is visited */
		lowcost[minid] = 0;

		/* update lowcost */
		for (j = 1; j < CITYNUM; j++)
		{
			/* find smaller distance */
			if (lowcost[j] > 0)
			{
				if (graph[minid][j] < lowcost[j] && graph[minid][j] > 0)
				{
					/* update distance */
					lowcost[j] = graph[minid][j];

					/* update record */
					visit[j] = minid;
				}
			} else if (lowcost[j] == -1)
			{
				if (graph[minid][j] > 0)
				{
					lowcost[j] = graph[minid][j];

					visit[j] = minid;
				}
			}
		}
	}
	/* return  shortest distance */
	return sum;
}
/*
 * NAME: kernel()
 * PROGRAM KERNEL FUNCTION
 * ARGUMENTS: GRAPH* ga, char* argv
 * RETURNS: 1 always
 */
int kernel(GRAPH* ga, char* argv)
{
	CITY city[CITYNUM]; /* array of city */
	int connect[CITYNUM][CITYNUM]; /* TABLE OF linked between two citys */
	int sum;
	int n; /* number of choosed menu */
	int q = 0; /* use for quit */
	char str[32]; /* use for get string */

	/* read data from file named argv
	 * save city's name to CITY array
	 * save connection to connect array
	 */
	readfile(city, ga, connect, argv);

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
		/* Minimum Spanning tree */
		case 1:

			sum = prim(city, connect);
			printf("Total sorted edge = %d\n", sum);
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
	GRAPH ga;

	/* IF NO FILE */
	if (argv[1] == NULL)
	{
		printf("No file\n");
		printf("EX: ./hw3-17 chcities-location.txt\n");

		return 0;
	}

	/* START KERNEL FUNCTION */
	kernel(&ga, argv[1]);

	return 1;
}
