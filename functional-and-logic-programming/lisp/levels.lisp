(defun getLen (L)
    (cond
        ((null L) 0)
        (t (+ 1 (getLen (cdr L))))
    )
)

(defun decremFirst (L)
    (cond
        (t (cons (- (car L) 1) (cdr L)))
    )
)

(defun deleteLeadZeros (L)
    (cond 
        ((null L) L)
        ((eq (car L) 0) (deleteLeadZeros (cdr L)))
        (T L)
    )
)


(defun levelAux (L X S)
    (cond
        ((eq X (car L)) (getLen (deleteLeadZeros S)))
        (T (levelAux 
                (cdr (cdr L)) 
                X 
                (cons 
                    (car (cdr L))
                    (decremFirst (deleteLeadZeros S))
                    )))
    )
)

(defun level (L X)
    (cond 
        ((eq X (car L)) 0)
        (T (levelAux (cdr (cdr L)) X (list (car (cdr L)))))
    )
)


(print (level '(A 3 B 2 C 0 D 0 E 3 J 1 M 0 K 0 L 0 F 1 G 1 H 1 I 0) 'M))
