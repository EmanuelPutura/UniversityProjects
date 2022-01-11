(defun nodesNo (tree klvl crtlvl)
    (cond
        ((and (atom tree) (eq klvl crtlvl)) 1)
        ((atom tree) 0)
        (t (apply #'+ (mapcar #'(lambda (crt) (nodesNo crt klvl (+ crtlvl 1))) tree)))
    )
)

(defun nodesNoMain (tree k)
    (nodesNo tree k -1)
)

(write (nodesNoMain '(a (b (c)) (d) (e (f))) 1))
