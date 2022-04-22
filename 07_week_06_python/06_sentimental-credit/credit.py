# import get_int from cs50 library
from cs50 import get_int


def main():
    cardnumber = get_cardnumber()
    length = calc_length(cardnumber)
    checksum = calc_checksum(cardnumber)
    startdigits = calc_startdigits(cardnumber, length)
    validation = determine_validity(checksum, length, startdigits)
    print(f"{validation}")


# ask user for credit card number


def get_cardnumber():
    number = get_int("Number: ")
    return number


# calculate the length of provided credit card number


def calc_length(cardnumber):
    length = len(str(cardnumber))
    return length


# calculate the checksum


def calc_checksum(cardnumber):
    checksum_eod = 0
    checksum_nmd = 0
    cardnumber_eod = cardnumber // 10
    cardnumber_nmd = cardnumber

    while cardnumber_eod > 0:
        eod = cardnumber_eod % 10
        mult_eod = eod * 2
        cardnumber_eod //= 100

        while mult_eod > 0:
            eod_digit = mult_eod % 10
            checksum_eod = checksum_eod + eod_digit
            mult_eod = mult_eod // 10

    while cardnumber_nmd > 0:
        nmd = cardnumber_nmd % 10
        checksum_nmd += nmd
        cardnumber_nmd //= 100

    checksum = checksum_eod + checksum_nmd
    mod_checksum = checksum % 10

    if mod_checksum == 0:
        return True
    else:
        return False


# calculate the first two digits of the credit card number


def calc_startdigits(cardnumber, length):
    for i in range(2, length, 1):
        cardnumber //= 10

    startdigits = cardnumber
    return startdigits


# determine the validity


def determine_validity(checksum, length, startdigits):
    validity = 0

    # check if conditions apply for AMEX
    if (checksum == True and length == 15) and (startdigits == 34 or startdigits == 37):
        validity = "AMEX"

    # check if conditions apply for MASTERCARD
    elif (checksum == True and length == 16) and (startdigits in range(51, 56)):
        validity = "MASTERCARD"

    # check if conditions apply for VISA
    elif (checksum == True and length == 13) or (length == 16 and startdigits in range(40, 50)):
        validity = "VISA"

    # else return INVALID
    else:
        validity = "INVALID"

    return validity


if __name__ == "__main__":
    main()
