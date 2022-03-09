#include <stdio.h>
#include <stdlib.h>

void solve1();	//다리비용 < 매립지비용
void solve2();	//다리비용 >= 매립지비용
int find(int i);
int Union(int i, int j);
void search();

typedef struct brid
{
	int l1;
	int l2;
	int built;	//지었으면 1, 아니면 0
}brid;


typedef struct cases
{
	int n;	//섬의 개수
	int m;	//다리의 개수
	int cland;
	int croad;
	brid* bridge;
	int cost;
	int groups;
	int builted_bridges;
}cases;

int N;
int k = 0;
cases* Ncase;
FILE* fp;
int min = -1;
int *parent;
int flag = 0;
int main()
{
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &N);
	Ncase = (cases*)malloc(sizeof(cases) * N);
	while (k < N)
	{
		fscanf(fp, "%d %d %d %d", &(Ncase[k].n), &(Ncase[k].m), &(Ncase[k].cland), &(Ncase[k].croad));
		Ncase[k].bridge = (brid*)malloc(sizeof(brid) * Ncase[k].m);
		parent = (int*)malloc(sizeof(int) * Ncase[k].n);
		for (int i = 0; i < Ncase[k].n; i++)
		{
			parent[i] = -1;
		}
		for (int i = 0; i < Ncase[k].m; i++)
		{
			fscanf(fp, "%d %d", &(Ncase[k].bridge[i].l1), &(Ncase[k].bridge[i].l2));
		}
		if (Ncase[k].cland <= Ncase[k].croad)
		{
			solve2();
			break;
		}
		else
		{
			solve1();
			flag = 1;
		}
		k++;
	}
	if (flag == 1)
	{
		search();
	}
	printf("\n");
	return 0;
}

int find(int i)
{
	for (; parent[i - 1] >= 0; i = parent[i - 1])
	{

	}
	return i;
}

int Union(int i, int j)
{
	if (i != j)
	{
		parent[j - 1] = i;
		return 1;
	}
	return 0;
}


void solve2()
{
	min = Ncase[k].cland * Ncase[k].n;
	for(int i = 0; i < N; i++)
	{
		printf("%d\n", i + 1);
	}
	printf("%d", min);
	return;
}

void solve1()
{
	int count = 0;
	int i, j;
	int u, v;
	for (i = 0; i < Ncase[k].m; i++)
	{
		u = Ncase[k].bridge[i].l1;
		v = Ncase[k].bridge[i].l2;
		u = find(u);
		v = find(v);
		if (Union(u, v))
		{
			Ncase[k].bridge[i].built = 1;
		}
		else
		{
			Ncase[k].bridge[i].built = 0;
		}
	}


	for (int z = 0; z < Ncase[k].n; z++)
	{
		if (parent[z] == -1)
		{
			count++;
		}
	}
	Ncase[k].groups = count;
	count = 0;
	for (int z = 0; z < Ncase[k].m; z++)
	{
		if (Ncase[k].bridge[z].built == 1)
		{
			count++;
		}
	}
	Ncase[k].builted_bridges = count;
	Ncase[k].cost = Ncase[k].builted_bridges * Ncase[k].croad + Ncase[k].groups * Ncase[k].cland;
	if (min == -1)
	{
		min = Ncase[k].cost;
	}
	else if (min > Ncase[k].cost)
	{
		min = Ncase[k].cost;
	}
}

void search()
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		if (Ncase[i].cost <= min)
		{
			printf("%d\n", i + 1);
			for (j = 0; j < Ncase[i].m; j++)
			{
				if (Ncase[i].bridge[j].built == 1)
				{
					printf("%d %d\n", Ncase[i].bridge[j].l1, Ncase[i].bridge[j].l2);
				}
			}
		}
	}
	printf("%d", min);
}