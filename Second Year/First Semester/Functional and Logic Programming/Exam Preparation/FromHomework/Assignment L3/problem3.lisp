(defun solve (tree node)
    (cond
        ((and (atom tree) (eq tree node)) t)
        ((atom tree) nil)
        (t (some #'identity (mapcar #'(lambda (el) (solve el node)) tree)))
    )
)

(write (solve '(a (b (c)) (d) (E (f))) 'b))
; (write (solve '(a (b (c)) (d) (E (f))) 'x))