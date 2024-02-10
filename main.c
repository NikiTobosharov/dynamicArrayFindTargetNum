#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "vector.c"

void findTheSumOfElements(Vector *array);
void freeArray(Vector *array);

int main() {
    Vector array; 

    printf("Enter the elements (type -1 to stop):\n");
    findTheSumOfElements(&array);


    freeArray(&array);
    return 0;
}

void findTheSumOfElements(Vector *array) 
{
    int num = 0;
    int target = 0;
    int found = 0;

    vectorInit(array, 1);
    while (1) 
    {
        scanf("%d", &num);
        if (num == -1) 
        {
            break;
        }

        int *newNum = malloc(sizeof(int));
        *newNum = num;
        vectorPush(array, newNum);
    }
    scanf("%d", &target);
    
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


void freeArray(Vector *array)
{
    for (int i = 0; i < vectorGetSize(array); i++) 
    {
        int *currentNum = (int *)vectorGet(array, i);
        free(currentNum); 
    }

    vectorFree(array);
}