/*
Michael Ha
ICS 365-50
Professor Carlson
01/15/2022

-- Quick sort was based on pseudocode from https://www.geeksforgeeks.org/quick-sort/ --
*/

#include <stdio.h>
int main()
{
    // instantiate the array for data entry
    const int SIZE = 100;
    int data[SIZE];
    // run(data, SIZE);
    getSize();
    return 0;
}

// runs the program
void run(int array[], const int size)
{
    // enters the data into an array. If there is no data in the txt file, then the program will abort
    enterData(array, size, "data.txt");

    // checks if the array is sorted or not. returns 1 which means it is sorted
    if (checkArray(array, size) == 1)
    {
        printf("\n");
    }
    // else the array is sorted and then written into sorted.txt
    else
    {
        quickSort(array, 0, size - 1);
        writeFile(array, size, "sorted.txt");
    }
}

// sorts the list from smallest to biggest
void quickSort(int array[], int startIndex, int endIndex)
{
    if (endIndex <= startIndex)
        return;

    // moves the pivot value to the correct spot
    int pivotIndex = partition(array, startIndex, endIndex);

    // sorts both sides of the pivot index from smallest to biggest
    quickSort(array, startIndex, pivotIndex - 1);
    quickSort(array, pivotIndex + 1, endIndex);
}

int partition(int array[], int startIndex, int endIndex)
{
    // setting the pivot value to the last value in the array for movement
    int pivot = array[endIndex];
    int i = startIndex - 1;

    int x;
    for (int x = startIndex; x <= endIndex - 1; x++)
    {
        // if the value at x is smaller than pivot then swap the two values and increment i
        if (array[x] < pivot)
        {
            i++;
            swapIndex(i, x, array);
        }
    }
    // at this point, the end of the array should have the smallest value, so theyre swapped
    i++;
    swapIndex(i, endIndex, array);

    return i;
}

// basic array swap algorithm with temp variable
swapIndex(int original, int swapped, int array[])
{
    int temp = array[original];
    array[original] = array[swapped];
    array[swapped] = temp;
}

int getSize()
{
    int count;
    int c;
    char *filename;
    getName(filename);
    FILE *file = fopen(filename, "r");

    for (c = getc(file); c != EOF; c = getc(file))
    {
        if (c == '\n')
        {
            count = count + 1;
        }
    }
    printf("Count: %d", count);
    fclose(file);
    return count;
}

void getName(char *fileName)
{
    printf("\nEnter the name of your file: \n");
    scanf("%c", &fileName);
}

void readFile(int array[], const int size, char *filename)
{
    getName(filename);
    // reads specified file in the method constructor
    FILE *filePointer;
    filePointer = fopen(filename, "r");
    int i;

    // loops through size of array and puts the data into the array
    for (i = 0; i < size; i++)
    {
        fscanf(filePointer, "%d", &array[i]);
    }
    fclose(filePointer);

    // closes the file after its done looping
}

// Writes and creates a new file with the sorted integers
void writeFile(int array[], const int size, char *filename)
{
    // basically the same as readFile method, but with fprintf to write into a new file
    FILE *filePointer;
    // writes the array into a text file and overrides any old values inside
    filePointer = fopen(filename, "w+");
    int i;

    for (i = 0; i < size; i++)
    {
        fprintf(filePointer, "%d\n", array[i]);
    }
    fclose(filePointer);
}

// handy method for printing out the array
int printArray(int array[], const int size)
{
    printf("\nPrinting array:\n");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d\n", array[i]);
    }
}

// Checks input file for errors (empty/non-existent files, already sorted data, etc.)
int checkFile(char *fileName)
{
    FILE *filePointer;
    filePointer = fopen(fileName, "r");
    // if file is not null, then it'll check if the file is empty
    if (filePointer != NULL)
    {
        // seeks to the end of the file and returns the size
        fseek(filePointer, 0, SEEK_END);
        int size = ftell(filePointer);

        // if size is 0 then the process aborts and gives user feedback
        if (size == 0)
        {
            // returns 0 if the file is empty which means false
            printf("The file is empty\n");
            abort();
            return 0;
        }
        else
        {
            // else it returns 1 and gives user feedback
            printf("File is not empty\n");
            return 1;
        }
    }
    // else the file simply does not exist and aborts with user feedback
    else
    {
        printf("The file does not exist\n");
        abort();
    }
}

// checks if array is sorted already
int checkArray(int array[], const int size)
{
    int i;
    for (i = 0; i < size - 1; i++)
    {
        // return 0 if array is not sorted, breaks out of loop if it finds an unsorted value
        if (array[i] > array[i + 1])
        {
            return 0;
            break;
        }
        else
        {
            // simply gives user feedback if its sorted
            printf("array is sorted\n");
            return 1;
        }
    }
}

// used to populate array with one simple method
void enterData(int array[], const int size, char *filename)
{
    if (checkFile(filename) == 1)
    {
        readFile(array, size, filename);
        // printArray(array, size);
    }
}
