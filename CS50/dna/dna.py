import csv
import sys


def main():

    # Check for command-line usage
    # Ensure correct usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py filename.cvs filename.txt")
        exit()
    filecsv = sys.argv[1]
    filetxt = sys.argv[2]
    # Read database file into a variable
    with open(filecsv) as f:
        reader1 = csv.DictReader(f)
        database = list(reader1)
    # Read DNA sequence file into a variable
    with open(filetxt) as f:
        dna = f.read()

    # Find longest match of each STR in DNA sequence
    # Run through first row of database to grab subsequences and pair into the match function
    matches = {}
    for i in database[0]:
        matches[i] = (longest_match(dna, i))

    #  Check database for matching profiles
    count = 1
    # Iterate through length of database, match matches longest matches to the values in the database, if match, print name
    for i in range(len(database)):
        for j in matches:
            if str(matches[j]) == database[i][j]:
                count += 1
        if count == len(matches):
            print(database[i]['name'])
            return
        else:
            count = 1
    print("No Match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
