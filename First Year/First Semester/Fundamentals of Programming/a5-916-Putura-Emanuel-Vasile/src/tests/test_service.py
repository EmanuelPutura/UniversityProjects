from src.services.service import ComplexService


def test_service():
    test_generate_default_complex_nos()
    test_filter_complex_nos_by_indices()
    test_add_complex_no()
    test_undo_operation()
    test_update_history()


def test_generate_default_complex_nos():
    service = ComplexService()
    service.generate_default_complex_nos()
    assert len(service.complex_nos) == 10
    for cn in service.complex_nos:
        assert cn.real_part in range(-9, 10)
        assert cn.imaginary_part in range(-9, 10)


def test_filter_complex_nos_by_indices():
    service = ComplexService()
    service.generate_default_complex_nos()
    cn_list = service.complex_nos[3:8]

    service.filter_complex_nos_by_indices(3, 7)
    assert len(service.complex_nos) == 5
    for i in range(5):
        assert cn_list[i] == service.complex_nos[i]


def test_add_complex_no():
    service = ComplexService()
    try:
        service.add_complex_no('z = 2 + 3i')
        assert False
    except ValueError:
        assert True

    try:
        service.add_complex_no('2+3i')
        assert False
    except ValueError:
        assert True

    service.add_complex_no(' 2 - 2.3i')
    assert service.complex_nos[len(service.complex_nos) - 1].real_part == 2 and service.complex_nos[len(service.complex_nos) - 1].imaginary_part == -2.3
    service.add_complex_no('2 - i')
    assert service.complex_nos[len(service.complex_nos) - 1].real_part == 2 and service.complex_nos[len(service.complex_nos) - 1].imaginary_part == -1
    service.add_complex_no('-2.3i')
    assert service.complex_nos[len(service.complex_nos) - 1].real_part == 0 and service.complex_nos[len(service.complex_nos) - 1].imaginary_part == -2.3


def test_undo_operation():
    service = ComplexService()
    service.add_complex_no('2 + 3i')
    assert len(service.complex_nos) == 1
    service.undo_operation()
    assert not len(service.complex_nos)
    try:
        service.undo_operation()
        assert False
    except ValueError:
        assert True


def test_update_history():
    service = ComplexService()
    service.generate_default_complex_nos()
    service.add_complex_no('2 + 3i')
    assert len(service.history) == 1
    service.undo_operation()
    assert not len(service.history)
