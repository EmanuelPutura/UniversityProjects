from abc import ABC, abstractmethod


class BacktrackingAlgorithm(ABC):
    """
        Abstract base class for the backtracking algorithm
    """
    @abstractmethod
    def first(self, *args):
        pass

    @abstractmethod
    def next_element(self, *args):
        pass

    @abstractmethod
    def is_consistent(self, *args):
        pass

    @abstractmethod
    def is_solution(self, *args):
        pass

    @abstractmethod
    def print_solution(self, *args):
        pass

    @abstractmethod
    def backtracking(self, *args):
        pass
