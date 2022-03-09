#include <stdio.h>
#include <string.h>
#define MAX_STRING_LENGTH 10000000
#define MAX_PATTERN_LENGTH 3000

char string[MAX_STRING_LENGTH];
char pattern[MAX_PATTERN_LENGTH];

int appr = 0;
int pos[MAX_STRING_LENGTH] = {0, };

void naiveMatching();
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
	//입력값 받아오기
	naiveMatching();
	//패턴매칭함수
	FILE* fpresult;
	fpresult = fopen("result_naive.txt", "w");
	fprintf(fpresult, "%d\n", appr);
	for(int i = 0; i < appr; i++)
	{
		fprintf(fpresult, "%d ", pos[i]);
	}
	fprintf(fpresult, "\n");
	//출력파일 생성 및 출력값 입력
	printf("Program complete. Result saved to result_naive.txt\n");
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

void naiveMatching()
{
	int i, j, start = 0;
	int laststr = strlen(string) - 1;
	int lastpat = strlen(pattern) - 1;
	int end = lastpat;

	for(i = 0; end <= laststr; end++, start++)
	{
		if(string[end] == pattern[lastpat])	//마지막 글자 일치 여부에 따라 다음 단계 진행
		{
			for(j = 0, i = start; j < lastpat && string[i] == pattern[j]; i++, j++) ;
		}
		if(j == lastpat)
		{
			pos[appr++] = start;	//발견된 위치 저장하고 발견 횟수 증가
		}
		j = 0;
	}
}