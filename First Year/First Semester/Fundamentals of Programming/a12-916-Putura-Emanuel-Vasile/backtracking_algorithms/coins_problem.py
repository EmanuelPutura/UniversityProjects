from backtracking_algorithms.backtracking import BacktrackingAlgorithm


class CoinsBacktracking(BacktrackingAlgorithm):
    """
        Subclass of the BacktrackingAlgorithm class -> implements a backtracking problem:
            - the coins problem
    """
    def __init__(self, candidates, coins, sum):
        self.__solution_number = 0
        self._coins = coins
        self._sum = sum

    def first(self):
        return 0

    def next_element(self, candidates):
        if candidates[-1] == 1:
            return None
        return 1

    def is_consistent(self, candidates):
        current_sum = 0
        if len(candidates) > len(self._coins):
            return False
        for i in range(len(candidates)):
            if candidates[i] == 1:
                current_sum += self._coins[i]
            if current_sum > self._sum:
                return False
        return True

    def is_solution(self, candidates):
        current_sum = 0
        for i in range(len(candidates)):
            if candidates[i] == 1:
                current_sum += self._coins[i]
            if current_sum > self._sum:
                return False
        return current_sum == self._sum

    def print_solution(self, candidates):
        self.__solution_number += 1
        print("Solution no. {}:".format(self.__solution_number))
        for i in range(len(candidates)):
            if candidates[i] == 1:
                print(self._coins[i], end=' ')
        print()

    def backtracking(self, *args):
        pass


class CoinsRecursiveBacktracking(CoinsBacktracking):
    """
        Subclass of the CoinsBacktracking class -> implements the backtracking algorithm using a recursive method
    """
    def __init__(self, candidates, coins, sum):
        super().__init__(candidates, coins, sum)
        self.backtracking(candidates)

    def backtracking(self, candidates):
        element = self.first()
        candidates.append(element)
        while element is not None:
            if self.is_consistent(candidates):
                if self.is_solution(candidates):
                    self.print_solution(candidates)
                else:
                    self.backtracking(candidates[:])
            element = self.next_element(candidates)
            candidates[-1] = element


class CoinsIterativeBacktracking(CoinsBacktracking):
    """
        Subclass of the CoinsBacktracking class -> implements the backtracking algorithm using an iterative method
    """
    def __init__(self, candidates, coins, sum):
        super().__init__(candidates, coins, sum)
        self.__stack = [(candidates, coins, sum)]
        self.backtracking(candidates)

    def backtracking(self, candidates):
        while len(self.__stack) > 0:
            candidates = self.__stack[-1][0]
            coins = self.__stack[-1][1]
            sum = self.__stack[-1][2]
            self.__stack.pop()

            element = self.first()
            candidates.append(element)
            while element is not None:
                if self.is_consistent(candidates):
                    if self.is_solution(candidates):
                        self.print_solution(candidates)
                    else:
                        self.__stack.append((candidates[:], coins, sum))
                element = self.next_element(candidates)
                candidates[-1] = element
            if element is None:
                candidates = candidates[:-1]
