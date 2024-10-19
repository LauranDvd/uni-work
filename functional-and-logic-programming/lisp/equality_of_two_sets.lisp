(DEFUN INSELEM (L POS ELEM)
  (COND
    ((EQUAL POS 1) (CONS ELEM L))
    (T (CONS (CAR L) (INSELEM (CDR L) (- POS 1) ELEM)))
  )
)

(DEFUN ATOMSUM (L)
  (COND
    ((NULL L) 0)
    ((NUMBERP (CAR L)) (+ (CAR L) (ATOMSUM (CDR L))))
    ((ATOM (CAR L)) (ATOMSUM (CDR L)))
    ((LISTP (CAR L)) (+ (ATOMSUM (CAR L)) (ATOMSUM (CDR L))))
  )
)

(DEFUN ALLSUBS (L)
  (COND
    ((NULL L) '())
    
    ((LISTP (CAR L)) (APPEND (LIST (CAR L)) (ALLSUBS (CAR L)) (ALLSUBS (CDR L))))
    
    (T (ALLSUBS (CDR L)))
  )
)

(DEFUN GETSIZE (A)
(COND 
  ((NULL A) 0)
  (T (+ 1 (GETSIZE (CDR A))))
))

(DEFUN APPEARS (X L)
;(print X)
(COND 
  ((NULL L) nil)
  ((EQ X (CAR L)) T)
  (T (APPEARS X (CDR L)))
))

(DEFUN ALLAPPEAR (SMALL BIG)
(COND
  ((NULL SMALL) T)
  (T (AND (APPEARS (CAR SMALL) BIG) (ALLAPPEAR (CDR SMALL) BIG)))
))

(DEFUN EQUALSETS (A B)
  (COND
    ((AND (ALLAPPEAR A B) (EQ (GETSIZE A) (GETSIZE B))) T)
    (T nil)
  )
)


(print (INSELEM '(2 3 4) 4 77))
(print (ATOMSUM '((1 2 3) ((4 "f" (5)) 6))))
(print (ALLSUBS '((1 2 3) ((4 5) 6)) ))
;(print (APPEARS 5 '(1 2 4 3)))
;(print (ALLAPPEAR '(6 3 2) '(1 2 4 3)))
(print (EQUALSETS '(1 2 3 5) '(1 2 3 4 )))





