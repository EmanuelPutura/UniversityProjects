(defun solve (lst)
    (cond
        ((and (numberp lst) (zerop (mod lst 2))) lst)
        ((numberp lst) (- 0 lst))
        ((atom lst) 0)
        (t (apply #'+ (mapcar #'solve lst)))
    )
)

(write (solve '(1 2 (4 3 (1 4 (2)) 3))))
