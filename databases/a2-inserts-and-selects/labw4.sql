INSERT INTO REGIONAL_AGENCIES(region, noTerritories)
VALUES	('Transylvania', 14),
		('Moldavia', 13),
		('Wallachia', 13)

GO

/* transylvania */
INSERT INTO LOCAL_AGENCIES(laCity, lBudget, RId)
VALUES	('Cluj-Napoca', 300 * 1000, (SELECT RId FROM REGIONAL_AGENCIES WHERE region='Transylvania')),
		('Baia Mare', 70 * 1000, (SELECT RId FROM REGIONAL_AGENCIES WHERE region='Transylvania')),
		('Brasov', 120 * 1000, (SELECT RId FROM REGIONAL_AGENCIES WHERE region='Transylvania'))

/* moldavia */
INSERT INTO LOCAL_AGENCIES(laCity, lBudget, RId)
VALUES	('Iasi', 200 * 1000, (SELECT RId FROM REGIONAL_AGENCIES WHERE region='Moldavia')),
		('Vaslui', 30 * 1000, (SELECT RId FROM REGIONAL_AGENCIES WHERE region='Moldavia'))

/* wallachia */
INSERT INTO LOCAL_AGENCIES(laCity, lBudget, RId)
VALUES	('Bucharest', 500 * 1000, (SELECT RId FROM REGIONAL_AGENCIES WHERE region='Wallachia')),
		('Calarasi', 20 * 1000, (SELECT RId FROM REGIONAL_AGENCIES WHERE region='Wallachia'))


INSERT INTO HOSPITALS(hName, hCity, hCap)
VALUES	('Cluj Regional Hospital', 'Cluj-Napoca', 500),
		('Moldova Care', 'Iasi', 200),
		('Cluj Small Hospital', 'Turda', 300),
		('The National Hospital', 'Bucharest', 2300),
		('Wallachia Care', 'Bucharest', 4200)
		

INSERT INTO DOCTORS(drName, drExp)
VALUES	('Iulian Popescu-Cezar', 7),
		('Octavian Ionescu-Augustus', 41),
		('Ion al Glanetasului', 10),
		('Lucian-Septimiu Severus', 1),
		('David Lauran', 38)
		
GO

INSERT INTO PRACTICES_AT(DId, HId, paSince)
VALUES ((SELECT DId FROM DOCTORS WHERE drName='Iulian Popescu-Cezar'), (SELECT HId FROM HOSPITALS WHERE hName='Cluj Regional Hospital'), '2018-02-17'),
		((SELECT DId FROM DOCTORS WHERE drName='Iulian Popescu-Cezar'), (SELECT HId FROM HOSPITALS WHERE hName='Moldova Care'), '2021-02-23'),
		((SELECT DId FROM DOCTORS WHERE drName='Octavian Ionescu-Augustus'), (SELECT HId FROM HOSPITALS WHERE hName='Moldova Care'), '2022-12-09'),
		((SELECT DId FROM DOCTORS WHERE drName='Octavian Ionescu-Augustus'), (SELECT HId FROM HOSPITALS WHERE hName='Cluj Small Hospital'), '1986-08-09'),
		((SELECT DId FROM DOCTORS WHERE drName='Ion al Glanetasului'), (SELECT HId FROM HOSPITALS WHERE hName='The National Hospital'), '2015-01-09'),
		((SELECT DId FROM DOCTORS WHERE drName='Lucian-Septimiu Severus'), (SELECT HId FROM HOSPITALS WHERE hName='Wallachia Care'), '2023-04-09')

INSERT INTO PATIENTS(pName, patAge, IPId)
VALUES ('Lefter Popescu', 32, NULL),
		('Maria Popescu', 27, NULL),
		('Florin Popescu', 13, NULL)

