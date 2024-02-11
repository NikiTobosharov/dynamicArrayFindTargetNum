#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "vector.c"

void scanNumbers(Vector *array);
void findPeakElement(Vector *array);
void findTheSumOfElements(Vector *array);

int main() 
{
    Vector array;
    vectorInit(&array, 1);

    printf("Enter numbers (press two times Enter):\n");
    scanNumbers(&array);
    findTheSumOfElements(&array);
    findPeakElement(&array);

    vectorFree(&array);
    return 0;
}

void scanNumbers(Vector *array) 
{
    char input[100];
    char *token;

    while (true) 
    {
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n' || input[0] == ' ')
        break;

        token = strtok(input, " \n");
        while (token != NULL) 
        {
            int num = atoi(token);
            int *ptr = malloc(sizeof(int));
            if (ptr == NULL) 
            {
                printf("Memory allocation failed. Exiting.\n");
                exit(EXIT_FAILURE);
            }

            *ptr = num;
            vectorPush(array, ptr);
            token = strtok(NULL, " \n");
        }
    }
}

void findPeakElement(Vector *array)
{
    for (int i = 0; i < vectorGetSize(array); i++)
    {
        int *previous = (i > 0) ? vectorGet(array, i - 1) : NULL;
        int *current = vectorGet(array, i);
        int *next = (i < vectorGetSize(array) - 1) ? vectorGet(array, i + 1) : NULL;

        if (current == NULL)
        {
            continue;
        }

        if ((previous == NULL || *current > *previous) && (next == NULL || *current > *next))
        {
            printf("%d is a peak element.\n", *current);
        }
    }
}

void findTheSumOfElements(Vector *array)
{
    char input[100];
    int target = 0;
    int found = 0;

    printf("Enter the target sum:\n");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &target);

    for (int i = 0; i < vectorGetSize(array); i++)
    {
        int *firstNumPtr = (int *)vectorGet(array, i);
        for (int j = i + 1; j < vectorGetSize(array); j++)
        {
            int *secondNumPtr = (int *)vectorGet(array, j);
            if ((*firstNumPtr + *secondNumPtr) == target)
            {
                if (!found)
                {
                    printf("The combinations are: \n");
                }
                
                int *currentFirstNum = (int *)vectorGet(array, i);
                int *currentSecondNum = (int *)vectorGet(array, j);
                
                printf("First number: %d at index: %d and second number: %d at index %d",
                *currentFirstNum, i, *currentSecondNum, j);
                printf("\n");
                found = 1;
                
            }
        }   
    }
    if (!found)
    {
        printf("No such a combination.\n");
    }
}
