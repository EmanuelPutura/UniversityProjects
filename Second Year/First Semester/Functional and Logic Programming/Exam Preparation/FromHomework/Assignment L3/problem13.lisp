(defun treeDepth (tree)
    (cond
        ((atom tree) 0)
        (t (+ 1 (apply #'max (mapcar #'treeDepth tree))))
    )
)

(write (treeDepth '(a (b (c)) (d) (e (f)))))
