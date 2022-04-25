#
# Implement the program to solve the problem statement from the third set here
#
# 15. Generate the largest perfect number smaller than a given natural number n.
# If such a number does not exist, a message should be displayed.
# A number is perfect if it is equal to the sum of its divisors, except itself.
# (e.g. 6 is a perfect number, as 6=1+2+3).
#


from math import sqrt


def read_number():
    """
        Reads a natural number

        :return: the natural number
    """
    n = int(input("Please input a natural number: "))
    return n


def sum_of_divisors(n):
    """
        Finds the sum of all the divisors of n

        :param n: a natural number
        :return: the sum
    """
    sum = 0
    for d in range(1, int(sqrt(n)) + 1):
        if n % d == 0:
            sum += d
            if d != n / d:
                sum += n / d
    return int(sum)


def check_if_perfect(n):
    """
        Checks if n is a perfect number

        :param n: a natural number
        :return: True if n is a perfect number, False else
    """
    sum = sum_of_divisors(n) - n
    if sum == n:
        return True
    return False


def search_perfect_number(n):
    """
        Searchs the largest perfect number smaller than a given natural number n
        If such a number does not exist, function returns -1

        :param n: a natural number
        :return: the largest perfect number smaller than n, or -1 if such a number
                 does not exist
    """
    for i in range(n - 1, 0, -1):
        if check_if_perfect(i) == True:
            return i
    return -1


def print_result(result):
    """
        Prints the result if it exists, or a message else

        :param result: the result (or -1 if it does not exist)
    """
    if result == -1:
        print("There is no perfect number smaller than your number!")
    else:
        print(result)


if __name__ == "__main__":
    n = read_number()
    result = search_perfect_number(n)
    print_result(result)
