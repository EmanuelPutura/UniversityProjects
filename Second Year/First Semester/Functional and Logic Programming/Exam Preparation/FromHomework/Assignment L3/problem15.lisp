(defun reverseSuperficial (lst col)
    (cond
        ((atom lst) col)
        (t (reverseSuperficial (cdr lst) (cons (car lst) col)))
    )
)

(defun reverseSuperficialMain (lst)
    (reverseSuperficial lst NIL)
)

(defun reverseAll (lst)
    (cond
        ((atom lst) lst)
        (t (reverseSuperficialMain (mapcar #'reverseAll lst)))
    )
)


(write (reverseSuperficialMain '(1 2 3 4 5 6 7 8 9)))
(terpri)
(write (reverseAll '(1 2 3 (4 5 (6 7 (8 9) 10 11)) 12 13 (14 15 (16 17) 18 19) 20)))