INSERT INTO AGENTS(aName, aExp, LId, inBranchSince)
VALUES ('James Red', 6, (SELECT LId FROM LOCAL_AGENCIES WHERE laCity='Cluj-Napoca'), '2020-01-01'),
		('Rick Cameron', 11, (SELECT LId FROM LOCAL_AGENCIES WHERE laCity='Bucharest'), '2015-01-09'),
		('Anne Smith', 4, (SELECT LId FROM LOCAL_AGENCIES WHERE laCity='Iasi'), '2022-01-13')

INSERT INTO CASES(cType, cSum, cDate, DId, HId, PId, victimFiledComplaint)
VALUES ('bribery', 30000, '2006-02-03', (SELECT DId FROM DOCTORS WHERE drName='Octavian Ionescu-Augustus'), (SELECT HId FROM HOSPITALS WHERE hName='Cluj Small Hospital'),
			(SELECT PId FROM PATIENTS WHERE pName='Lefter Popescu'), 1),
		('bribery', 125000, '2022-12-10', (SELECT DId FROM DOCTORS WHERE drName='Octavian Ionescu-Augustus'), (SELECT HId FROM HOSPITALS WHERE hName='Moldova Care'),
			(SELECT PId FROM PATIENTS WHERE pName='Lefter Popescu'), 1),

		('bribery', 28000, '2023-08-13', (SELECT DId FROM DOCTORS WHERE drName='Lucian-Septimiu Severus'), (SELECT HId FROM HOSPITALS WHERE hName='Wallachia Care'),
			(SELECT PId FROM PATIENTS WHERE pName='Maria Popescu'), 0),
		('bribery', 17000, '2022-02-13', (SELECT DId FROM DOCTORS WHERE drName='Iulian Popescu-Cezar'), (SELECT HId FROM HOSPITALS WHERE hName='Moldova Care'),
			(SELECT PId FROM PATIENTS WHERE pName='Lefter Popescu'), 1),

		('malpraxis', NULL, '2022-02-13', (SELECT DId FROM DOCTORS WHERE drName='Ion al Glanetasului'), (SELECT HId FROM HOSPITALS WHERE hName='The National Hospital'),
			(SELECT PId FROM PATIENTS WHERE pName='Florin Popescu'), 0)



/* will violate integrity constraints: doctor does not practice at hospital*/
INSERT INTO CASES(cType, cSum, cDate, DId, HId, PId, victimFiledComplaint)
VALUES ('bribery', 30000, '2006-02-03', (SELECT DId FROM DOCTORS WHERE drName='Iulian Popescu-Cezar'), (SELECT HId FROM HOSPITALS WHERE hName='Cluj Small Hospital'),
			(SELECT PId FROM PATIENTS WHERE pName='Lefter Popescu'), 1)
/* end of invalid statements */



INSERT INTO INVESTIGATES(AId, CId)
VALUES ((SELECT AId FROM AGENTS WHERE aName='James Red'), (SELECT CId FROM CASES WHERE cSum=28000)),
		((SELECT AId FROM AGENTS WHERE aName='James Red'), (SELECT CId FROM CASES WHERE cSum=17000)),
		((SELECT AId FROM AGENTS WHERE aName='Anne Smith'), (SELECT CId FROM CASES WHERE cSum=30000))


/* A */

/* patients who are old (>70) or don't have insurance */
SELECT *
FROM PATIENTS P
WHERE P.patAge > 70
UNION
SELECT *
FROM PATIENTS P
WHERE P.IPId IS NULL

/* cases where the victim filed complaint or the sum is >=100.000 */
SELECT *
FROM CASES C
WHERE C.victimFiledComplaint = 1 OR C.cSum >= 100000


/* B */

/* cases where the victim didn't file complaint and the sum is >=100.000 */
SELECT *
FROM CASES C
WHERE C.victimFiledComplaint = 1
INTERSECT
SELECT *
FROM CASES C
WHERE C.cSum >= 100000

/* malpraxis cases where the doctor is young (<=7 yrs of exp) */
SELECT *
FROM CASES C 
WHERE C.cType = 'malpraxis'
AND C.DId IN (
	SELECT D.DId
	FROM DOCTORS D
	WHERE D.drExp <= 7
)


