#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}
//Prompt User for input until the input is an integer above 0
int get_cents(void)
{
    int x;
    do
    {
        x = get_int("Change owed: ");
    }
    while (x <= 0);
    return x;
}

int calculate_quarters(int cents)
{
    //Run a check of Cents to determine how many quarters can be used
    if (cents <= 24)
    {
        return 0;
    }
    else if (cents >= 25 && cents <= 49)
    {
        return 1;
    }
    else if (cents >= 50 && cents <= 74)
    {
        return 2;
    }
    else if (cents >= 75 && cents <= 99)
    {
        return 3;
    }
    else if (cents >= 100 && cents <= 124)
    {
        return 4;
    }
    else if (cents >= 125 && cents <= 149)
    {
        return 5;
    }
    else if (cents >= 150 && cents <= 174)
    {
        return 6;
    }
    else
    {
        return 0;
    }
}

int calculate_dimes(int cents)
{
    //Run a check of Cents to determine how many dimes can be used
    if (cents <= 9)
    {
        return 0;
    }
    else if (cents >= 10 && cents <= 19)
    {
        return 1;
    }
    else if (cents >= 20 && cents <= 29)
    {
        return 2;
    }
    else if (cents >= 30 && cents <= 39)
    {
        return 3;
    }
    else if (cents >= 40 && cents <= 49)
    {
        return 4;
    }
    else if (cents >= 50 && cents <= 59)
    {
        return 5;
    }
    else if (cents >= 60 && cents <= 69)
    {
        return 6;
    }
    else if (cents >= 70 && cents <= 79)
    {
        return 7;
    }
    else if (cents >= 80 && cents <= 89)
    {
        return 8;
    }
    else if (cents >= 90 && cents <= 99)
    {
        return 9;
    }
    else if (cents >= 100 && cents <= 109)
    {
        return 10;
    }
    else
    {
        return 0;
    }
}

int calculate_nickels(int cents)
{
    //Run a check of Cents to determine how many nickels can be used
    if (cents <= 4)
    {
        return 0;
    }
    else if (cents >= 5 && cents <= 9)
    {
        return 1;
    }
    else if (cents >= 10 && cents <= 14)
    {
        return 2;
    }
    else if (cents >= 15 && cents <= 19)
    {
        return 3;
    }
    else if (cents >= 20 && cents <= 24)
    {
        return 4;
    }
    else if (cents >= 25 && cents <= 29)
    {
        return 5;
    }
    else if (cents >= 30 && cents <= 34)
    {
        return 6;
    }
    else if (cents >= 35 && cents <= 39)
    {
        return 7;
    }
    else if (cents >= 40 && cents <= 44)
    {
        return 8;
    }
    else
    {
        return 0;
    }

}

int calculate_pennies(int cents)
{
    //Run a check of Cents to determine how many pennies can be used
    if (cents <= 0)
    {
        return 0;
    }
    else if (cents > 0)
    {
        //At this point it's easy to determine whether the penny can cover the centage, as it's a one to one ratio.
        return cents;
    }
    else
    {
        return 0;
    }
}
