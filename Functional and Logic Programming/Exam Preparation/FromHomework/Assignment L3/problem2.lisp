(defun sumNumeric (lst)
    (cond
        ((numberp lst) lst)
        ((atom lst) 0)
        (t (apply #'+ (mapcar #'sumNumeric lst)))
    )
)

(write (sumNumeric '(1 2 (1 2 (10 (11)) 3) 3 4 (42) 5)))
