(defun substituteAll (crt elem lst)
    (cond
        ((and (atom crt) (eq crt elem)) lst)
        ((atom crt) crt)
        (t (mapcar #'(lambda (e) (substituteAll e elem lst)) crt))
    )
)

(write (substituteAll '(A B 2 3 D (M 0 2 2 (2 D E 2 (D 2)) G) F 5 2) 'D '(25 26 27)))
