(defun removeAll (crt at)
    (cond
        ((and (atom crt) (eq at crt)) nil)
        ((atom crt) (list crt))
        (t (list (apply #'append (mapcar #'(lambda (el) (removeAll el at)) crt))))
    )
)

(defun removeAllMain (crt at)
    (car (removeAll crt at))
)

(write (removeAllMain '(1 2 1 3 (2 1 (2 3 (1 2 3 1 2) 3) 7 5 (1 2) (1 -1) 7 3)) 1))
