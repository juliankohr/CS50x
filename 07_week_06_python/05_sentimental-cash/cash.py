# import get_float function from cs50 library
from cs50 import get_float


def main():
    change = get_change()

    quarters = calculate_quarters(change)
    change = change - quarters * 25

    dimes = calculate_dimes(change)
    change = change - dimes * 10

    nickels = calculate_nickels(change)
    change = change - nickels * 5

    pennies = calculate_pennies(change)
    change = change - pennies * 1

    # sum together in how many coins the cashier can give the change back to the customer
    coins = int(quarters + dimes + nickels + pennies)
    print(f"{coins}")


# asks user for how much the customer is owed


def get_change():
    while True:
        change = get_float("Change owed: ")
        if change >= 0:
            return change * 100


# calculates how many quartes fit into change


def calculate_quarters(change):
    quarters = change // 25
    return quarters


# calculates how many dimes fit into change


def calculate_dimes(change):
    dimes = change // 10
    return dimes


# calculates how many nickels fit into change


def calculate_nickels(change):
    nickels = change // 5
    return nickels


# calculates how many pennies fit into change


def calculate_pennies(change):
    pennies = change // 1
    return pennies


if __name__ == "__main__":
    main()
