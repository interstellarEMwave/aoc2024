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

int 
sign(int a)
{
	if(a < 0) return 1;
	else return 0;
}


void
printArr(int* arr, int length)
{
	for(int i = 0; i < length; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}


int
isUnsafe(int prev, int cur, u8 shouldDecr)
{
	int expected = prev + 1;
	if(shouldDecr) expected = prev - 3;

	if(cur < expected)			return 1;
	else if(cur > expected + 2) return 2;
	else						return 0;
}


void
part1(u8* input, int inputSize)
{
	int total = 0;

	int prev = 0;
	int cur = 0;
	int shouldDecr = 0;
	int i = 0;
	while(i < inputSize)
	{
		PARSE_INT(input,i,prev);
		i++;
		PARSE_INT(input,i,cur);
		i++;
		shouldDecr = sign(cur-prev);
		
		if(isUnsafe(prev, cur, shouldDecr))
		{
			while(input[i] != '\n') i++;
			i++;
			continue;
		}


		while(input[i] != '\n')
		{
			prev = cur;
			PARSE_INT(input, i, cur);
			
			if(isUnsafe(prev, cur, shouldDecr))
			{
				while(input[i] != '\r') i++;
				break;
			}
			i++;
		}

		if(input[i] == '\r') i++;
		else total++;

		i++;
	}

	printf("part 1: %d\n", total);
}


int
isUnsafe2(int a, u8 shouldDecr)
{
	if(a == 0 || abs(a) > 3 || sign(a) != shouldDecr) return 1;
	else											  return 0;
}


u8
helper(int* der, u8 start, u8 end, u8 shouldDecr, u8 hasRemoved)
{
	for(int j = start; j < end; j++)
	{
		printf("	%d\n", der[j]);
		if(isUnsafe2(der[j], shouldDecr))
		{
			if(hasRemoved)		return 0;
			else if(j+1 == end) return 1;
			else
			{
				printf("		%d\n", der[j-1]+der[j]);
				printf("		%d\n", der[j]+der[j+1]);
				if(!isUnsafe2(der[j-1] + der[j], shouldDecr)
				|| !isUnsafe2(der[j] + der[j+1], shouldDecr))
				{
					u8 a = helper(der, j+1, end, shouldDecr, 1);
					der[j+1] += der[j];
					u8 b = helper(der, j+1, end, shouldDecr, 1);

					if(a || b) return 1;
				}
				else return 0;
			}
		}
	}

	return 1;
}


void
part2(u8* input, int inputSize)
{
	int total = 0;
	
	int i = 0;
	while(i < inputSize)
	{
		int report[] = {0,0,0,0,0,0,0,0,0,0};
		u8 repSize = 0;

		int a = 0;
		while(input[i] != '\n')
		{
			PARSE_INT(input, i, report[repSize]);
			i++;
			repSize++;
		}
		
		u8 faults = 0;
		for(int j = 1; j < repSize; j++) 
		{
			if(isUnsafe(report[j-1], report[j], sign(report[1]-report[0]))) faults++;
		}
		//printf("\n");
		
		u8 safe = 0;
		if(faults == 0) 
		{
			safe = 1;
			total++;
		}
		else
		{
			for(int k = 0; k < repSize; k++)
			{
				int t[] = {0,0,0,0,0,0,0,0,0,0};
				for(int j = 0; j < k; j++) t[j] = report[j];
				for(int j = k+1; j < repSize; j++) t[j-1] = report[j];
				u8 shouldDecr = sign(t[1]-t[0]);

				u8 f = 0;
				for(int j = 1; j < repSize-1; j++)
				{
					if(isUnsafe(t[j-1], t[j], shouldDecr)) 
					{
						//printf("	%d %d %d\n", t[j-1], t[j], shouldDecr);
						f++;
						break;
					}
				}
				//printf("%d  ", f);
				if(f == 0) 
				{
					safe = 1;
					total++;
					break;
				}
			}
		}
		printf("%d ", safe);
		printArr(report, repSize);

		i++;
	}

	printf("part 2: %d\n", total);
}


int
main(int argc, u8** argv)
{
	INPUT;
	part1(input, inputSize);
	part2(input, inputSize);
	return 0;
}
