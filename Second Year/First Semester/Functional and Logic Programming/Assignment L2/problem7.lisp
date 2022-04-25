#||
    Assignment L2 - Problem 7:
    Return the level of a node X in a tree of type (1). The level of the root element is 0.

    cadr(x) = car(cdr(x))
    cddr(x) = cdr(cdr(x))
||#


#||
    chooseLevel1(lvl1, lvl2) = -1,       if lvl1 = lvl2 = -1
                             = lvl2 + 1, if lvl1 = -1
                             = lvl1 + 1, if lvl2 = -1
                             = lvl1 + 1, if (lvl1 < lvl2)
                             = lvl2 + 1, otherwise
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

#||
    rightSubtreeHelper(t - list, vtx - number, edges - number)
    rightSubtreeHelper(t1t2...tn, vtx, edges) = the empty set, if n = 0
                                              = t1t2...tn, if vtx = edges + 1
                                              = rightSubtreeHelper(t3...tn, vtx + 1, edges + t2), otherwise
||#
(defun rightSubtreeHelper (tree vtx edges)
    (cond
        ((null tree) nil)
        ((= vtx (+ 1 edges)) tree)
        (t  (rightSubtreeHelper (cddr tree) (+ 1 vtx) (+ (cadr tree) edges)))
    )
)

#||
    rightSubtree(t1t2...tn) = rightSubtreeHelper(t3...tn, 0, 0)
||#
(defun rightSubtree (tree)
    (rightSubtreeHelper (cddr tree) 0 0)
)

#||
    callAndBind(x1x2, node) = level1(x2, node, 0, 0)
||#
(defun callAndBind (x node)
    (setq y (level1 (cadr x) node 0 0))
    y
)

#||
    level1(t - list, node - atom, vtx - number, edges - number)
    level1(t1t2...tn, node, vtx, edges) = {-1, the empty set}, if n = 0
                                        = {0, rightSubtree(t1t2...tn)}, if t1 = node
                                        = {-1, t1t2...tn}, if vtx = edges + 1
                                        = {-1, t3...tn}, if t2 = 0
                                        = {chooseLevel1(-1, r1), r2}, where r1r2 = level1(t3...tn, node, vtx + 1, edges + 1), if t2 = 1
                                        = {chooseLevel(x1, cb1), y2}, where 
                                            x1x2 = level1(t3...tn, node, 0, 0) and y1y2 = callAndBind(x, node), otherwise (if t2 = 2)
||#
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
(level1Main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 1 k 0 h 0) 'K)

