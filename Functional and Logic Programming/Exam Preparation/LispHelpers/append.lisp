(DEFUN appendUtil (L1 L2)
    (COND
        ((NULL L1) L2)
        (T (CONS (CAR L1) (appendUtil (CDR L1) L2)))
    )
)

(DEFUN listAppend(L1 L2 &rest L)
    (COND
         ((NULL L) (appendUtil L1 L2))
         (T (appendUtil L1 (apply #'listAppend (CONS L2 L))))
    )
)

(defun removeElem (crt elem)
    (cond
        ((and (atom crt) (eq crt elem)) nil)
        ((atom crt) (list crt))
        (t (list (apply #'listAppend (mapcar #'(lambda (c) (removeElem c elem)) crt))))
    )
)

; (write (listAppend '(1 2 3) '(4 5 6) '(7 8 9)))

(write (car (removeElem '(1 2 (3 1 2 (1 2 3 (4 3 1 (1 5) 1 4) 2 1)) 1 5 1 3 1 (2 1 3)) 1)))
