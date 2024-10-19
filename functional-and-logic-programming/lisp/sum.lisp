(defun sumNum (L)
    (cond
        ((numberp L) L)
        ((atom L) 0)
        (T (apply #'+ (mapcar #'sumNum L)))
    )
)


(print (sumNum '(1 2 3 4))) ;10
(print (sumNum '(1 2 (3 4)))) ;10
(print (sumNum '(A (2 G) 3 (4 A X (Y 100)) 2 A 3 (F E)))) ;114