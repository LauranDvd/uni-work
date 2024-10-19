/* delete bribery cases */
DELETE FROM CASES WHERE cType='bribery'

/* delete doctors who aren't practicing anywhere */
DELETE FROM DOCTORS WHERE DId NOT IN (
	SELECT PA.DId
	FROM PRACTICES_AT PA
)

/* delete small bribery cases */
DELETE FROM CASES WHERE cSum IS NOT NULL AND cSum < 1000

/* delete the doctors whose names sound Roman */
DELETE FROM DOCTORS WHERE drName LIKE '%us'


/* increment no territories of regional agency */
UPDATE REGIONAL_AGENCIES 
SET noTerritories = noTerritories+1
WHERE RId = 2

/* double the budgets of all local agencies which are part of a certain regional agency */
UPDATE LOCAL_AGENCIES
SET lBudget = lBudget * 2
WHERE RId = 2

/* assign a certain insurance provider to all elementary school children */
UPDATE PATIENTS
SET IPId = 3
WHERE patAge BETWEEN 7 AND 11
