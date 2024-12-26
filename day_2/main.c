#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned __int8 u8;
typedef unsigned __int64 u64;

/*
#define INPUT ;\
    FILE* file = fopen(argv[1], "rb");\
	int inputSize = 0;\
	int ___i = 0;\
	PARSE_INT(argv[2], ___i, inputSize);\
	u8* input = calloc(inputSize+1, 1);\
	fread(input, 1, inputSize, file);\
	input[inputSize] = 0
*/
#define CRASH(a) assert((a,0))
#define SWAP(a,b) if(&a != &b) {a^=b; b^=a; a^=b;}
#define PARSE_INT(arr,i,b) b = 0; while((u8)(arr[i] - ('0')) < 10) { b = b*10 + (u8)(arr[i] - '0'); i++; }
void
INPUT(int argc, u8** argv, u8** input, int* inputSize)
{
    FILE* file = fopen(argv[1], "rb");
	int i = 0;
	PARSE_INT(argv[2], i, (*inputSize));
	(*input) = calloc((*inputSize)+1, 1);
	fread((*input), 1, (*inputSize), file);
	(*input)[(*inputSize)] = 0;
}


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
	int expected = 1;
	if(shouldDecr) expected = -3;
	
	if(a < expected)	 return -1;
	if(a > expected + 2) return 1;
	else                 return 0;
}


void
part2(u8* input, int inputSize)
{
	int total = 0;
	
	int i = 0;
	while(i < inputSize)
	{
		int der[10] = {0};
		u8 derSize = 0;
	
		int prev = 0;
		int cur = 0;
		PARSE_INT(input, i, cur);
		i++;

		while(input[i] != '\n')
		{
			prev = cur;
			PARSE_INT(input, i, cur);
			i++;	
			der[derSize] = cur-prev;
			derSize++;
		}

		int avg = 0;
		for(int j = 0; j < derSize; j++) avg += 1 - 2*sign(der[j]);
		u8 sd = sign(avg);

		u8 hasRemoved = 0;
		u8 s = 1;
		if(isUnsafe2(der[0], sd) && !isUnsafe2(der[1], sd)) hasRemoved = 1;
		else if(isUnsafe2(der[0], sd))
		{
			hasRemoved = 1;
			der[1] += der[0];
		}

		for(int j = 1; j < derSize; j++)
		{
			if(isUnsafe2(der[j], sd))
			{
				if(hasRemoved)
				{
					s = 0;
					break;
				}
				else if(j + 1 != derSize)
				{
					hasRemoved = 1;
					if(isUnsafe2(der[j-1]+der[j], sd)) der[j+1] += der[j];
				}
			}
		}

		total += s;
		i++;
	}

	printf("part 2: %d\n", total);
}

int
main(int argc, u8** argv)
{
	u8* input = 0;
	int inputSize = 0;
	INPUT(argc, argv, &input, &inputSize);
	part1(input, inputSize);
	part2(input, inputSize);
	return 0;
}
