//Name: Beginning.c
//Purpose: A simple C program that prints a famous quote to the console.
//Author: Ty Strong
//Date: 2025-11-13

#include <stdio.h>
#include <stdlib.h>
void calculateBox() 
{
    int height = 8;
    int length = 12;
    int width = 10;
    int volume = height * length * width;
    printf("Dimensions: %dx%dx%d\n", length, width, height);
    printf("Volume: %d\n", volume);
}

void customBox() 
{
    int height, length, width, volume, weight;

    // remember to pass address of the variable to scanf
    printf("Enter height: ");
    scanf("%d", &height);
    printf("Enter length: ");
    scanf("%d", &length);
    printf("Enter width: ");
    scanf("%d", &width);

    volume = height * length * width;
    weight = (volume + 165) / 166;
    
    printf("Volume (cubic inches): %d\n", volume);
    printf("Dimensional weight (pounds): %d\n", weight);

}

char* createSentence() // returns char pointer, like char array in Java, on the heap does the Java array creation run on the heap or stack???
{
    int MAX_SENTENCE_LENGTH; // max length of sentence, malloc will allocate 10 bytes, one per char
    printf("Enter the maximum length of your sentence (including spaces): ");
    scanf("%d", &MAX_SENTENCE_LENGTH); // get max length from user
    printf("Enter a sentence of %d letters:\n", MAX_SENTENCE_LENGTH - 1); // prompt user for sentence length minus null terminator
    char* sentence = malloc(MAX_SENTENCE_LENGTH); // acts similarly to new in Java creates a char array on the heap
    for(int i = 0; i < MAX_SENTENCE_LENGTH - 1; i++) // leave space for null terminator
    {
        printf("Enter letter %d: ", i + 1); // prompt user for letter 1,2,3...
        char letter;
        scanf("%c", &letter); // store letter in var
        if(letter == '@') 
        {
            break; // exit loop if user enters @
        }
        sentence[i] = letter; // store letter in sentence array
    }
    sentence[MAX_SENTENCE_LENGTH - 1] = '\0'; // null terminator to end the string
    return sentence; // return pointer to the sentence
}

int main() 
{
    float number = 42.0f;
    printf("Number: %f\n", number);
    printf("To C, or not to C, that is the question.\n");
    calculateBox();
    //customBox();

    char* sentence; // create pointer to hold sentence
    sentence = createSentence(); // call function to create sentence
    printf("%s\n", sentence); // print 
    free(sentence); // free memory from the heap

    return 0;
}


