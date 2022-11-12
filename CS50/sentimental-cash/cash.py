# Import necessary functions for the task from proper libraries
from cs50 import get_float
# Take float change owed from user, ensure no negative vals
while(True):
    cents = get_float("Change owed: ")
    if cents > 0.0:
        break
# create variables for change
quarter = 0.25
dime = 0.10
nickel = 0.05
penny = 0.01
quarters = 0
dimes = 0
nickels = 0
pennies = 0
# Run through the value of cents, determine how much of each coin can go into value, subtract that amount out for next coin, return coins used
if cents >= quarter:
    quarters = cents / quarter
    quarters = int(quarters)
    cents = round(cents - quarter * quarters, 2)
if cents >= dime:
    dimes = cents / dime
    dimes = int(dimes)
    cents = round(cents - dime * dimes, 2)
if cents >= nickel:
    nickels = cents / nickel
    nickels = int(nickels)
    cents = round(cents - nickel * nickels, 2)
pennies = cents / penny
pennies = int(pennies)
total = quarters + dimes + nickels + pennies

print(f"{total}")