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

(defun level1 (tree node vtx edges)
    (cond
        ((null tree) (list -1 nil))
        ((eq (car tree) node) (list 0 (rightSubtree tree)))
        ((eq vtx (+ 1 edges)) (list -1 tree))
        ((eq (cadr tree) 0) (list -1 (cddr tree)))
        ((eq (cadr tree) 1)
            (setq rcv (level1 (cddr tree) node (+ vtx 1) (+ edges 1)))
            (list (chooseLevel1 -1 (car rcv)) (cadr rcv))
        )
        ((eq (cadr tree) 2)
            (setq x (level1 (cddr tree) node 0 0))
            (list (chooseLevel1 (car x) (car (callAndBind x node))) (cadr y))
            ;(list (chooseLevel1 (car (level1 (cddr tree) node 0 0)) (car (level1 (cadr (level1 (cddr tree) node 0 0)) node 0 0))) (cadr (level1 (cadr (level1 (cddr tree) node 0 0)) node 0 0)))
        )
    )
)

(defun callAndBind (x node)
    (setq y (level1 (cadr x) node 0 0))
    y
)

(defun level1Main (tree node)
    (format t "The level of the node ~D from the tree ~D is ~D.~%" node tree (car (level1 tree node 0 0)))
)

(level1Main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0) 'A)
(level1Main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0) 'B)
(level1Main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0) 'C)
(level1Main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0) 'D)
(level1Main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0) 'E)
(level1Main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0) 'F)
(level1Main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0) 'G)
(level1Main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0) 'H)
(level1Main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0) 'I)
