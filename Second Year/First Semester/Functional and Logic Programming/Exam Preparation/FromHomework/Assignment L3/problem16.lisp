(defun linearList (lst)
    (cond
        ((atom lst) (list lst))
        (t (apply #'append (mapcar #'linearList lst)))
    )
)

(write (linearList '(((A B) C) (D E (F G (H I (J K) L M N))) O P Q)))
