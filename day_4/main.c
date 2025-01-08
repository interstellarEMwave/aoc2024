#include <windows.h>
#include <stdio.h>

typedef unsigned __int64 u64;
typedef unsigned __int8 u8;

typedef __int8 smol;

#define PARSE_INT(arr,i,b) b = 0; while((u8)(arr[i] - ('0')) < (u8)10) { b = b*10 + (u8)(arr[i] - '0'); i++; }


void
takeInput(int argc, u8** argv, u8** input, int* inputSize)
{
    FILE* file = fopen(argv[1], "rb");
	int i = 0;
	PARSE_INT(argv[2], i, (*inputSize));
	(*input) = calloc((*inputSize)+1, 1);
	fread((*input), 1, (*inputSize), file);
	(*input)[(*inputSize)] = 0;
}


void
part1(u8* input, int inputSize)
{
	u64 total = 0;

	int width = 0;
	int height = 0;
	while(input[width] != '\r') width++;
	height = inputSize/(height+2);
	
	smol map[width*height] = {0};
	int c1 = 0;
	int c2 = 0;
	while(c1 < inputSize)
	{
		map[c2] = input[c1]-'1';
		c1++;
		c2++;
		if(input[c1] == '\r') c1 += 2;
	}
	
	for(int i = 0; i < width*size; i += width)
	{
		c1 = 0;
		c2 = 3;
		for(int j = 0; j < width; j++)
		{
			if(map[i+j] == c1) 
			{
				c1++;
				if(c1 == 4)
				{
					total++;
					c1 = 0;
				}
			}
			if(map[i+j] == c2)
			{
				c2--;
				if(c2 == -1)
				{
					total++;
					c2 = 3;
				}
			}
		}
	}

	for(int i = 0; i < width; i++)
	{
		c1 = 0;
		c2 = 3;
		for(int j = 0; j < height; j++)
		{
			if(map[j*width + i] == c1) 
			{
				c1++;
				if(c1 == 4)
				{
					total++;
					c1 = 0;
				}
			}
			if(map[j*width + i] == c2)
			{
				c2--;
				if(c2 == -1)
				{
					total++;
					c2 = 3;
				}
			}
		}
	}

	incr = -1;
	for(int i = 0; i
	

int
main(int argc, u8** argv)
{
	int inputSize = 0;
	u8* input = 0;
	takeInput(argc, argv, &input, &inputSize);

	part1(input, inputSize);

	return 0;
}
