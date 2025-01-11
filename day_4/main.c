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


u8
wordSearch(smol* map, int width, int height, int i, int mult, int add)
{
	u8 a = 1;
	for(int j = 1; j < 4; j++) if(map[i+j*mult+add]) a = 0;
	return a;
}


void
part1(u8* input, int inputSize)
{
	u64 total = 0;

	int width = 0;
	int height = 0;
	while(input[width] != '\r') width++;
	height = inputSize/(height+2);
	
	smol* map = calloc(width*height, 1);
	int c1 = 0;
	int c2 = 0;
	while(c1 < inputSize)
	{
		map[c2] = input[c1]-'0';
		c1++;
		c2++;
		if(input[c1] == '\r') c1 += 2;
	}
	
	for(int i = 0; i < width*height; i++)
	{
		if(map[i] == 1)
		{
			int h = i/width;
			int w = i%width; 
			if(w > 2)						total += wordSearch(map, width, height, i,	  -1,  0);
			if(h > 2)						total += wordSearch(map, width, height, i, -width,  0);
			if(w > width-4)					total += wordSearch(map, width, height, i,	   1,  0);
			if(w > height-4)				total += wordSearch(map, width, height, i,  width,  0);
			if(w > 2 && h > 2)				total += wordSearch(map, width, height, i, -width, -1);
			if(w > 2 && h < height-4)		total += wordSearch(map, width, height, i,  width, -1);
			if(w < width-4 && h > 2)		total += wordSearch(map, width, height, i, -width,  1);
			if(w < width-4 && h < height-4) total += wordSearch(map, width, height, i,  width,  1);
		}
	}
	
	printf("part 1: %llu", total);
}
	

int
main(int argc, u8** argv)
{
	int inputSize = 0;
	u8* input = 0;
	takeInput(argc, argv, &input, &inputSize);

	part1(input, inputSize);

	return 0;
}
