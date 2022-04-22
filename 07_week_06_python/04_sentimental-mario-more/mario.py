# import get_int function from cs50 library
from cs50 import get_int

# initialize while-loop
while True:

    # ask user for height of the pyramid
    height = get_int("Height: ")

    # if user input is not a positive integer no greater than 8, ask again
    if height not in range(1, 9):
        continue

    # if user input is in the right range
    if height in range(1, 9):

        # start loop on which # gets printed based on the provided height input of user
        for i in range(0, height, 1):

            # print left spacing as long as j < height whereas j is depending on i so the number of spacings decrease while i and the number of # increase
            for j in range(i + 1, height, 1):
                print(" ", end="")

            # prints left half of pyramid in dependency to i
            for k in range(0, i + 1, 1):
                print("#", end="")

            # print two spaces
            print("  ", end="")

            # prints right half of pyramid in dependency to i
            for l in range(0, i + 1, 1):
                print("#", end="")

            # starts new line after each row
            print("\n", end="")

    # break out of while-loop
    break