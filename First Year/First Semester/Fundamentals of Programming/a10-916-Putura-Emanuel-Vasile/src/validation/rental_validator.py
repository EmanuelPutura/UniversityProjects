from erros.exceptions import ValidationError


class RentalValidator:
    """
    Validator class for the Rental class
    """
    def validate(self, rental):
        errors = ''
        if rental.id < 0:
            errors += "'{}' is not a valid rental ID.\n".format(rental.id)
        if rental.rented_date > rental.due_date:
            errors += 'Invalid rented and due dates.\n'
        if not isinstance(rental.returned_date, str) and rental.rented_date > rental.returned_date:
            errors += 'Invalid rented and returned dates.\n'
        if len(errors) > 0:
            raise ValidationError(errors)
