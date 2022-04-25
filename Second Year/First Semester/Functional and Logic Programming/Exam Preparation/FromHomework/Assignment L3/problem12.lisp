(defun subsAll (lst elem newelem)
    (cond
        ((and (atom lst) (eq elem lst)) newelem)
        ((atom lst) lst)
        (t (mapcar #'(lambda (crt) (subsAll crt elem newelem)) lst))
    )
)

(write (subsAll '(1 2 3 (1 2 (1) 4 5 1) 8 9 1 2) 1 99))
