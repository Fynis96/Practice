#include <stdio.h>
#include <cs50.h>



int main(void)
{
    //Function variable to acquire users name
    string name = get_string("What's your name? \n");
    //Print to terminal name plus formatted input (string and variable for name)
    printf("Hello, %s\n", name);
}