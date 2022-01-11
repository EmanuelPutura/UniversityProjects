(defun product (lst)
    (cond
        ((numberp lst) lst)
        ((atom lst) 1)
        (t (apply #'* (mapcar #'product lst)))
    )
)

(write (product '(1 2 (2 (2) 3) 3 4 5)))
