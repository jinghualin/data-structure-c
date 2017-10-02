/*
 * hw3-17.c
 *
 *  Created on: 15 Nov 2009
 *      Author: lin
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define VERTEXNUM 1024

typedef struct city
{
	char name[32];
	float north;
	float east;
} CITY;

typedef struct node
{
	int vertex;
	struct node* next;
} NODE;

typedef struct headtype
{
	int data;
	struct node* first;
} HT;

typedef struct graph
{
	HT adlist[VERTEXNUM];
	int n;
} GRAPH;

typedef struct queue
{
	int data[VERTEXNUM];
	int front;
	int rear;
} SQ;

int getint(char* str)
{
	int i;

	gets(str);

	i = atol(str);

	return i;
}

void initqueue(SQ* q)
{
	q->front = q->rear = 0;
}

int enqueue(SQ* q, int n)
{
	if ((q->rear + 1) % VERTEXNUM == q->front)
	{
		printf("queue full");
		return 0;
	}
	q->data[q->rear] = n;
	q->rear = (q->rear + 1) % VERTEXNUM;
	return 1;
}

int dequeue(SQ* q)
{
	int n;
	if (q->front == q->rear)
	{
		printf("queue empty");
		return 0;
	}
	n = q->data[q->front];
	q->front = (q->front + 1) % VERTEXNUM;
	return n;
}

int isEmpty(SQ* q)
{
	return (q->front == q->rear);
}

int DFSL(GRAPH* g, int n, int visited[25], CITY* city)
{
	NODE* p;
	printf("[%s]->", (city + (g->adlist[n].data))->name);
	visited[n] = 1;
	for (p = g->adlist[n].first; p != NULL; p = p->next)
		if (!visited[p->vertex])
			DFSL(g, p->vertex, visited, city);

	return 1;
}

void BFSL(GRAPH* g, int n, int visited[25], CITY* city)
{
	SQ q;
	NODE* p;

	initqueue(&q);
	printf("[%s]->", (city + (g->adlist[n].data))->name);
	visited[n] = 1;
	enqueue(&q, n);
	while (!isEmpty(&q))
	{
		n = dequeue(&q);
		p = g->adlist[n].first;
		while (p != NULL)
		{
			if (!visited[p->vertex])
			{
				printf("[%s]->", (city + (g->adlist[p->vertex].data))->name);
				visited[p->vertex] = 1;
				enqueue(&q, p->vertex);
			}
			p = p->next;
		}
	}
}

CITY* vector(CITY* city1, CITY* city2, CITY* temp)
{
	float x1, x2, y1, y2;
	x1 = city1->east;
	x2 = city2->east;
	y1 = city1->north;
	y2 = city2->north;
	//	printf("CHECK:%f %f\n",x1,y1);
	temp->east = x2 - x1;
	temp->north = y2 - y1;
	//	printf("%f %f\n",temp->east,temp->north);
	return temp;
}

float angle(CITY* vector1, CITY* vector2)
{
	float result;

	result = ((vector1->east) * (vector2->east) + (vector1->north)
			* (vector2->north)) / (sqrt((vector1->east) * (vector1->east)
			+ (vector1->north) * (vector1->north)) * sqrt((vector2->east)
			* (vector2->east) + (vector2->north) * (vector2->north)));

	return (result);
}

int DFSLOTD(GRAPH* g, int n1, int n2, int visited[25], CITY* city)
{
	NODE* p;
	NODE* temp;
	CITY* vector1 = (CITY*) malloc(sizeof(CITY));
	CITY* vector2 = (CITY*) malloc(sizeof(CITY));
	int sign = 1;
	int vertex;
	float big;
	int end;

	vector2 = vector(city + n1, city + n2, vector2);
	p = g->adlist[n1].first;

	printf("[%s]->", (city + (g->adlist[n1].data))->name);

	visited[n1] = 1;

	if (n1 == n2)
		return -1;

	while (sign == 1)
	{
		if (p == NULL)
		{
			return 0;
		}

		end = 0;
		temp = g->adlist[n1].first;
		;
		while (temp)
		{
			//			printf("1:%s\n", city[temp->vertex].name);
			if (!visited[temp->vertex])
			{
				vector1 = vector(city + n1, city + temp->vertex, vector1);
				end++;
				if (end == 1)
				{
					vertex = temp->vertex;
					big = angle(vector1, vector2);
					//					printf("%f\n", big);

				} else
				{
					if (angle(vector1, vector2) > big)
					{
						big = angle(vector1, vector2);
						vertex = temp->vertex;
					}
				}
			}
			//			printf("%d\n", end);
			temp = temp->next;
		}
		//		printf("2:%s\n", city[vertex].name);
		if (end == 0)
		{
			return 0;
		}

		sign = DFSLOTD(g, vertex, n2, visited, city);

		if (sign == 0)
			printf("[%s]->", (city + (g->adlist[n1].data))->name);

		if (sign == -1)
			return -1;

		p = p->next;
	}
	return 1;
}



int creategraph(GRAPH* ga, int connect[25][25])
{
	int i, j;
	NODE* p;

	//	printf("CHECK!!\n");
	for (i = 0; i < ga->n; i++)
	{
		ga->adlist[i].data = i;
		ga->adlist[i].first = NULL;
	}

	for (i = 0; i < ga->n; i++)
	{
		for (j = ga->n - 1; j >= 0; j--)
		{
			if (connect[i][j] <= 0)
			{
				continue;
			}

			p = (NODE*) malloc(sizeof(NODE));
			p->vertex = j;
			p->next = ga->adlist[i].first;
			ga->adlist[i].first = p;
		}
	}

	return 1;
}

int ReadFile(CITY* city, GRAPH* ga, int connect[25][25], char* argv)
{
	FILE *fp, *fopen();
	char temp[32];
	int i, j;
	float num[4];
	int w;
	if (fp = fopen(argv, "r"))
	{

		for (i = 0; i < ga->n; i++)
		{
			fscanf(fp, "%s %f°%f'N %f°%f'E", temp, &num[0], &num[1], &num[2],
					&num[3]);
			strcpy(city[i].name, temp);
			//			printf("%s\n",city[i].name);
			city[i].north = num[0] + num[1] / 60;
			city[i].east = num[2] + num[3] / 60;
			//			printf("%s:%f %f\n",city[i].name,city[i].east,city[i].north);
		}

		for (i = 0; i < ga->n; i++)
		{
			for (j = 0; j < ga->n; j++)
			{
				fscanf(fp, "%d", &w);
				connect[i][j] = w;
				//				printf("%d\n",connect[i][j]);
			}
		}

	}
	fclose(fp);
	return 1;
}

int CheckFile(char* argv)
{
	FILE *fp, *fopen();
	int ret = 0;
	char temp[3][32];
	if (fp = fopen(argv, "r"))
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %s", temp[0], temp[1], temp[2]);
			if (strcmp(temp[0], "0") == 0)
				break;
			ret++;
		}
		printf("%s: a file has entries of %d cities in China\n", argv, ret);
		fclose(fp);

	} else
	{
		printf("No file\n");
		printf("EX: ./a.out chcities-location.txt\n");
	}

	return (ret);
}

int menu(void)
{
	printf("+++++++ MENU ++++++\n");
	printf("1. Show City Number\n");
	printf("2. Depth First Search\n");
	printf("3. Breadth First Search\n");
	printf("4. Depth First Search with Origin to Destination\n");
	printf("5. Quit\n");

	return 1;
}

int kernel(GRAPH* ga, char* argv)
{
	int visited[ga->n];
	CITY city[ga->n];
	int connect[ga->n][ga->n];
	int i;
	int n;
	int q = 0;
	char str[32];
	int start, end;
	//	CITY* x = (CITY*) malloc(sizeof(CITY));
	//	CITY* y = (CITY*) malloc(sizeof(CITY));
	//	NODE* p;
	ReadFile(city, ga, connect, argv);

	//	for (i = 0; i < ga->n; i++)
	//		printf("%s: %f %f \n", city[i].name, city[i].north, city[i].east);
	//	for (i = 0; i < ga->n; i++)
	//	{
	//		for (j = 0; j < ga->n; j++)
	//			printf("%d ", connect[i][j]);
	//		printf("\n");
	//	}
	creategraph(ga, connect);

	//	for (i = 0; i < ga->n; i++)
	//	{
	//		p = ga->adlist[i].first;
	//		printf("%d:",i);
	//
	//		while (p)
	//		{
	//			printf("%d->", p->vertex);
	//			p = p->next;
	//		}
	//		printf("\n");
	//	}

	//	printf("Input City for start:");
	//	gets(temp);
	//	for (i = 0; i < ga->n; i++)
	//	{
	//		if (strcmp(temp, city[i].name) == 0)
	//			break;
	//	}
	while (!q)
	{
		menu();
		printf("Input:");
		n = getint(str);
		switch (n)
		{
		case 1:
			printf("City number:\n");
			for (i = 0; i < ga->n; i++)
			{
				printf("%d:%s\n", i, city[i].name);
			}
			break;
		case 2:
			printf("input number for start:");
			start = getint(str);
			if (start >= ga->n || start < 0)
			{
				printf("Error Input!\n");
				break;
			}
			for (i = 0; i < ga->n; i++)
				visited[i] = 0;
			printf("Depth First Search :\n");
			printf("Begin->");
			DFSL(ga, start, visited, city);
			printf("End\n");
			break;
		case 3:
			printf("input number for start:");
			start = getint(str);
			if (start >= ga->n || start < 0)
			{
				printf("Error Input!\n");
				break;
			}
			for (i = 0; i < ga->n; i++)
				visited[i] = 0;
			printf("Breadth First Search :\n");
			printf("Begin->");
			BFSL(ga, start, visited, city);
			printf("End\n");
			break;
		case 4:
			printf("input number for start:");
			start = getint(str);
			if (start >= ga->n || start < 0)
			{
				printf("Error Input!\n");
				break;
			}
			for (i = 0; i < ga->n; i++)
				visited[i] = 0;
			printf("input number for end:");
			end = getint(str);
			if (end >= ga->n || end < 0)
			{
				printf("Error Input!\n");
				break;
			}
			printf("Depth First Search with Origin to Destination:\n");
			printf("Begin->");

			DFSLOTD(ga, start, end, visited, city);
			//	x = vector(&city[15], &city[0], x);
			//	y = vector(&city[15], &city[3], y);
			//	printf("%f\n", angle(x, y));
			printf("End\n");
			break;
		case 5:
			q = 1;
			break;
		default:
			printf("Error Input!!\n");
			break;
		}
	}

	return 1;
}

int main(int argc, char *argv[])
{
	GRAPH ga;
	ga.n = CheckFile(argv[1]);
	if (ga.n == 0)
		return 0;
	kernel(&ga, argv[1]);
	//	ga.n = CheckFile("chcities-location.txt");
	//	if (ga.n == 0)
	//		return 0;
	//	kernel(&ga, "chcities-location.txt");
	return 1;
}
