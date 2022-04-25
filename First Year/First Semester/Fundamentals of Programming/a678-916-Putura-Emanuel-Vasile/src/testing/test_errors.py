import unittest

from colors.color import Color
from erros.exceptions import ValidationError, RepositoryError, ServiceError, IDError, UndoRedoError


class TestValidationError(unittest.TestCase):
    def test_validation_error(self):
        error = 'error'
        try:
            raise ValidationError(error)
        except ValidationError as validationError:
            self.assertEqual(str(validationError), Color.FAIL + error + Color.ENDC)
            self.assertEqual(validationError.gui_str(), error)


class TestRepositoryError(unittest.TestCase):
    def test_repository_error(self):
        error = 'error'
        try:
            raise RepositoryError(error)
        except RepositoryError as repositoryError:
            self.assertEqual(str(repositoryError), Color.FAIL + error + Color.ENDC)
            self.assertEqual(repositoryError.gui_str(), error)


class TestServiceError(unittest.TestCase):
    def test_service_error(self):
        error = 'error'
        try:
            raise ServiceError(error)
        except ServiceError as serviceError:
            self.assertEqual(str(serviceError), Color.FAIL + error + Color.ENDC)
            self.assertEqual(serviceError.gui_str(), error)


class TestIDError(unittest.TestCase):
    def test_id_error(self):
        error = 'error'
        try:
            raise IDError(error)
        except IDError as idError:
            self.assertEqual(str(idError), Color.FAIL + error + Color.ENDC)
            self.assertEqual(idError.gui_str(), error)


class TestUndoRedoError(unittest.TestCase):
    def test_undo_redo_error(self):
        error = 'error'
        try:
            raise UndoRedoError(error)
        except UndoRedoError as undoRedoError:
            self.assertEqual(str(undoRedoError), Color.FAIL + error + Color.ENDC)
            self.assertEqual(undoRedoError.gui_str(), error)
