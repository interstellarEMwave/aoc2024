#include <windows.h>
#include <stdio.h>

typedef unsigned __int64 u64;
typedef unsigned __int8 u8;


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
	u8 test[] = {'m', 'u', 'l', '(', ',', ')'};

	u64 total = 0;
	int i = 0;
	while(i < inputSize)
	{
		u8 flag = 0;
		u8 j = 0;
		while(i < inputSize && input[i] != 'm') i++;
		while(i < inputSize && j < 4)
		{
			if(i == inputSize || input[i] != test[j])
			{
				flag = 1;
				break;
			}
			i++;
			j++;
		}
		if(flag) continue;

		int left = 0;
		PARSE_INT(input, i, left);
		if(left < 1 || left > 999) continue;
		
		if(i == inputSize || input[i] != test[j]) continue;
		i++;
		j++;

		int right = 0;
		PARSE_INT(input, i, right);
		if(right < 1 || right > 999) continue;
	
		if(i == inputSize || input[i] != test[j]) continue;

		total += left * right;
	}

	printf("part 1: %llu\n", total);
}

void
part2(u8* input, int inputSize)
{
	u64 total = 0;
	
	u8 mul[] = {'m', 'u', 'l', '(', ',', ')'};
	u8 donts[] = {'n', 39, 't','(', ')'};
	u8 counts = 1;

	int i = 0;
	while(i < inputSize)
	{
		u8 flag = 0;
		u8 j = 0;
		int left = 0;
		int right = 0;

		while(i < inputSize && input[i] != 'm' && input[i] != 'd') i++;
		if(input[i] == 'd')
		{
			i++;
			if(i == inputSize || input[i] != 'o') continue;
			i++;
			if(i == inputSize || (input[i] != '(' && input[i] != 'n')) continue;
			else if(input[i] == '(')
			{
				i++;
				if(i != inputSize && input[i] == ')') counts = 1;
			}
			else
			{
				while(i < inputSize && j < 5)
				{
					if(input[i] != donts[j])
					{
						flag = 1;
						break;
					}
					i++;
					j++;
				}
				if(flag) continue;
				counts = 0;
			}
		}
		else
		{
			while(i < inputSize && j < 4)
			{
				if(i == inputSize || input[i] != mul[j])
				{
					flag = 1;
					break;
				}
				i++;
				j++;
			}
			if(flag) continue;

			PARSE_INT(input, i, left);
			if(left < 1 || left > 999) continue;
			
			if(i == inputSize || input[i] != mul[j]) continue;
			i++;
			j++;

			PARSE_INT(input, i, right);
			if(right < 1 || right > 999) continue;
		
			if(i == inputSize || input[i] != mul[j]) continue;
		}

		if(counts) total += left * right;
	}

	printf("part 2: %llu\n", total);
}

int
main(int argc, u8** argv)
{
	int inputSize = 0;
	u8* input = 0;
	takeInput(argc, argv, &input, &inputSize);
	
	part1(input, inputSize);
	part2(input, inputSize);

	return 0;
}
