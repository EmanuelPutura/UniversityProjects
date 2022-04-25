; Assignment L2 (problem 7)

#||
    cadr(x) = car(cdr(x))
    cddr(x) = cdr(cdr(x))
||#

; the tree is (a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0). Each helper function gets applied to the list containing all its elements but for the root
; (leftSubtree '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0)) = (b 2 c 1 i 0 f 1 g 0)
(defun leftSubtreeHelper (tree vtx edges)
    (cond
        ((null tree) nil)
        ((= vtx (+ 1 edges)) nil)
        (t  (cons (car tree) (cons (cadr tree) (leftSubtreeHelper (cddr tree) (+ 1 vtx) (+ (cadr tree) edges)))))
    )
)

(defun leftSubtree (tree)
    (leftSubtreeHelper (cddr tree) 0 0)
)

(print (leftSubtree '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0)))

; (rightSubtree '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0)) = (d 2 e 1 k 0 h 0)
(defun rightSubtreeHelper (tree vtx edges)
    (cond
        ((null tree) nil)
        ((= vtx (+ 1 edges)) tree)
        (t  (rightSubtreeHelper (cddr tree) (+ 1 vtx) (+ (cadr tree) edges)))
    )
)

(defun rightSubtree (tree)
    (rightSubtreeHelper (cddr tree) 0 0)
)

(print (rightSubtree '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0)))

; (subtrees '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0) 0 0) = ((B 2 C 1 I 0 F 1 G 0) (D 2 E 1 K 0 H 0))
(defun subtreesHelper (tree vtx edges)
    (cond
        ((null tree) nil)
        ((= vtx (+ 1 edges)) tree)
        ((= (+ 1 vtx) (+ (cadr tree) (+ 1 edges))) (list (list (car tree) (cadr tree)) (subtreesHelper (cddr tree) (+ 1 vtx) (+ (cadr tree) edges))))
        (t 
            (setq rec (subtreesHelper (cddr tree) (+ 1 vtx) (+ (cadr tree) edges)))
            (setq left (car rec))
            (setq right (cadr rec))
            (list (cons (car tree) (cons (cadr tree) left)) right)
        )
    )
)

(defun subtrees (tree)
    (subtreesHelper (cddr tree) 0 0)
)

(print (subtrees '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0)))



