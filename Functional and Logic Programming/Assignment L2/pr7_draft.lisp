#||
    Assignment L2 - Problem 7:
    Return the level of a node X in a tree of type (1). The level of the root element is 0.

    cadr(x) = car(cdr(x))
    cddr(x) = cdr(cdr(x))
||#

(defun chooseLevel1 (lvl1 lvl2)
    (cond
        ((and (= lvl1 -1) (= lvl2 -1)) -1)
        ((= lvl1 -1) (+ 1 lvl2))
        ((= lvl2 -1) (+ 1 lvl1))
        ((< lvl1 lvl2) (+ 1 lvl1))
        (t (+ 1 lvl2))
    )
)

(defun level1 (tree node vtx edges)
    (cond
        ((null tree) (list -1 nil))
        ((eq (car tree) node) (list 0 (cddr tree)))
        ((eq vtx (+ 1 edges)) (list -1 tree))
        ((eq (cadr tree) 0) (list -1 (cddr tree)))
        ((eq (cadr tree) 1)
            (setq rcv (level1 (cddr tree) node (+ vtx 1) (+ edges 1)))
            (list (chooseLevel1 -1 (car rcv)) (cadr rcv))
        )
        ((eq (cadr tree) 2)
            (setq rcv1 (level1 (cddr tree) node 0 0))
            (setq right (cadr rcv1))
            
            (print tree)
            (print right)
            (print "\n")
            
            (setq lvl1 (car rcv1))
            (setq rcv2 (level1 right node 0 0))
            (setq lvl2 (car rcv2))
            
            (print tree)
            (print right)
            (print "\n")
            ;(print lvl1)
            ;(print lvl2)
            ;(print (cddr tree))
            ;(print node)
            
            (setq res (chooseLevel1 lvl1 lvl2))
            
            ;(print res)
            
            (list res (cadr rcv2))
        )
    )
)

;(print (level1 '(e 1 i 0 h 0) 'E 0 0))
;(print (level1 '(d 2 e 1 i 0 h 0) 'E 0 0))
;(print (level1 '(c 1 i 0 f 1 g 0 d 2 e 1 i 0 h 0) 'E 0 0))
;(print (level1 '(B 2 C 1 I 0 F 1 G 0 D 2 E 1 I 0 H 0) 'E 0 0))
(print (level1 '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 i 0 h 0) 'E 0 0))

#||
(print (level1 '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 i 0 h 0) 'A 0 0))
(print (level1 '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 i 0 h 0) 'B 0 0))
(print (level1 '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 i 0 h 0) 'C 0 0))
(print (level1 '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 i 0 h 0) 'D 0 0))
(print (level1 '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 i 0 h 0) 'E 0 0))
(print (level1 '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 i 0 h 0) 'F 0 0))
(print (level1 '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 i 0 h 0) 'G 0 0))
(print (level1 '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 i 0 h 0) 'H 0 0))
(print (level1 '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 i 0 h 0) 'I 0 0))
||#

