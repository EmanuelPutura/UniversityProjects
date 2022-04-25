(defun insertSorted (lst el)
    (cond
        ((atom lst) (list el))
        ((< el (car lst)) (cons el lst))
        (t (cons (car lst) (insertSorted (cdr lst) el)))
    )
)

(defun sortList (lst)
    (cond
        ((atom lst) lst)
        (t (insertSorted (sortList (cdr lst)) (car lst)))
    )
)

(write (insertSorted '(1 2 3 4 5 6 7 8 9) -1))
(terpri)
(write (sortList '(1 8 4 2 5 3 7 9 6)))

