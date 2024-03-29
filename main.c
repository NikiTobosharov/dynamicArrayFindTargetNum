#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "vector.c"

void scanNumbers(Vector *array);
void findPeakElement(Vector *array);
void findTheSumOfElements(Vector *array);
void sortArrayLowToHigh(Vector *array);
void swap(void **a, void **b);
int partition(void **array, int low, int high);
void quickSort(void **array, int low, int high);
void printArray(Vector *array);
void binarySearch(Vector *array, int target);

int main() 
{
    Vector array;
    vectorInit(&array, 1);

    printf("Enter numbers (press two times Enter):\n");
    scanNumbers(&array);
    findTheSumOfElements(&array);
    findPeakElement(&array);
    printf("Before sort:\n");
    printArray(&array);
    sortArrayLowToHigh(&array);
    printf("Sorted array: \n");
    printArray(&array);

    int target;
    printf("Enter the target value to search for: ");
    scanf("%d", &target);
    printf("Search results:\n");
    binarySearch(&array, target);

    for (int i = 0; i < vectorGetSize(&array); i++)
    {
        free(vectorGet(&array, i));
    }
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

void swap(void **a, void **b) 
{
    void *temp = *a;
    *a = *b;
    *b = temp;
}

int partition(void **array, int low, int high)
{
    int pivot = *((int *) array[high]);
    int i = low - 1;

    for (int j = low; j <= high; j++)
    {
        if (*((int *)array[j]) < pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return(i + 1);   
}

void quickSort(void **array, int low, int high)
{
    if(low < high)
    {
        int pivot = partition(array, low, high);
        quickSort(array, low, pivot - 1);
        quickSort(array, pivot + 1, high);
    }
}

void sortArrayLowToHigh(Vector *array)
{
    quickSort(array->items, 0, vectorGetSize(array) - 1);
}

void printArray(Vector *array)
{
    for (int i = 0; i < vectorGetSize(array); i++) {
        int *numPtr = (int *)vectorGet(array, i);
        printf("%d ", *numPtr);
    }
    printf("\n");
}

void binarySearch(Vector *array, int target) 
{
    int low = 0;
    int high = vectorGetSize(array) - 1;
    int found = 0;

    while (low <= high) 
    {
        int mid = low + (high - low) / 2;
        int *midElement = (int *)vectorGet(array, mid);

        if (*midElement == target) 
        {
            found = 1;
            printf("Target value %d found at index %d.\n", target, mid);
            
            int left = mid - 1;
            while (left >= 0 && *((int *)vectorGet(array, left)) == target) 
            {
                printf("Target value %d found at index %d.\n", target, left);
                left--;
            }
            
            int right = mid + 1;
            while (right < vectorGetSize(array) && *((int *)vectorGet(array, right)) == target) 
            {
                printf("Target value %d found at index %d.\n", target, right);
                right++;
            }
            
            break;
        } else if (*midElement < target) 
        {
            low = mid + 1;
        } else 
        {
            high = mid - 1;
        }
    }

    if (!found) 
    {
        printf("Target value %d not found in the array.\n", target);
    }
}