/* C */

/* experienced doctors (>=20 yrs of exp) with no cases */
SELECT D.DId
FROM DOCTORS D
WHERE D.drExp >= 20
EXCEPT
SELECT C.DId
FROM CASES C

/* hospitals in whose cities there isn't a local agency */
SELECT H.HId, H.hName, H.hCity
FROM HOSPITALS H
WHERE H.hCity NOT IN (
	SELECT L.laCity
	FROM LOCAL_AGENCIES L
)


/* D */

/* doctors without a job */
SELECT D.DId, D.drName
FROM DOCTORS D LEFT JOIN PRACTICES_AT PA ON D.DId = PA.DId
WHERE PA.HId IS NULL

/* agencies in cities without hospitals, ordered by the agency's budget (top 3) */
SELECT TOP 3 L.LId, L.laCity
FROM HOSPITALS H RIGHT JOIN LOCAL_AGENCIES L ON H.hCity = L.laCity
WHERE H.HId IS NULL
ORDER BY L.lBudget DESC

/* top 3 patient, doctor pairs (ordered by number of cases) */
SELECT TOP 3 C.PId, P.pName, C.DId, D.drName, COUNT(*) AS noMeetings
FROM PATIENTS P INNER JOIN CASES C ON P.PId = C.PId INNER JOIN DOCTORS D ON C.DId = D.DId
GROUP BY C.PId, P.pName, C.DId, D.drName
ORDER BY noMeetings DESC

/* doctors/hospitals without the other */
SELECT D.DId, D.drName, H.HId, H.hName
FROM DOCTORS D FULL JOIN HOSPITALS H ON EXISTS (
	SELECT *
	FROM PRACTICES_AT PA
	WHERE PA.DId = D.DId AND PA.HId = H.HId
)
EXCEPT
SELECT D.DId, D.drName, H.HId, H.hName
FROM DOCTORS D INNER JOIN HOSPITALS H ON EXISTS (
	SELECT *
	FROM PRACTICES_AT PA
	WHERE PA.DId = D.DId AND PA.HId = H.HId
)

/* all (agent, hospital_having_doctor_investigated_by_agent) pairs */
SELECT DISTINCT
(
	SELECT A.aName
	FROM AGENTS A
	WHERE A.AId = I.AId
) AS aName, 
(
	SELECT H.hName
	FROM HOSPITALS H
	WHERE H.HId = PA.HId
) AS hName
FROM PRACTICES_AT PA INNER JOIN INVESTIGATES I ON PA.DId=(
	SELECT C.DId
	FROM CASES C
	WHERE C.CId = I.CId
)


/* E */
/* see B.2 or C.2 */

/* doctors who work in hospitals which don't have a local agency in their city */
SELECT DISTINCT PA.DId
FROM PRACTICES_AT PA
WHERE PA.HId IN (
	/* ids of hospitals in cities without local agency */
	SELECT H.HId
	FROM HOSPITALS H
	WHERE H.hCity NOT IN (
		SELECT L.laCity
		FROM LOCAL_AGENCIES L
	)
)

/* F */
/* all hospitals with investigated doctors (the case's hospital does not matter) */
SELECT DISTINCT PA.HId
FROM PRACTICES_AT PA
WHERE EXISTS (
	SELECT *
	FROM CASES C
	WHERE C.DId = PA.DId
)

/* agents who have joined their branch on the same day a doctor has joined one of their hospitals  */
SELECT *
FROM AGENTS A
WHERE EXISTS (
	SELECT *
	FROM PRACTICES_AT PA
	WHERE PA.paSince = A.inBranchSince
)


/* G */
/* the highest average bribe for any hospital */
SELECT MAX(avgBribe) / 1000 as maxAvgBribeInThousands
FROM (
	SELECT C.HId, AVG(C.cSum) AS avgBribe
	FROM CASES C
	GROUP BY C.HId
) t

