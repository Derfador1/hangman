#include <stdio.h>
#include <string.h>



int main(int argc, char * argv[])
{

	if (argc == 1)
	{
		//begins like normal
	}
	else if (argc == 2)
	{
		if (strncmp(argv[1], "-h", 10) == 0) //checks if the strings are equal
		{
			printf("Rule: \n");
		}
	}

	char *dictionary[] = {"WORD", "COW", "CHEESE", "POOP", "FALSE"};

	for (int c = 0; c < 5; c++)
		printf("%s\n", dictionary[c]);

}
