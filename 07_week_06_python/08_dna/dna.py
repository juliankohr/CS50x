import csv
import sys


def main():

    # if provided cli-arguments are not equal 3, exit with error message
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py database.csv sequence.txt")

    # initialize two lists for database and short tandem repeats
    DB = []
    STR = []

    # open .csv file whohc is the second cli argument as database
    with open(sys.argv[1], "r") as database:

        # initialize a reader
        reader = csv.DictReader(database)

        # for each row add the content to list DB
        for row in reader:
            DB.append(row)

        # save names of strs which are in the very first line of the .csv file in the list STR
        STR = reader.fieldnames[1:]

    # initialize list for dna sequence
    DNA = []

    # open file of the third cli argument and put content into DNA list
    with open(sys.argv[2], "r") as sequence:
        DNA = sequence.read()

    # initialize dict to save names of STRs as keys and their correponding matches as values
    LM_STR = {}
    for i in range(len(STR)):
        LM_STR.update({STR[i]: longest_match(str(DNA), str(STR[i]))})

    # for every entry (person) in the database initialize variable matches
    for i in range(len(DB)):
        matches = 0

        #  for every STR value from LM_STR compare with entries (persons) STR values from DB
        for j in range(len(STR)):
            if int(LM_STR[str(STR[j])]) == int(DB[i][str(STR[j])]):
                # if there is a match increment variable matches by 1
                matches += 1
            # if matches match the amount of STRs print out the corresponding name from DB
            if matches == len(STR):
                print(DB[i]["name"])
                sys.exit(0)

    # if there is no match print correponding message
    print("No match")
    sys.exit(1)


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
