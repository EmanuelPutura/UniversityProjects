(defun removeOdd (elem level)
    (cond
        ((and (atom elem) (or (numberp elem) (eq (mod level 2) 1)) (list elem)))
        ((atom elem) nil)
        (t (list (apply 'append (mapcar #'(lambda (crt) (removeOdd crt (+ level 1))) elem))))
    )
)

(defun removeOddMain (lst)
    (car (removeOdd lst 0))
)

(print (removeOddMain '(a (1 (2 b)) (c (d)))))
(print (removeOddMain '(1 2 A 3 4 (B C 1 2 D 4 2 (a b c (1 2 s d a z))))))

