#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int countLetters(string s);
int countWords(string s);
int countSentences(string s);

int main(void)
{
    string userInput = get_string("Text: ");
    // Store all the results of count functions as floats to handle the fun math
    float letters = countLetters(userInput);
    float words = countWords(userInput);
    float sentences = countSentences(userInput);
    // Letters per 100 words
    float L = letters / words * 100;
    // Sentences per 100 words
    float S = sentences / words * 100;
    // Plug all that fun into the Coleman-Liau index and print out based on the value.
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int countLetters(string s)
{
    int length = strlen(s);
    int letters = 0;
    //Loop through every element of an array searching for letters only, upper and lower.
    for (int i = 0; i < length; i++)
    {
        if (isalpha(s[i]))
        {
            letters += 1;
        }
    }
    return letters;
}

int countWords(string s)
{
    //Int for holding string length
    int length = strlen(s);
    int words = 0;
    //Loop through every element of an array searching for spaces and punctuation
    for (int i = 0; i < length; i++)
    {
        if (isspace(s[i]))
        {
            words += 1;
        }
        //If there is punctuation, and then a space afterwards, add one to word.
        else if ((s[i] == 33 && (s[i + 1] == 0))  || (s[i] == 46 && (s[i + 1] == 0)) || (s[i] == 63 && (s[i + 1] == 0)))
        {
            words += 1;
        }
    }
    return words;
}

int countSentences(string s)
{
    int length = strlen(s);
    int sentences = 0;
    //Loop through every element of an array searching for punctuation to end a sentence.
    for (int i = 0; i < length; i++)
    {
        if (s[i] == 33 || s[i] == 46 || s[i] == 63)
        {
            sentences += 1;
        }
    }
    return sentences;
}