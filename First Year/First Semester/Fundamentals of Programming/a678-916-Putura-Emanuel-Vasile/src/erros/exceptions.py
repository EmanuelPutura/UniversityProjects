from colors.color import Color


class ValidationError(Exception):
    """
    Custom exception class for a validation error
    """
    def __str__(self):
        return Color.FAIL + super().__str__() + Color.ENDC

    def gui_str(self):
        return super().__str__()


class ServiceError(Exception):
    """
    Custom exception class for a service error
    """

    def __str__(self):
        return Color.FAIL + super().__str__() + Color.ENDC

    def gui_str(self):
        return super().__str__()


class RepositoryError(Exception):
    """
    Custom exception class for a repository error
    """
    def __str__(self):
        return Color.FAIL + super().__str__() + Color.ENDC

    def gui_str(self):
        return super().__str__()


class IDError(ValueError):
    """
    Custom exception class for an ID error
    """
    def __str__(self):
        return Color.FAIL + super().__str__() + Color.ENDC

    def gui_str(self):
        return super().__str__()


class UndoRedoError(Exception):
    """
    Custom exception class for an undo error
    """
    def __str__(self):
        return Color.FAIL + super().__str__() + Color.ENDC

    def gui_str(self):
        return super().__str__()
