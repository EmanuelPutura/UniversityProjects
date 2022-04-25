#
# Implement the program to solve the problem statement from the second set here
#
# 9. Consider a given natural number n.
# Determine the product p of all the proper factors of n.
#


from math import sqrt


def read_number():
    """
        Reads a natural number

        :return: the natural number
    """
    n = int(input("Please input a natural number: "))
    return n


def find_product_of_proper_factors(n):
    """
        Finds the product of the proper factors of n

        :param n: a natural number
        :return: the product
    """
    product = 1
    for d in range(2, int(sqrt(n)) + 1):
        if n % d == 0:
            product *= d
            if d != n / d:
                product *= n / d
    return int(product)


def print_result(p):
    """
        Prints the result

        :param p: the number to be printed
    """
    print(p)
    
if __name__ == "__main__":
    n = read_number()
    p = find_product_of_proper_factors(n)
    print_result(p)
