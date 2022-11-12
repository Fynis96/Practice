#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptText(string user, string alpha);

int main(int argc, string argv[])
{
    //If there arent 2 elements in argc (name of program, and key), inform user and close program
    if (argc != 2)
    {
        printf("Usage ./substitution key\n");
        return 1;
    }
    //Assign string length of argvs 2nd element to int
    int length = strlen(argv[1]);
    //Setting second element of argv to a string for clarification and simplicity.
    string key = argv[1];
    //If there arent 26 chars in the 2nd element of argv, inform user and close program
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    //Loop through every element of argv[1] to see if there are numbers, if so inform user and close program
    for (int i = 0; i < length; i++)
    {
        if (isdigit(key[i]))
        {
            printf("Usage ./substituion key\n");
            return 1;
        }
    }
    //Create a for loop that checks through argv[1] for any duplicate chars, if so inform user and close program
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (key[i] == key[j])
            {
                count++;
            }
        }
        if (count != 1)
        {
            printf("Duplicate Chars in the key\n");
            return 1;
        }
        count = 0;
    }
    //Acquire user input, and run the encryptText function
    string userInput = get_string("plaintext: ");
    encryptText(userInput, key);
}

void encryptText(string user, string alpha)
{
    //Loop through users input
    for (int i = 0, n = strlen(user); i < n; i++)
    {
        //Take ASCII of user to acquire encrypted char, make sure original case is kept.
        if (isupper(user[i]))
        {
            int c = (user[i] - 65);
            user[i] = (toupper(alpha[c]));
        }
        else if (islower(user[i]))
        {
            int c = (user[i] - 97);
            user[i] = (tolower(alpha[c]));
        }
    }
    printf("ciphertext: %s\n", user);
}








