# Import get_Int function from cs50 library
from cs50 import get_int
# Get user input on height, but only within certain range
while(True):
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break
# Create a loop that prints out # based on height variable, but right aligned
counterUp = 1
counterDown = height - 1
n = 0
while(n < height):
    n += 1
    print(" " * counterDown, end="")
    counterDown -= 1
    print("#" * counterUp)
    counterUp += 1