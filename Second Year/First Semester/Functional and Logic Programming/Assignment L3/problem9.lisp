#||
    Assignment L3 - Problem 9:
    Write a function that removes all occurrences of an atom from any level of a list.
||#

(defun removeAtomV1 (lst x)
    (cond
        ((and (atom lst) (eq lst x)) nil)
        ((atom lst) lst)
        (t (remove nil (mapcar #'(lambda (elem) (removeAtomV1 elem x)) lst)))
    )
)

#||
    removeAtomV2(l1l2...ln, x) = the empty set,                             if l1l2...ln = list is an atom and list = x
                               = {lst} (a list with a single element: lst), if lst is an atom 
                               = {U (1 <= i <= n) removeAtomV2(li, x)},     otherwise (if lst is a list)
                               
    mainRemoveAtomV2(l1l2...ln, x) = r1, where removeAtomV2(l1l2...ln, x) = r1r2...rm
||#

(defun removeAtomV2 (lst x)
    (cond
        ((and (atom lst) (eq lst x)) nil)
        ((atom lst) (list lst))
        (t (list (apply 'append (mapcar #'(lambda (elem) (removeAtomV2 elem x)) lst))))
    )
)

(defun mainRemoveAtomV2 (lst x)
    (car (removeAtomV2 lst x))
)

(print (removeAtomV1 '(2 1 1 2 3 4 1 (1 2 3 (1 2 3 1 (4 5 A 1))) 6 3) 1))
(print (mainRemoveAtomV2 '(2 1 1 2 3 4 1 (1 2 3 (1 2 3 1 (4 5 A 1))) 6 3) 1))
(print (mainRemoveAtomV2 '(1 2 3 A B (A B A) 1 2 AA A 24 A) 'A))

