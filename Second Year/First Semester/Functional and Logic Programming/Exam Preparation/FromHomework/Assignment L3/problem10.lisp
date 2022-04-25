(defun replaceNode (crt node repl)
    (cond
        ((and (atom crt) (eq crt node)) repl)
        ((atom crt) crt)
        (t (mapcar #'(lambda (c) (replaceNode c node repl)) crt))
    )
)

(write (replaceNode '(a (b (c)) (d) (e (f))) 'b 'g))
