#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned __int8 u8;
typedef unsigned __int64 u64;

#define INPUT int ___i = 0;\
			int inputSize = 0;\
			parseInt(argv[1], &___i, inputSize);\
			u8* input = (u8*)malloc(inputSize+1);\
			fread(input, sizeof(u8), inputSize, stdin);\
			input[inputSize] = 0
#define CRASH(a) assert((a,0))
#define SWAP(a,b) if(&a != &b) {a^=b; b^=a; a^=b;}
#define parseInt(arr,i,b) while((u8)(arr[*i] - ('0')) < 10) { b = b*10 + (u8)(arr[*i] - '0'); (*i)++; }


void
printArr(int* arr, int start, int end)
{
	for(int i = start; i < end; i++) printf("%d ", arr[i]);
	printf("\n");
}

void sort(int* arr, int start, int end)
{
	if(start >= end) return;

	int p = rand()%(end-start) + start;
	SWAP(arr[end-1], arr[p]);

	int left = start;
	int right = end-2;
	while(left <= right)
	{
		while(arr[left] <= arr[end-1] && left <= right) left++; while(arr[right] > arr[end-1] && left <= right) right--;
		
		if(left <= right) SWAP(arr[left], arr[right]);
	}

	SWAP(arr[left], arr[end-1]);

	sort(arr, start, left);
	sort(arr, left+1, end);
}


void
part1(int* arr1, int* arr2, int length)
{
	sort(arr1, 0, length);
	sort(arr2, 0, length);
	
	u64 total = 0; 
	for(int i = 0; i < length; i++)
	{
		total += abs(arr1[i] - arr2[i]);
	}

	printf("Part 1: %llu\n", total);
}


void
part2(int* arr1, int* arr2, int length)
{
	int arr1c = 0;
	int arr2c = 0;

	u64 total = 0;

	while(arr1c < length)
	{
		int t = arr1[arr1c];
		int b = 0;
		int c = 0;

		while(arr2[arr2c] < t) 
		{
			arr2c++;
		}
	
		while(arr2[arr2c] == t && arr2c < length) 
		{
			b++;
			arr2c++;
		}
		
		while(arr1[arr1c] == t) 
		{
			c++;
			arr1c++;
		}
	
		total += c*b*t;
	}
				
	printf("Part 2: %llu\n", total);
}
int
main(int argc, u8** argv)
{
	INPUT;
	int length = 0;
	for(int i = 0; i < inputSize; i++) if(input[i] == '\n') length++;
	
	int* arr1 = calloc(length, sizeof(int));
	int* arr2 = calloc(length, sizeof(int));
	
	int i = 0;
	int l = 0;
	while(i < inputSize)
	{
		parseInt(input, &i, arr1[l]);
		i += 3;
		parseInt(input, &i, arr2[l]);
		l++;
		i++;
	}

	part1(arr1, arr2, length);	
	part2(arr1, arr2, length);	

	return 0;
}

