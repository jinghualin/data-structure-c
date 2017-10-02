/* Name: hw3a-17.c

 * Description: Chinese Railroad System with Depth First Search, Breadth First Search ,
 * 				Depth First Search with Origin to Destination
 *
 * Author: Kyunghwa Lim (11/15/2009)
 *
 * Modified by: Kyunghwa Lim (11/21/2009)
 *
 * Version: BETA
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

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

/* QUEUE FOR CITY IN BFS*/
typedef struct queue
{
	int data[VERTEXNUM]; /* queue array */
	int front; /* index of front */
	int rear; /* index of rear */
} SQ;

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
 * NAME: initqueue()
 * INITIALIZE QUEUE FUNCTION
 * ARGUMENTS: SQ* q
 * RETURNS: 1 always
 */
int initqueue(SQ* q)
{
	q->front = q->rear = 0; /* initialize queue */

	return 1;
}

/*
 * NAME:enqueue()
 * ENQUEUE FUNCTION
 * ARGUMENTS: QS* q, int n
 * RETURNS: 1 always
 */
int enqueue(SQ* q, int n)
{
	/* if rear+1 equal to front, means queue is full */
	if ((q->rear + 1) % VERTEXNUM == q->front)
	{
		printf("queue full");
		return 0;
	}
	else
	{
		/* insert one data to queue */
		q->data[q->rear] = n;
		q->rear = (q->rear + 1) % VERTEXNUM;
	}
	return 1;
}

/*
 * NAME: dequeue()
 * DEQUEUE FUNCTION
 * ARGUMENTS: SQ* q
 * RETURNS: index of city number,0 for empty
 */
int dequeue(SQ* q)
{
	/* RETURN VALUE */
	int n; /* index of city number */

	/* if front equal to rear, means queue is empty */
	if (q->front == q->rear)
	{
		printf("queue empty");
		return 0;
	}
	else
	{
		/* delete one data from queue */
		n = q->data[q->front];
		q->front = (q->front + 1) % VERTEXNUM;
	}
	return n;
}

/*
 * NAME: isempty()
 * DETERMINE QUEUE IS EMPTY FUNCTION
 * ARGUMENTS: SQ* q
 * RETURNS: 1 for empty, 0 for have node
 */
int isempty(SQ* q)
{
	/* if queue is empty,return 1  else return 0 */
	return (q->front == q->rear);
}

/*
 * NAME: depthfirstsearch()
 * Depth First Search FUNCTION
 * ARGUMENTS: GRAPH* g, int n, int visited[CITYNUM], CITY* city
 * RETURNS: 1 always
 */
int depthfirstsearch(GRAPH* ga, int n, int visited[CITYNUM], CITY* city)
{
	NODE* temp;

	printf("[%s]->", (city + (ga->adlist[n].data))->name);

	visited[n] = 1;

	/* visit all linked cities */
	for (temp = ga->adlist[n].first; temp != NULL; temp = temp->next)
	{
		/* if this city not visited ,compare it,else pass this city */
		if (!visited[temp->vertex])
		{
			/* visit next city */
			depthfirstsearch(ga, temp->vertex, visited, city);
		}
	}

	return 1;
}

/*
 * NAME: breadthfirstsearch()
 * Breadth First Search  FUNCTION
 * ARGUMENTS: GRAPH* g, int n, int visited[CITYNUM], CITY* city
 * RETURNS: 1 always
 */
int breadthfirstsearch(GRAPH* ga, int n, int visited[CITYNUM], CITY* city)
{
	SQ q; /* create a queue */
	NODE* temp;

	/* initialize queue */
	initqueue(&q);

	printf("[%s]->", (city + (ga->adlist[n].data))->name);

	visited[n] = 1;

	/* enqueue city number which started */
	enqueue(&q, n);

	/* DO THIS UNTIL QUEUE IS EMPTY */
	while (!isempty(&q))
	{
		/* delete last visited cities */
		n = dequeue(&q);
		temp = ga->adlist[n].first;

		/* DO THIS UNTIL TEMP IS NULL */
		while (temp != NULL)
		{
			/* if this city not visited ,compare it,else pass this city */
			if (!visited[temp->vertex])
			{
				printf("[%s]->", (city + (ga->adlist[temp->vertex].data))->name);
				visited[temp->vertex] = 1;
				enqueue(&q, temp->vertex);
			}
			temp = temp->next;
		}
	}

	return 1;
}

/*
 * NAME: vector()
 * CALCULATE VECTOR FUNCTION
 * ARGUMENTS: CITY* city1, CITY* city2, CITY* temp
 * RETURNS: one vector
 */
CITY* vector(CITY* city1, CITY* city2, CITY* temp)
{
	/* two point's coordinate */
	float x1, x2, y1, y2;

	x1 = city1->east;
	x2 = city2->east;
	y1 = city1->north;
	y2 = city2->north;
	temp->east = x2 - x1;
	temp->north = y2 - y1;

	/* return a vector */
	return temp;
}

/*
 * NAME: angle()
 * CALCULATE ANGLE FUNCTION
 * ARGUMENTS: CITY* vector1, CITY* vector2
 * RETURNS: return the value of cos(angle)
 */
