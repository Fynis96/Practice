# Only import the get_string function from cs50 library
from cs50 import get_string
# Set get_strings return to name variable
name = get_string("What is your name? ")
# Print aforementioned name variable using a formatted string print
print(f"Hello, {name}")