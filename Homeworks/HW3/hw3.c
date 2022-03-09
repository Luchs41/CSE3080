#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 10000
#define MAX_EDGES 50000001

typedef struct {
  int u;
  int v;
  int weight;
} edge;

//Global Variables
edge minHeap[MAX_EDGES];
int sizeH = 0;
int numV;
int numE;
int parent[MAX_VERTICES];
FILE* fpOutput;

//Functions
void insertMinHeap(edge newEdge);
edge deleteMinHeap();
void kruskal();
void Union(int i, int j);
int Find(int i);


int main(int argNum, char **argName)
{
  
  if(argNum != 2)
  {
    printf("usage: ./hw3 input_filename\n");
    return -1;
  }
  double time = clock();
  //Command line Error
  FILE* fpInput = fopen(argName[1], "r");
  if(!fpInput)
  {
    printf("The input file does not exist.\n");
    return -1;
  }
  //File open Error
  
  fpOutput = fopen("hw3_result.txt", "w");
  //Output File generate & open

  fscanf(fpInput, "%d", &numV);
  fscanf(fpInput, "%d", &numE);
  
  //read the number of vertices and edges
  for(int i = 0; i < numV; i++)
  {
    parent[i] = -1;
  }
  edge tempEdge;
  for(int i = 0; i < numE; i++)
  {
    fscanf(fpInput, "%d %d %d", &tempEdge.u, &tempEdge.v, &tempEdge.weight);
    insertMinHeap(tempEdge);
  }
  
  kruskal();
  

  printf("output written to hw3_result.txt. \nrunning time: %.6f seconds\n", (clock() - time) / CLOCKS_PER_SEC);
  fclose(fpInput);
  fclose(fpOutput);
  return 0;
}

void insertMinHeap(edge newEdge)
{
  if(sizeH == MAX_EDGES - 1)
  {
    printf("Heap is FULL\n");
    return;
  }
  int i = ++sizeH;
  while((i != 1) && (newEdge.weight < minHeap[i / 2].weight))
  {
    minHeap[i] = minHeap[i / 2];
    i /=2;
  }
  minHeap[i] = newEdge;
}

edge deleteMinHeap()
{
  int parent, child;
  edge item = minHeap[1];
  edge temp;
  temp = minHeap[sizeH--];
  parent = 1; child = 2;
  while(child <= sizeH)
  {
    if((child < sizeH) && (minHeap[child].weight > minHeap[child + 1].weight)) child++;
    if(temp.weight <= minHeap[child].weight) break;
    minHeap[parent] = minHeap[child];
    parent = child;
    child *= 2;
  }
  minHeap[parent] = temp;
  return item;
}

void kruskal()
{
  int count = 0;
  edge temp;
  int weightSum = 0;
  int u, v;

  while(count < numV - 1)
  {
    
    temp = deleteMinHeap();
    
    u = Find(temp.u);
    
    v = Find(temp.v);
    
    if(u != v)
    {
      fprintf(fpOutput, "%d %d %d\n", temp.u, temp.v, temp.weight);
      weightSum += temp.weight;
      count++;
      Union(u, v);
    }
  }
  fprintf(fpOutput, "%d\n", weightSum);
  if(count == numV - 1)
    fprintf(fpOutput, "CONNECTED\n");
  else
    fprintf(fpOutput, "DISCONNECTED\n");
}

void Union(int i, int j)
{
  int temp = parent[i] + parent[j];
  if(parent[i] > parent[j])
  {
    parent[i] = j;
    parent[j] = temp;
  }
  else
  {
    parent[j] = i;
    parent[i] = temp;
  }
}

int Find(int i)
{
  int temp = i;
  for( ; parent[i] >= 0; i = parent[i])
    ;
  return i;
}
