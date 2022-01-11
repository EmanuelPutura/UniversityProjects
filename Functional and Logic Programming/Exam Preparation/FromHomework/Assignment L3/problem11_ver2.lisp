(defun listDepthVer2 (lst crt)
    (cond
        ((atom lst) crt)
        (t (apply #'max (mapcar #'(lambda (c) (listDepthVer2 c (+ 1 crt))) lst)))
    )
)

(defun listDepthVer2Main (lst)
    (listDepthVer2 lst 0)
)

(write (listDepthVer2Main '(1 (2 3 (3) (4 5 (6 7 (8 9) 10)) 2 (4 5) 3 (5)))))