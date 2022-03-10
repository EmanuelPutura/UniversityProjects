import pygame

from Utils.constants import Constants
from Domain.map import DetectedMap


class Drone:
    def __init__(self, x, y):
        self.x = x
        self.y = y

        self.__dfs_visited = set()
        self.__dfs_stack = [(x, y, False)]
        self.__backtrack = False

    def move(self, detectedMap):
        pressed_keys = pygame.key.get_pressed()
        if self.x > 0:
            if pressed_keys[pygame.K_UP] and detectedMap.surface[self.x - 1][self.y] == 0:
                self.x = self.x - 1
        if self.x < Constants.BOARD_DIM - 1:
            if pressed_keys[pygame.K_DOWN] and detectedMap.surface[self.x + 1][self.y] == 0:
                self.x = self.x + 1

        if self.y > 0:
            if pressed_keys[pygame.K_LEFT] and detectedMap.surface[self.x][self.y - 1] == 0:
                self.y = self.y - 1
        if self.y < Constants.BOARD_DIM - 1:
            if pressed_keys[pygame.K_RIGHT] and detectedMap.surface[self.x][self.y + 1] == 0:
                self.y = self.y + 1

    def __isValidIndex(self, x, y):
        return 0 <= x < Constants.BOARD_DIM and 0 <= y < Constants.BOARD_DIM

    def __isWorthVisiting(self, x, y, detectedMap):
        # S/N direction
        for verticalDirection in [-1, 1]:
            (i, j) = (x, y)
            while self.__isValidIndex(i, j):
                if detectedMap.surface[i][j] == -1:
                    return True
                if detectedMap.surface[i][j] == 1:
                    break
                if self.__isValidIndex(i - 1, j) and detectedMap.surface[i - 1][j] == -1:
                    return True
                if self.__isValidIndex(i + 1, j) and detectedMap.surface[i + 1][j] == -1:
                    return True
                j += verticalDirection

        # W/E direction
        for horizontalDirection in [-1, 1]:
            (i, j) = (x, y)
            while self.__isValidIndex(i, j):
                if detectedMap.surface[i][j] == -1:
                    return True
                if detectedMap.surface[i][j] == 1:
                    break
                if self.__isValidIndex(i, j - 1) and detectedMap.surface[i][j - 1] == -1:
                    return True
                if self.__isValidIndex(i, j + 1) and detectedMap.surface[i][j + 1] == -1:
                    return True
                i += horizontalDirection

        return False

    def moveDFS(self, detectedMap, environment, optimize=True):
        if not self.__dfs_stack:
            self.x, self.y = None, None
            return

        (x, y, backtrack) = self.__dfs_stack.pop()
        while ((x, y) in self.__dfs_visited and not backtrack) or (optimize and not self.__isWorthVisiting(x, y, detectedMap) and not backtrack):
            self.__dfs_stack.pop()
            if not self.__dfs_stack:
                self.x, self.y = None, None
                return
            (x, y, backtrack) = self.__dfs_stack.pop()

        if (x, y) not in self.__dfs_visited:
            self.__dfs_visited.add((x, y))
        self.x = x
        self.y = y

        sensors_data = environment.readUDMSensors(x, y)
        for variation in Constants.VARIATIONS:
            if sensors_data[Constants.DIRECTION_TO_VARIATION[(variation[0], variation[1])]] == 0:
                continue

            current = (x + variation[0], y + variation[1])
            if self.__isValidIndex(current[0], current[1]) and detectedMap.surface[x][y] != 1 and (current[0] != self.x or current[1] != self.y):
                if current not in self.__dfs_visited:
                    self.__dfs_stack.append((x, y, True))
                    self.__dfs_stack.append((current[0], current[1], False))
