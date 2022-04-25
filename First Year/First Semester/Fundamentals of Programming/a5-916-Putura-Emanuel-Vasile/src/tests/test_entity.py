from src.domain.entity import Complex


def test_entity():
    test_complex()
    test_complex_eq()
    test_complex_abs()


def test_complex():
    try:
        c1 = Complex(1, 0)
        c2 = Complex(1.0, 0.0)
        c3 = Complex(1, -1)
        c4 = Complex(4, -5.0)
        assert True
    except ValueError:
        assert False


def test_complex_eq():
    c1 = Complex(2, 3)
    c2 = Complex(2, 3)
    c3 = Complex(2, 6)
    assert c1 == c2
    assert c2 != c3


def test_complex_abs():
    c1 = Complex(4, 3)
    assert abs(c1) == 5
