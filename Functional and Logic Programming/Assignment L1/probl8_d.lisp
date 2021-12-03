; numSum(list - list)
; numSum(l1l2...ln) = 0, if n = 0
; 					= l1 + numSum(l2...ln), if l1 is a number
;					= numSum(l2...ln), otherwise

(defun numSum (list)
  (cond
    ((atom list) 0)
    ((numberp (car list)) (+ (car list) (numSum (cdr list))))
    (T (numSum (cdr list)))
  )
)

; test: (numsum '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))) => 11