/* the lowest average number of beds for any city*/
SELECT MIN(avgBeds) / 100 as minAvgBedsInHundreds
FROM (
	SELECT H.hCity, AVG(H.hCap) AS avgBeds
	FROM HOSPITALS H
	GROUP BY H.hCity
) t


/* H */

/* at how many hospitals each doctor works */
SELECT PA.DId, COUNT(*)
FROM PRACTICES_AT PA
GROUP BY PA.DId

/* hospitals where the average bribe is higher than the global average */
SELECT (
	SELECT H.hName
	FROM HOSPITALS H
	WHERE H.HId = C.HId
) AS hName, AVG(C.cSum) AS avgBribe
FROM CASES C
GROUP BY C.HId
HAVING AVG(C.cSum) > (
	SELECT AVG(C2.cSum)
	FROM CASES C2
)

/* patients who have given more than 10% of our total local budgets in bribes */
SELECT (
	SELECT P.pName 
	FROM PATIENTS P
	WHERE P.PId = C.PId
), SUM(C.cSum) AS totalBribes
FROM CASES C
GROUP BY C.PId
HAVING SUM(C.cSum) * 10 > (
	SELECT SUM(L.lBudget)
	FROM LOCAL_AGENCIES L
)

/* for new doctors (<=7 exp), what is the maximum sum each has taken as bribe */
/* note: can be rewritten with where */
SELECT C.DId, MAX(C.cSum) / 1000 AS maxBribeInThousands
FROM CASES C
GROUP BY C.DId
HAVING 7 >= (
	SELECT D.drExp
	FROM DOCTORS D
	WHERE D.DId=C.DId
)

/* cities with >=2 cases */
/* note: can be rewritten with where */
SELECT H.hCity
FROM HOSPITALS H
GROUP BY H.hCity
HAVING 2 <= (
	SELECT COUNT(*)
	FROM CASES C
	WHERE H.hCity = (
		SELECT H2.hCity
		FROM HOSPITALS H2
		WHERE H2.HId = C.HId
	)
)

/* hospitals where the sum of all bribes > capacity * 50 */
SELECT H.HId, H.hName, hCap, SUM(C.cSum) AS Total_bribes
FROM CASES C INNER JOIN HOSPITALS H ON C.HId = H.HId
GROUP BY H.HId, H.hName, H.hCap
HAVING H.hCap * 50 < SUM(C.cSum)


/* I */
/* doctors with malpraxis cases */
SELECT *
FROM DOCTORS D
WHERE D.DId = ANY(
	SELECT C.DId
	FROM CASES C
	WHERE C.cType = 'malpraxis'
)

/* local agencies with the budget equal to a bribe */
SELECT *
FROM LOCAL_AGENCIES L
WHERE L.lBudget = ANY(
	SELECT C.cSum
	FROM CASES C 
)

/* hospitals which could provide 100 beds per territory for any region */
SELECT *
FROM HOSPITALS H
WHERE H.hCap / 100 >= ALL(
	SELECT R.noTerritories
	FROM REGIONAL_AGENCIES R
)

/* agents with less experience than all doctors */
SELECT *
FROM AGENTS A
WHERE A.aExp < ALL(
	SELECT D.drExp
	FROM DOCTORS D
)


/* I.rewritten */
/* doctors with malpraxis cases */
SELECT *
FROM DOCTORS D
WHERE D.DId IN (
	SELECT C.DId
	FROM CASES C
	WHERE C.cType = 'malpraxis'
)

/* local agencies with the budget equal to a bribe */
SELECT *
FROM LOCAL_AGENCIES L
WHERE L.lBudget IN (
	SELECT C.cSum
	FROM CASES C 
)

/* hospitals which could provide 100 beds per territory for any region */
SELECT *
FROM HOSPITALS H
WHERE H.hCap / 100 >= (
	SELECT MAX(R.noTerritories)
	FROM REGIONAL_AGENCIES R
)

/* agents with less experience than all doctors */
SELECT *
FROM AGENTS A
WHERE A.aExp < (
	SELECT MIN(D.drExp)
	FROM DOCTORS D
)
