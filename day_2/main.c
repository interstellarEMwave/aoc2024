#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned __int8 u8;
typedef unsigned __int64 u64;

#define INPUT ;\
    FILE* file = fopen(argv[1], "rb");\
	int inputSize = 0;\
	int ___i = 0;\
	PARSE_INT(argv[2], ___i, inputSize);\
	u8* input = calloc(inputSize+1, 1);\
	fread(input, 1, inputSize, file);\
	input[inputSize] = 0

#define CRASH(a) assert((a,0))
#define SWAP(a,b) if(&a != &b) {a^=b; b^=a; a^=b;}
#define PARSE_INT(arr,i,b) b = 0; while((u8)(arr[i] - ('0')) < 10) { b = b*10 + (u8)(arr[i] - '0'); i++; }

void
part1(u8* input, int inputSize)
{
	u64 total = 0;
	int lastNum = 0;
	int curNum = 0;
	int decr = 0;

	int i = 0;
	while(i < inputSize)
	{
		int flag = 0;
		int lastNum = 0;
		int curNum = 0;
		PARSE_INT(input, i, lastNum);
		if(input[i] == '\n') 
		{
			total++;
			i++;
			continue;
		}
		int t = i+1;
		PARSE_INT(input, t, curNum);
		decr = ((unsigned int)(curNum-lastNum))>>31;

		while(input[i] != '\n')
		{
			i++;
			curNum = 0;
			PARSE_INT(input, i, curNum);
			
			if(curNum == lastNum
			|| abs(curNum-lastNum) > 3
			|| (((unsigned int)(curNum-lastNum))>>31) != decr)
			{
				while(input[i] != '\n') i++;
				flag = 1;
				break;
			}

			lastNum = curNum;
		}

		if(!flag) total++;
		i++;
	}

	printf("Part 1: %llu\n", total);
}

int unsafe(int a, int b, unsigned int shouldDecr) { return (a == b || abs(a-b) > 3 || (((unsigned int)(b-a))>>31) != shouldDecr); }

void
part2(u8* input, int inputSize)
{
	int total = 0;
	int window[] = {0,0,0,0};
	int shouldDecr = 0;

	int i = 0;
	while(i < inputSize)
	{
		int j = 0;
		int hasRemoved = 0;
		int flag = 0;
		int shouldDecr = 0;

		PARSE_INT(input, i, window[0]);
		i++;
		j++;
		PARSE_INT(input, i, window[1]);
		int t = i + 1;
		j++;
		PARSE_INT(input, t, window[2]);
		t++;
		j++;
		PARSE_INT(input, t, window[3]);
		
		shouldDecr = ((unsigned int)(window[1]-window[0]))>>31;
		
		int wind[] = {unsafe(window[0], window[1], (((unsigned int)(window[1]-window[0]))>>31)), //normal 0 and 1
					  unsafe(window[1], window[2], (((unsigned int)(window[1]-window[0]))>>31)), //normal 1 and 2
					  unsafe(window[2], window[3], (((unsigned int)(window[1]-window[0]))>>31)), //normal 2 and 3
					  unsafe(window[1], window[2], (((unsigned int)(window[2]-window[1]))>>31)), //if 0 removed
					  unsafe(window[0], window[2], (((unsigned int)(window[2]-window[0]))>>31)), //if 1 removed
					  unsafe(window[2], window[3], (((unsigned int)(window[2]-window[0]))>>31)), //if 1 removed
					  unsafe(window[2], window[3], (((unsigned int)(window[2]-window[1]))>>31))}; //if 0 removed
		for(int k = 0; k < 7; k++)
		{
			if(wind[k]) printf("%d\n", k);
		}

		if(wind[0])
		{
			if(!wind[4] && !wind[5])
			{
				shouldDecr = (((unsigned int)(window[2]-window[0]))>>31);
				j--;
				hasRemoved = 1;
			}
			else if(!wind[3] && !wind[6])
			{
				shouldDecr = (((unsigned int)(window[2]-window[1]))>>31);
				hasRemoved = 1;
			}
			else 
			{
				printf("	unsafe1\n");
				while(input[i] != '\n') i++;
				flag = 1;
			}
		}
		else if(wind[1])
		{
			if(!wind[4] && !wind[5])
			{
				j--;
				shouldDecr = (((unsigned int)(window[2]-window[0]))>>31);
				hasRemoved = 1;
			}
			else 
			{
				printf("	unsafe2\n");
				while(input[i] != '\n') i++;
				flag = 1;
			}
		}

		j -= 2;
		while(input[i] != '\n' && i < inputSize)
		{
			i++;
			j++;

			PARSE_INT(input, i, window[j%4]);
			

			if(unsafe(window[(j-1)%4], window[j%4], shouldDecr))
			{
				printf("%d %d\n", window[(j-1)%4], window[j%4]);
				if(hasRemoved)
				{
					printf("	unsafe3\n");
					while(input[i] != '\n' && i < inputSize) i++;
					flag = 1;
					break;
				}

				int next = 0;
				t = i+1;
				if(input[i] != '\n')
				{
					PARSE_INT(input, t, next);
				}
				else break;	


				
				if(j>1 && !unsafe(window[(j-2)%4], window[j%4], shouldDecr) && !unsafe(window[j%4], next, shouldDecr))
				{
					window[(j-1)%4] = window[j%4];
					j--;
					hasRemoved = 1;
				}
				else if(!unsafe(window[(j-1)%4], next, shouldDecr))
				{
					j--;
					hasRemoved = 1;
				}
				else
				{
					printf("	unsafe4\n");
					while(input[i] != '\n' && i < inputSize) i++;
					flag = 1;
					break;
				}
			}
		}
		
		if(!flag) total++;
		//printf("\n");	
		i++;
	}

	printf("part 2: %d\n", total);
}


int
main(int argc, u8** argv)
{
	INPUT;
	for(int i = 0; i < 30; i++) printf("%d ", input[i]);
	printf("\n");
	part1(input, inputSize);
	part2(input, inputSize);

	return 0;
}
