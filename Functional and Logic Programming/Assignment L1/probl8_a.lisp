#||
    a) Write a function to return the difference of two sets.   
||#

; membr(elem - atom/list, list - list)
; membr(elem, l1l2...ln) = nil,       if l1l2...ln is an atom
;                        = l1l2...ln, if elem = l1
;						 = membr(elem, l2...ln), otherwise  
(defun membr (elem list)
  (cond
    ((atom list) nil)
    ((equal elem (car list)) list)
    (T (membr elem (cdr list)))
  )
)

; setsDiff(set1 - list, set2 - list)
; setsDiff(f1f2...fn, s1s2...sm) = the empty set, if n = 0
;                                = f1 U setsDiff(f2...fn, s1s2...sm), if membr(f1, s1s2...sm) is nil
;								 = setsDiff(f2...fn, s1s2...sm), otheriwise
(defun setsDiff (set1 set2)
  (cond
    ((null set1) nil)
    ((not (membr (car set1) set2)) (cons (car set1) (setsDiff (cdr set1) set2)))
    (T (setsDiff (cdr set1) set2))
  )
)

; test: (setsDiff `(1 2 3 4 5 6 7) `(1 3 5 7 9)) => (2 4 6)
