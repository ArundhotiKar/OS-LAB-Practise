#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Function to reverse a string */
void reverseString(char str[])
{
    int len = strlen(str);

    printf("Reversed string: ");

    for (int i = len - 1; i >= 0; i--)
    {
        printf("%c", str[i]);
    }

    printf("\n");
}

/* Function to count vowels and consonants */
void countVC(char str[])
{
    int vowels = 0, consonants = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = tolower(str[i]);

        if (isalpha(ch))
        {
            if (ch == 'a' || ch == 'e' || ch == 'i' ||
                ch == 'o' || ch == 'u')
            {
                vowels++;
            }
            else
            {
                consonants++;
            }
        }
    }

    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
}

/* Function for arithmetic operations */
void arithmetic(char op[], int a, int b)
{
    if (strcmp(op, "add") == 0)
    {
        printf("Addition: %d\n", a + b);
    }
    else if (strcmp(op, "mul") == 0)
    {
        printf("Multiplication: %d\n", a * b);
    }
    else
    {
        printf("Invalid arithmetic operation!\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage:\n");
        printf("  %s reverse <string>\n", argv[0]);
        printf("  %s count <string>\n", argv[0]);
        printf("  %s add <num1> <num2>\n", argv[0]);
        printf("  %s mul <num1> <num2>\n", argv[0]);
        return 1;
    }

    /* Reverse string */
    if (strcmp(argv[1], "reverse") == 0)
    {
        reverseString(argv[2]);
    }

    /* Count vowels and consonants */
    else if (strcmp(argv[1], "count") == 0)
    {
        countVC(argv[2]);
    }

    /* Arithmetic operations */
    else if (strcmp(argv[1], "add") == 0 ||
             strcmp(argv[1], "mul") == 0)
    {
        if (argc != 4)
        {
            printf("Please provide two numbers.\n");
            return 1;
        }

        int a = atoi(argv[2]);
        int b = atoi(argv[3]);

        arithmetic(argv[1], a, b);
    }

    else
    {
        printf("Invalid command.\n");
    }

    return 0;
}