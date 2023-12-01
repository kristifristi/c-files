#include <stdio.h>

int vowelcheck(char input)
{
	int isVowelBool = 0;
	char vowels[11] = { "aeiouAEIOU" };
	int index;
	for (index = 0; index < 10; ++index)
	{
		if (input == vowels[index])
		{
			isVowelBool = 1;
			break;
		}
	}
	return isVowelBool;
}

int main()
{
	char letter;
	printf("character please\n");
	scanf("%c", &letter);
	int result = vowelcheck(letter);
	if (result == 1)
	{
		printf("%c's a vowel\n", letter);
	}
	else
	{
		printf("%c's a consonant\n", letter);
	}
	return 0;
}
