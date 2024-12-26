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
	if(a == 0 || abs(a) > 3 || sign(a) != shouldDecr) return 1;
	else											  return 0;
}


void
part2(u8* input, int inputSize)
{
	int total = 0;
	
	int i = 0;
	while(i < inputSize)
	{
		int der[] = {0,0,0,0,0,0,0,0,0,0};
		u8 derSize = 0;
		u8 faults = 0;
		
		int prev = 0;
		int cur = 0;
		PARSE_INT(input, i, cur);
		i++;
		while(input[i] != '\n')
		{
			prev = cur;
			PARSE_INT(input, i, cur);
			i++;
			der[derSize] = cur - prev;
			derSize++;
		}

		u8 faults1 = 0;
		u8 faults2 = 0;
		u8 faults3 = 0;
		
		if(isUnsafe2(der[0], sign(der[0]))) faults1++;
		if(isUnsafe2(der[1], sign(der[0]))) faults1++;
		if(isUnsafe2(der[1], sign(der[1]))) faults2++;
		if(isUnsafe2(der[0]+der[1], sign(der[0]+der[1]))) faults3++;
		for(int j = 2; j < derSize; j++) 
		{
			if(isUnsafe2(der[j], sign(der[0]))) faults1++;
			if(isUnsafe2(der[j], sign(der[1]))) faults2++;
			if(isUnsafe2(der[j], sign(der[0]+der[1]))) faults3++;
		}
	
		u8 success = 0;
		if(!faults1 || !faults2 || !faults3) 
		{
			success = 1;
			total++;
		}
		else
		{
			u8 shouldDecr = sign(der[0]);
			for(int j = 1; j < derSize; j++)
			{
				if(isUnsafe2(der[j], shouldDecr))
				{
					if (j+1 == derSize) 
					{
						success = 1;
						total++;
					}
					else
					{
						int derAlt[] = {0,0,0,0,0,0,0,0,0,0};
						if(!isUnsafe2(der[j-1]+der[j], shouldDecr))
						{
							for(int k = j+1; k < derSize; k++) derAlt[k] = der[k];
						}
						
						der[j+1] += der[j];

						j++;
						faults1 = 0;
						faults2 = 0;
						for(; j < derSize; j++)
						{
							if(isUnsafe2(der[j], shouldDecr))	 faults1++;
							if(isUnsafe2(derAlt[j], shouldDecr)) faults2++;
						}

						if(!faults1 || !faults2) 
						{
							success = 1;
							total++;
						}
					}
				}
			}
		}

		//printf("%d

		i++;
	}

	printf("part 2: %d\n", total);
}


void
part2correct(u8* input, int inputSize)
{
	int total = 0;

	int i = 0;
	while(i < inputSize)
	{
		int report[] = {0,0,0,0,0,0,0,0,0,0};
		u8 repSize = 0;

		while(input[i] != '\n')
		{
			PARSE_INT(input, i, report[repSize]);
			i++;
			repSize++;
		}

		u8 faults = 0;
		for(int j = 1; j < repSize; j++) if(isUnsafe(report[j-1], report[j], sign(report[1]-report[0]))) faults++;
		
		u8 success = 0;
		if(faults == 0) 
		{
			success = 1;
			total++;
		}
		else
		{
			int faults1 = 0;
			int faults2 = 0;
			if(isUnsafe(report[1], report[2], sign(report[2]-report[1]))) faults1++;
			if(isUnsafe(report[0], report[2], sign(report[2]-report[0]))) faults2++;

			for(int j = 3; j < repSize; j++)
			{
				if(isUnsafe(report[j-1], report[j], sign(report[2]-report[1]))) faults1++;
				if(isUnsafe(report[j-1], report[j], sign(report[2]-report[0]))) faults2++;
			}

			if(!faults1 || !faults2) 
			{
				success = 1;
				total++;
			}
			else
			{
				u8 shouldDecr = sign(report[1]-report[0]);
				for(int k = 2; k < repSize; k++)
				{
					faults = 0;
					int t[] = {0,0,0,0,0,0,0,0,0,0};
					for(int j = 0; j < k; j++) t[j] = report[j];
					for(int j = k; j < repSize-1; j++) t[j] = report[j+1];
					for(int j = 1; j < repSize-1; j++)
					{
						if(isUnsafe(t[j-1], t[j], shouldDecr)) faults++;
					}
					if(faults == 0)
					{
						success = 1;
						total++;
						break;
					}
				}
			}
		}

		printf("%d  ", success);
		printArr(report, repSize);

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
	part2correct(input, inputSize);
	return 0;
}
