(defun isMember (l at)
    (cond
        ((and (atom l) (eq l at)) t)
        ((atom l) nil)
        (t (some #'identity (mapcar #'(lambda (crt) (isMember crt at)) l)))
    )
)

(write (isMember '(1 2 (-1 -2 -3 (9)) 3 4 (10 11 (12) (13) 14) 5 6) 12))
