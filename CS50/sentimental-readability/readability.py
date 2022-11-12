# Import get_string from cs50 library
from cs50 import get_string


def main():
    # Store users text input in a string
    text = get_string("Text: ")
    # Run functions to get numbers
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    L = float(letters / words * 100)
    S = float(sentences / words * 100)
    # Input values to get back Coleman Index and then print grade
    index = round(0.0588 * L - 0.296 * S - 15.8)
    index = int(index)
    print_value(index)

# Create a function to count words


def count_words(string):
    count = 1
    for i in string:
        if i.isspace():
            count += 1
    return count

# Create a function to count letters


def count_letters(string):
    count = 0
    for i in string:
        if i.isalpha():
            count += 1
    return count

# Create a function to count sentences


def count_sentences(string):
    count = 0
    for i in string:
        if i == "." or i == "?" or i == "!":
            count += 1
    return count

# Print result based on value


def print_value(index):
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


# Run Main
main()