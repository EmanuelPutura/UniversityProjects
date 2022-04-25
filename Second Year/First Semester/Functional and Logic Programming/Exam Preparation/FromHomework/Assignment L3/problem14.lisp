(defun atomsNo (lst)
    (cond
        ((atom lst) 1)
        (t (apply #'+ (mapcar #'atomsNo lst)))
    )
)

(write (atomsNo '(1 2 3 (4 5) (6 7 (8 9 (10 11) 12 13 (14 15) 16) 17))))
