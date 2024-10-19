/* nonclustered index scan */
SELECT *
FROM TA

/* clustered index seek */
SELECT *
FROM TA
WHERE TA.aid > 1

/* clustered index scan, seek */
SELECT *
FROM TA INNER JOIN TC ON TA.aid = TC.aid

/* non clustered index seek */
CREATE NONCLUSTERED INDEX SOMEINDEX
ON TC(bid, cid) INCLUDE (aid)

SELECT TC.aid
FROM TC
WHERE TC.bid = 1 AND TC.cid > 0

DROP INDEX TC.SOMEINDEX


/* key lookup */
CREATE NONCLUSTERED INDEX LOOKUP_INDEX ON TB(b2)
GO

SELECT *
FROM TB INNER JOIN TC ON TB.b2=TC.bid
WHERE TB.b2 > 1 

DROP INDEX TB.LOOKUP_INDEX



/* b. */
/* without index: clustered index scan */
/* with: nonclustered index scan */

CREATE NONCLUSTERED INDEX BINDEX
ON TB(bid) INCLUDE (b2)

SELECT TB.bid
FROM TB 
WHERE TB.b2 = 1

DROP INDEX TB.BINDEX
GO

/* c. */
/* without indexes: clustered index scan, seek */
/* with index TB.BINDEX: clustered index scan, nonclustered index seek */

CREATE OR ALTER VIEW SOMEVIEW AS
SELECT TB.bid
FROM TB INNER JOIN TC ON TB.bid = TC.bid
WHERE TB.b2 = 1
GO

SELECT * FROM SOMEVIEW