float angle(CITY* vector1, CITY* vector2)
{
	/* RETURN VALUE */
	float result;

	result = ((vector1->east) * (vector2->east) + (vector1->north)
			* (vector2->north)) / (sqrt((vector1->east) * (vector1->east)
			+ (vector1->north) * (vector1->north)) * sqrt((vector2->east)
			* (vector2->east) + (vector2->north) * (vector2->north)));

	return (result);
}

/*
 * NAME: origintodestination()
 * PROGRAM MAIN FUNCTION
 * ARGUMENTS: GRAPH* g, int n1, int n2, int visited[CITYNUM],
 CITY* city)
 * RETURNS: -1 for arrive city, 0 for return previous city, 1 for go to next city
 */
int origintodestination(GRAPH* ga, int n1, int n2, int visited[CITYNUM],
		CITY* city)
{
	/* temp node */
	NODE* p;
	NODE* temp;
	/* vector1 is from current city to next city */
	CITY* vector1 = (CITY*) malloc(sizeof(CITY));
	/* vector2 is from current city to destination city */
	CITY* vector2 = (CITY*) malloc(sizeof(CITY));

	int sign = 1; /* quit variable */
	int vertex;
	float big; /* if angle is small, cos value is big */
	int end; /* end sign variable */

	vector2 = vector(city + n1, city + n2, vector2);
	p = ga->adlist[n1].first;

	/* print current city */
	printf("[%s]->", (city + (ga->adlist[n1].data))->name);

	/* this city is visited */
	visited[n1] = 1;

	/* if arrive to destination city , return -1 to finish all OTD function */
	if (n1 == n2)
	{
		return -1;
	}

	/* DO THIS UNTIL QUIT */
	while (sign >= 0)
	{
		/* if visited from current city to all next city,  finish this OTD function */
		if (p == NULL)
		{
			return 0;
		}

		/* PREPARATION */
		end = 0;
		temp = ga->adlist[n1].first;

		/* DO THIS UNTIL TEMP POINT NULL */
		while (temp)
		{
			/* if this city not visited ,compare it,else pass this city */
			if (!visited[temp->vertex])
			{
				vector1 = vector(city + n1, city + temp->vertex, vector1);
				end++;
				/* if there is only one city can go */
				if (end == 1)
				{
					vertex = temp->vertex;
					big = angle(vector1, vector2);
				}
				else
				{
					/* find largest angle */
					if (angle(vector1, vector2) > big)
					{
						big = angle(vector1, vector2);
						vertex = temp->vertex;
					}
				}
			}
			temp = temp->next;
		}

		/* if there is no city can visit ,return 0 */
		if (end == 0)
		{
			return 0;
		}

		/* visit next city */
		sign = origintodestination(ga, vertex, n2, visited, city);

		/* if next city can't visit any other city, print current city */
		if (sign == 0)
		{
			printf("[%s]->", (city + (ga->adlist[n1].data))->name);
		}

		/* if arrive destination city, return -1 */
		if (sign == -1)
		{
			return -1;
		}

		p = p->next;
	}

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
			if (connect[i][j] <= 0)
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
 * NAME: menu()
 * PRINT MENU FUNCTION
 * ARGUMENTS:
 * RETURNS: 1 always
 */
int menu(void)
{
	/* Show menu */
	printf("+++++++ MENU ++++++\n");
	printf("1. Depth First Search\n");
	printf("2. Breadth First Search\n");
	printf("3. Depth First Search with Origin to Destination\n");
	printf("4. Quit\n");

	return 1;
}

/*
 * NAME: kernel()
 * PROGRAM KERNEL FUNCTION
 * ARGUMENTS: GRAPH* ga, char* argv
 * RETURNS: 1 always
 */
int kernel(GRAPH* ga, char* argv)
{
	int visited[CITYNUM]; /* array of visit record, 1 for visited  0 for not visited	*/
	CITY city[CITYNUM]; /* array of city */
	int connect[CITYNUM][CITYNUM]; /* TABLE OF linked between two citys */
	int i;
	int n; /* number of choosed menu */
	int q = 0; /* use for quit */
	char str[32]; /* use for get string */
	int start, end; /* index of start number and end number */

	/* read data from file named argv
	 * save city's name to CITY array
	 * save connection to connect array
	 */
	readfile(city, ga, connect, argv);

	/* use data from file to make a new graph */
	creategraph(ga, connect);

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
			/* Depth First Search */
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
			for (i = 0; i < CITYNUM; i++)
			{
				visited[i] = 0;
			}

			printf("Depth First Search :\n");
			printf("Begin->");

			/* start Depth First Search */
			depthfirstsearch(ga, start, visited, city);

			printf("End\n");
			break;

			/* Breadth First Search */
		case 2:
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
			for (i = 0; i < CITYNUM; i++)
			{
				visited[i] = 0;
			}

			printf("Breadth First Search :\n");
			printf("Begin->");
			/* start Breadth First Search */
			breadthfirstsearch(ga, start, visited, city);

			printf("End\n");
			break;

			/* Depth First Search with Origin to Destination */
		case 3:
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
			for (i = 0; i < CITYNUM; i++)
			{
				visited[i] = 0;
			}
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
			printf("Depth First Search with Origin to Destination:\n");
			printf("Begin->");

			/* start Depth First Search with Origin to Destination */
			origintodestination(ga, start, end, visited, city);

			printf("End\n");
			break;

			/* exit program */
		case 4:
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
