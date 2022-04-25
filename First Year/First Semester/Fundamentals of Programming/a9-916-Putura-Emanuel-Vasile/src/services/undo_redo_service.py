from dataclasses import dataclass

from erros.exceptions import UndoRedoError


@dataclass
class UndoOperation:
    target_object: object
    handler: object
    args: tuple


class UndoManager:
    __undo_operations = []

    @staticmethod
    def undo_operations():
        return UndoManager.__undo_operations

    @staticmethod
    def register_operation(target_object, handler, *args):
        UndoManager.__undo_operations.append(UndoOperation(target_object, handler, args))

    @staticmethod
    def undo():
        if not len(UndoManager.__undo_operations):
            raise UndoRedoError('No more undoes available.\n')
        last_operation = UndoManager.__undo_operations.pop()
        last_operation.handler(last_operation.target_object, *last_operation.args)


class RedoManager:
    __redo_operations = []

    @staticmethod
    def register_operation(length, target_object, handler, *args):
        RedoManager.__redo_operations.append((UndoOperation(target_object, handler, args), length))

    @staticmethod
    def redo():
        if not len(RedoManager.__redo_operations):
            raise UndoRedoError('Cannot redo.\n')
        last_operation = RedoManager.__redo_operations.pop()
        # this means that new operations have been executed after the last undo, so redo cannot be performed
        if last_operation[1] != len(UndoManager.undo_operations()):
            raise UndoRedoError('Redo can be executed only after an undo.\n')
        last_operation[0].handler(last_operation[0].target_object, *last_operation[0].args)
