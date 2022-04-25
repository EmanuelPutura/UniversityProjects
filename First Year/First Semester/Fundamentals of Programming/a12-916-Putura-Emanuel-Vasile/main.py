"""
    Coins Backtracking Problem
        1. A number of n coins are given, with values of a1, ..., an and a value s.
        Display all payment modalities for the sum s. If no payment modality exists print a message.
"""


from backtracking_algorithms.coins_problem import CoinsIterativeBacktracking, CoinsRecursiveBacktracking

if __name__ == "__main__":
    print('-' * 20 + 'Backtracking Algorithms' + '-' * 20)
    print(' recursive - Apply recursive backtracking for the coins problem')
    print(' iterative - Apply iterative backtracking for the coins problem')
    print(' exit - Exit the application')
    print('-' * 63)

    options = {'recursive': CoinsRecursiveBacktracking, 'iterative': CoinsIterativeBacktracking}

    while True:
        try:
            option = input('option > ')
            if option == 'exit':
                break
            if option in options:
                print('test example:')
                print('n = 5\nsum = 10\ncoins: 7, 2, 1, 3, 8\n')
                n = int(input('n = '))
                sum = int(input('sum = '))
                coins = []
                for i in range(n):
                    coins.append(int(input('Coin no. {} value = '.format(i + 1))))
                options[option]([], coins, sum)
            else:
                print('Invalid command.\n')
        except Exception as exception:
            print(exception)
