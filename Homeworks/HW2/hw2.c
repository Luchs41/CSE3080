#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 1000001

int maxHeap[MAX_SIZE];
int minHeap[MAX_SIZE];
int printHeap[MAX_SIZE];
int n = 0;
int data;




void insertHeap(int item);
void printMinHeap();
int findMin(int *n);
void printMaxHeap();
int findMax();
void printtest();

int main(int argNum, char **argName)
{
  
  if(argNum != 2)
  {
    printf("usage: ./hw2 input_filename\n");
    return -1;
  }
  //Command line Error
  FILE* fpInput = fopen(argName[1], "r");
  if(!fpInput)
  {
    printf("The input file does not exist.\n");
    return -1;
  }
  //File open Error
  FILE* fpOutput;
  fpOutput = fopen("hw2_result.txt", "w");
  fclose(fpOutput);
  //Output File generate

  char input[20];
  char *command;
  
  command = (char*)malloc(sizeof(char) * 20);

  double start = clock(); //Start time check
  while(!feof(fpInput))
  {
    input[1] = 0;
    fgets(input, 19, fpInput);
    command = strtok(input, "\n");
    command = strtok(input, " ");
    
    
    if(!strcmp(command, "INSERT"))
    {
      command = strtok(NULL, " ");
      if(command)
      {
        data = atoi(command);
        insertHeap(data);
      }
      
    }
    else if(!strcmp(command, "ASCEND"))
    {
      for(int k = 0; k <= n; k++)
      {
        printHeap[k] = minHeap[k];
      }
      printMinHeap();
    }
    else if(!strcmp(command, "DESCEND"))
    {
      for(int k = 0; k <= n; k++)
      {
        printHeap[k] = maxHeap[k];
      }
      printMaxHeap();
    }
  }

  double end = clock(); //End time check
  printf("output written to hw2_result.txt\nrunning time: %.6f seconds\n", (end - start)/CLOCKS_PER_SEC);

}

void insertHeap(int data)
{
  if(n >= MAX_SIZE - 1)
  {
    printf("Error : Heap is FULL\n");
    return ;
  }
  n += 1;
  int i = n;
  while((i != 1) && (data > maxHeap[i / 2]))
  {
    maxHeap[i] = maxHeap[i / 2];
    i /= 2;
  }
  maxHeap[i] = data;
  
  i = n;
  while((i != 1) && (data < minHeap[i / 2]))
  {
    minHeap[i] = minHeap[i / 2];
    i /= 2;
  }
  
  minHeap[i] = data;
}
/////////////////////////Min Heap Print/////////////////////////////
void printMinHeap()
{
  if(n == 0)
  {
    printf("Error : Heap is EMPRY\n");
    return ;
  }
  FILE *fpout = fopen("hw2_result.txt", "a");
  int found;
  int tempN = n;
  for(int i = 0; i < n; i++)
  {
    found = findMin(&tempN);
    fprintf(fpout, "%d ", found);
  }
  fprintf(fpout, "\n");
  fclose(fpout);
}

int findMin(int *n)
{
  int parent, child, item, temp;
  item = printHeap[1];
  temp = printHeap[(*n)--];
  parent = 1;
  child = 2;
  while(child <= *n)
  {
    if((child < *n) && (printHeap[child] > printHeap[child + 1])) child++;
    if(temp <= printHeap[child]) break;
    printHeap[parent] = printHeap[child];
    parent = child;
    child *= 2;
  }
  printHeap[parent] = temp;
  return item;
}
//////////////////////Max Heap Print/////////////////////
void printMaxHeap()
{
  if(n == 0)
  {
    printf("Error : Heap is EMPRY\n");
    return ;
  }
  FILE *fpout = fopen("hw2_result.txt", "a");
  int found;
  int tempN = n;
  for(int i = 0; i < n; i++)
  {
    found = findMax(&tempN);
    fprintf(fpout, "%d ", found);
  }
  fprintf(fpout, "\n");
  fclose(fpout);
}

int findMax(int *n)
{
  int parent, child, item, temp;
  item = printHeap[1];
  temp = printHeap[(*n)--];
  parent = 1;
  child = 2;
  while(child <= *n)
  {
    if((child < *n) && (printHeap[child] < printHeap[child + 1])) child++;
    if(temp >= printHeap[child]) break;
    printHeap[parent] = printHeap[child];
    parent = child;
    child *= 2;
  }
  printHeap[parent] = temp;
  return item;
}
