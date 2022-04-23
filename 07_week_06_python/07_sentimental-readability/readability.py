# import get_string from cs50 library
from cs50 import get_string


# define main function
def main():

    # ask user for a text
    text = get_string("Text: ")
    # create a dict with measures and initial values
    results = {"letter_count": 0, "word_count": 1, "sentence_count": 0}
    # count letters, words and sentences with count function
    count(text, results)
    # calculate grade with coleman-liau index
    grade = cl_index(results)

    # print relatet grade result
    if (grade < 1):
        print("Before Grade 1\n")

    elif (grade >= 16):
        print("Grade 16+\n")

    else:
        print(f"Grade {grade}\n")


# define count function
def count(text, results):

    # iterate through the given text to calculate letters, words and sentences and increment results in dict results
    for i in range(len(text)):
        n = ord(text[i])

        if (n >= 65 and n <= 90) or (n >= 97 and n <= 122):
            results["letter_count"] += 1

        if (n == 32):
            results["word_count"] += 1

        if (n == 33 or n == 46 or n == 63):
            results["sentence_count"] += 1


# define coleman-liau index function
def cl_index(results):

    # results from dict applied in the coleman-liau index
    letters_p100 = results["letter_count"] / results["word_count"] * 100
    sentences_p100 = results["sentence_count"] / results["word_count"] * 100
    index = (0.0588 * letters_p100) - (0.296 * sentences_p100) - 15.8

    # round result before returning the value
    return round(index)


if __name__ == "__main__":
    main()