/* do not change the order */

/* A. store CASES.cSum as bigint */
CREATE PROCEDURE uspModifyCasesCSumToBigInt
AS
	ALTER TABLE CASES
	ALTER COLUMN cSum BIGINT
GO

CREATE PROCEDURE uspModifyCasesCSumToInt
AS
	ALTER TABLE CASES
	ALTER COLUMN cSum INT
GO


/* B. add year founded to insurance providers*/
CREATE PROCEDURE uspAddYearFoundedToInsuranceProviders
AS
	ALTER TABLE INSURANCE_PROVIDERS
	ADD ipYearFounded DATE
GO

CREATE PROCEDURE uspDropYearFoundedToInsuranceProviders
AS
	ALTER TABLE INSURANCE_PROVIDERS
	DROP COLUMN ipYearFounded
GO


/* C. default of patients' age becomes 18 */
CREATE PROCEDURE uspSetPatientsAgeDefaultTo18
AS
	ALTER TABLE PATIENTS
	ADD CONSTRAINT default_patAge
	DEFAULT 18 FOR patAge
GO

CREATE PROCEDURE uspDropPatientsAgeDefault
AS
	ALTER TABLE PATIENTS
	DROP CONSTRAINT default_patAge
GO


/* F. drop from Cases the foreign key referencing (DId, HId) in Practices_At (FK_DOCTORS_HOSPITALS_CASES) */
CREATE PROCEDURE uspDropCasesForeignKeyToPracticesAt
AS
	ALTER TABLE CASES
	DROP CONSTRAINT FK_DOCTORS_HOSPITALS_CASES
GO

CREATE PROCEDURE uspAddCasesForeignKeyToPracticesAt
AS
	ALTER TABLE CASES
	ADD CONSTRAINT FK_DOCTORS_HOSPITALS_CASES FOREIGN KEY (DId, HId) REFERENCES PRACTICES_AT(DId, HId)
GO


/* D. remove (DId, HId) as primary key in Practices_At */
CREATE PROCEDURE uspDropDIdHIdAsPrimaryKeyInPracticesAt
AS
	ALTER TABLE PRACTICES_AT
	DROP CONSTRAINT PK_DOCTORS_HOSPITALS_PRACTICES
GO

CREATE PROCEDURE uspAddDIdHIdAsPrimaryKeyInPracticesAt
AS
	ALTER TABLE PRACTICES_AT
	ADD CONSTRAINT PK_DOCTORS_HOSPITALS_PRACTICES PRIMARY KEY (DId, HId)
GO

/* E. region becomes candidate key for RegionalAgencies */
CREATE PROCEDURE uspAddCandidateKeyRegionInRegionalAgencies
AS
	ALTER TABLE REGIONAL_AGENCIES
	ADD CONSTRAINT unique_region 
	UNIQUE(region)
GO

CREATE PROCEDURE uspDropCandidateKeyRegionInRegionalAgencies
AS
	ALTER TABLE REGIONAL_AGENCIES
	DROP CONSTRAINT unique_region
GO


/* G. create Central_Agency table */
CREATE PROCEDURE uspCreateCentralAgencyTable
AS
	CREATE TABLE CENTRAL_AGENCY(
		caBudget INT,
		caDirectorName VARCHAR(50)
	)
GO

CREATE PROCEDURE uspDropCentralAgencyTable
AS
	DROP TABLE CENTRAL_AGENCY
GO
