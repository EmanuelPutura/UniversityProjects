#||
    c) Write a function to return the list of the first elements of all list elements of a given list with an odd 
       number of elements at superficial level. Example:
       (1 2 (3 (4 5) (6 7)) 8 (9 10 11)) => (1 3 9). 
    
    listLength(l1l2...ln) = 0, if n = 0
                          = 1 + listLength(l2...ln), otherwise
    
    hasOddLength(l1l2...ln) = false, if listLength(l1l2...ln) % 2 = 0
                              true, otherwise
    
    getFirst(l1l2...ln) = the empty set, if n = 0
                        = mainGetFirst(l1) U getFirst(l2...ln), if l1 is a list
                        = getFirst(l2...ln), otherwise
                        
    
||#

(defun listLength (list)
  (cond
    ((atom list) 0)
    (T (+ 1 (listLength (cdr list))))
  )
)

(defun hasOddLength (list)
  (cond
    ((= (mod (listLength list) 2) 1) T)
    ((= (mod (listLength list) 2) 1) nil) 
  )
)

(defun mainGetFirst (list)
  (cond
    ((hasOddLength list) (cons (car list) (getFirst list)))
    (T (getFirst list))
  )
)

(defun getFirst (list)
  (cond
    ((atom list) nil)
    ((listp list) (append (mainGetFirst (car list)) (getFirst (cdr list))))
    (T (getFirst (cdr list)))
  )
)

; test: (mainGetFirst `(1 2 (3 (4 5) (6 7)) 8 (9 10 11))) => (1 3 9)
; test: (mainGetFirst `(0 1 2 (3 4 (5 6 7)))) => (3 5)
