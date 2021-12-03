; method 1 mathematical model
; reverseList(list - list)
; reverseList(l1l2...ln) = the empty set, if n = 0 or if l1l2...ln is an atom
; 					 = reverseList(l2...ln) U l1, if l1 is an atom
;					 = reverseList(l2...ln) U reverseList(l1), if l1 is a list

; method 2 (collector variable) mathematical model
; reverseList(list - list, res - list)
; reverseList(l1l2...ln, res) = res, if l1l2...ln is an atom
; 							  = reverseList(l2...ln, reverseList(l1, ()) U res), if l1 is a list
; 							  = reverseList(l2...ln, l1 U res), otherwise

(defun reverseList (list res)
  (cond
    ((atom list) res)
    ((listp (car list)) (setq res (cons (reverseList (car list) ()) res)) (reverseList (cdr list) res))
    (T (setq res (cons (car list) res)) (reverseList (cdr list) res))
  )
)

; reverseListMain(list - list)
; reverseListMain(l1l2...ln) = reverseList(l1l2...ln, ())
(defun reverseListMain (list)
  (reverseList list ())
)

; test: (reverselistmain '(1 2 (3 (4 5) (6 7)) 8 (9 10 11)))