(setq inf 999999999)

(defun maxAll (lst)
    (cond
        ((numberp lst) lst)
        ((atom lst) inf)
        (t (apply #'max (mapcar #'maxAll lst)))
    )
)

(write (maxAll '(1 5 2 (8 5 9) 5 (1 2 (4 5 (7 8 (10) 9) 6) 3) 8 2)))
