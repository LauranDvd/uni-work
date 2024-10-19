DROP TABLE Version_Transitions
GO

CREATE TABLE Version_Transitions(
	targetVersion INT PRIMARY KEY,
	uspUp VARCHAR(50),
	uspDown VARCHAR(50)
)
GO

INSERT INTO Version_Transitions(targetVersion, uspUp, uspDown)
VALUES (1, 'uspModifyCasesCSumToBigInt', 'uspModifyCasesCSumToInt'),
		(2, 'uspAddYearFoundedToInsuranceProviders', 'uspDropYearFoundedToInsuranceProviders'),
		(3, 'uspSetPatientsAgeDefaultTo18', 'uspDropPatientsAgeDefault'),
		(4, 'uspDropCasesForeignKeyToPracticesAt', 'uspAddCasesForeignKeyToPracticesAt'),
		(5, 'uspDropDIdHIdAsPrimaryKeyInPracticesAt', 'uspAddDIdHIdAsPrimaryKeyInPracticesAt'),
		(6, 'uspAddCandidateKeyRegionInRegionalAgencies', 'uspDropCandidateKeyRegionInRegionalAgencies'),
		(7, 'uspCreateCentralAgencyTable', 'uspDropCentralAgencyTable')
GO


DROP TABLE Current_Version
GO

CREATE TABLE Current_Version(
	currVersion INT
)
GO

INSERT INTO Current_Version(currVersion) VALUES(0)
GO

CREATE PROCEDURE goToVersion(@goalVersion INT)
AS
	DECLARE @currVersion INT

	SELECT @currVersion = currVersion
	FROM Current_Version

	WHILE @currVersion <> @goalVersion 
	BEGIN
		DECLARE @toExecute VARCHAR(50)

		IF @currVersion < @goalVersion 
		BEGIN
			SELECT @toExecute=uspUp
			FROM Version_Transitions
			WHERE targetVersion = @currVersion + 1

			EXEC @toExecute

			SET @currVersion = @currVersion + 1
		END
		ELSE
		BEGIN
			SELECT @toExecute=uspDown
			FROM Version_Transitions
			WHERE targetVersion=@currVersion

			EXEC @toExecute

			SET @currVersion = @currVersion - 1
		END
	END

	UPDATE Current_Version
	SET currVersion = @goalVersion
GO

EXEC goToVersion 1
