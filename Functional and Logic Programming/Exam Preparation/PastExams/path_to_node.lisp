(defun reverseSuperficial (lst col)
    (cond
        ((atom lst) col)
        (t (reverseSuperficial (cdr lst) (cons (car lst) col)))
    )
)

(defun reverseSuperficialMain (lst)
    (reverseSuperficial lst nil)
)

(defun path (crt node col) 
    (cond
        ((and (atom crt) (eq crt node)) col)
        ((atom crt) nil)
        (t (apply #'append (mapcar #'(lambda (c) (path c node (cons (car crt) col))) crt)))
    )
)

(defun pathMain (tree node)
    (reverseSuperficialMain (path tree node nil))
)

(write (pathMain '(a (b (g)) (c (d (e)) (f))) 'b))
