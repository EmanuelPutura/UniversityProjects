(defun listDepthVer1 (lst)
    (cond
        ((atom lst) 0)
        (t (+ 1 (apply #'max (mapcar #'listDepthVer1 lst))))
    )
)

(write (listDepthVer1 '(1 (2 3 (3) (4 5 (6 7 (8 9) 10)) 2 (4 5) 3 (5)))))
