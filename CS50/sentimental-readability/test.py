from cs50 import get_string

text = get_string("Text: ")

words = 1
letters = 0
sentences = 0

for char in text:
    if char.isalpha():
        letters += 1
    if char.isspace():
        words += 1
    if char == '.' or  char == '?' or char == '!':
        sentences += 1

L = float(letters * 100) / words
S = float(sentences * 100) / words
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")