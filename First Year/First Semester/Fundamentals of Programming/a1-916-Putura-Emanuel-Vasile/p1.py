#
# Implement the program to solve the problem statement from the first set here
#
# 4. For a given natural number n find the largest natural number
# written with the same digits. (e.g. n=3658, m=8653).
#


def read_number():
    """
        Reads a natural number

        :return: the natural number
    """
    n = int(input("Please input a natural number: "))
    return n


def build_frequency_list(n):
    """
        Builds a frequency list containing the number of appearances of each digit in n:
        l[d] = i <=> digit d appears exactly i times in n

        :param n: natural number
        :return: a list containing the number of appearances of each digit in n 
    """
    # frequency list. It first has 10 elements, all equal to 0
    l = [0] * 10

    # update frequency list
    while n != 0:
        c = int(n % 10)
        l[c] = l[c] + 1
        n //= 10
    
    return l


def build_new_number():
    """
        Builds the new number n

        :return: the new natural number n
    """
    n = 0
    for i in range(9, -1, -1):
        while l[i] > 0:
            n = n * 10 + i
            l[i] = l[i] - 1
    return n


def print_result(n):
    """
        Prints the result

        :param n: the number to be printed
    """
    print(n)

    
if __name__ == "__main__":
    n = read_number()
    l = build_frequency_list(n)
    n = build_new_number()
    print_result(n)
