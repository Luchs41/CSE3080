#include <stdio.h>
#include <string.h>
#define MAX_STRING_LENGTH 10000000
#define MAX_PATTERN_LENGTH 3000

char string[MAX_STRING_LENGTH];
char pattern[MAX_PATTERN_LENGTH];
int failure[MAX_PATTERN_LENGTH];

int appr = 0;
int pos[MAX_STRING_LENGTH] = {0, };

void kmp();
void failGen();
int fileOpenError(FILE*, FILE*);

int main()
{
  FILE* fpstr;
  fpstr = fopen("string.txt", "r");
	FILE* fppat;
	fppat = fopen("pattern.txt", "r");

  if(!fileOpenError(fpstr, fppat))
		return -1;
	//input file 열고 open error 시 프로그램 종료

  fgets(string, MAX_STRING_LENGTH, fpstr);
  fgets(pattern, MAX_PATTERN_LENGTH, fppat);
  
  failGen();
  kmp();
  
  
  FILE* fpresult;
  fpresult = fopen("result_kmp.txt", "w");
  fprintf(fpresult, "%d\n", appr);
  for(int i = 0; i < appr; i++)
  {
    fprintf(fpresult, "%d ", pos[i]);
  }
  fprintf(fpresult, "\n");
  //출력파일 생성 및 출력값 입력
  printf("Program complete. Result saved to result_kmp.txt\n");
  fclose(fpstr);
  fclose(fppat);
  fclose(fpresult);
  //파일포인터 닫고 프로그램 종료
  return 0;
}

int fileOpenError(FILE* fpstr, FILE* fppat)
{
	if(fpstr == NULL)
	{
		printf("The string file does not exist. \n");
		return 0;
	}
	if(fppat == NULL)
	{
		printf("The pattern file does not exist. \n");
		return 0;
	}
	else
		return 1;
}

void failGen()
{
  int i;
  int patlen = strlen(pattern);
  failure[0] = -1;
  for(int j = 1; j < patlen; j++)
  {
    i = failure[j - 1];
    while(pattern[j] != pattern[i + 1] && (i >= 0)) 
      i = failure[i];

    if(pattern[j] == pattern[i + 1])
      failure[j] = i + 1;
    else
      failure[j] = -1;
  }
}

void kmp()
{
  int i = 0;
  int j = 0;

  int lenstr = strlen(string);
  int lenpat = strlen(pattern);

  while(i < lenstr)
  {
    if(string[i] == pattern[j])
    {
      i++;
      j++;
    }
    else if(j == 0)
      i++;
    else  j = failure[j - 1] + 1;
    if(j == lenpat)
    {
      pos[appr++] = i - lenpat;
      j = failure[j - 1] + 1;
    }
  }
}