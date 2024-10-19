
/*
INSERT INTO InsertDemo 
 VALUES ('Jack','2000-02-10',5,'London','56552244'),
        ('Daniel','2000-07-24',5,'Oxford','56448899'),
        ('Gonzalo','2000-01-13',5,'Cambridge','56254896')
*/
CREATE OR ALTER PROCEDURE getRandomint(@randomElement VARCHAR(max) OUTPUT)
AS
BEGIN
	SET @randomElement = CAST(FLOOR(RAND() * 10) AS VARCHAR(max))
	/*RETURN CAST(ABS(CHECKSUM(NewId())) % 1000 AS VARCHAR(max))*/
END
GO

CREATE OR ALTER PROCEDURE getRandomvarchar(@randomElement VARCHAR(max) OUTPUT)
AS
BEGIN
	SET @randomElement = '''' + SUBSTRING(CONVERT(VARCHAR(max), NEWID()), 1, 10) + ''''	
END
GO

CREATE OR ALTER PROCEDURE getRandomdate(@randomElement VARCHAR(max) OUTPUT)
AS
BEGIN
	SET @randomElement = '''' + CAST(CAST(DATEADD(day, (ABS(CHECKSUM(NEWID())) % 65530), 0) AS DATE) AS VARCHAR(max)) + '''' /* 1900...2079 */
END
GO


CREATE OR ALTER PROCEDURE getRandomElement(@dataType VARCHAR(max), @randomElement VARCHAR(max) OUTPUT)
AS
BEGIN
	SET @randomElement = ''
	/*EXEC getRandomint @randomElement = @randomElement OUTPUT*/
	/*PRINT('EXEC getRandom' + @dataType + ' @randomElement = @randomElement OUTPUT')*/
	DECLARE @execCode NVARCHAR(max)
	SET @execCode = 'EXEC getRandom' + @dataType + ' @randomElement OUTPUT'
	EXEC sp_executesql @execCode, N'@randomElement VARCHAR(max) OUTPUT', @randomElement OUTPUT
END
GO

CREATE OR ALTER PROCEDURE getWhatItReferences(@tableName VARCHAR(max), @colName VARCHAR(max), @refdTable VARCHAR(max) OUTPUT, @refdcol VARCHAR(max) OUTPUT)
AS
BEGIN
	SELECT 
    /*FK.name AS ForeignKeyName,*/
    @refdTable = T2.name,
    @refdCol = C2.name
	FROM sys.foreign_keys FK
	INNER JOIN sys.tables T1 ON FK.parent_object_id = T1.object_id
	INNER JOIN sys.tables T2 ON FK.referenced_object_id = T2.object_id
	INNER JOIN sys.foreign_key_columns FKC ON FKC.constraint_object_id = FK.object_id
	INNER JOIN sys.columns C1 ON FKC.parent_column_id = C1.column_id AND FKC.parent_object_id = C1.object_id
	INNER JOIN sys.columns C2 ON FKC.referenced_column_id = C2.column_id AND FKC.referenced_object_id = C2.object_id
	WHERE T1.name = @tableName AND C1.name = @colName
END
GO

/*DECLARE @refdTable VARCHAR(max)
DECLARE @refdCol VARCHAR(max)
EXEC getWhatItReferences 'LOCAL_AGENCIES', 'RId', @refdTable=@refdTable OUTPUT, @refdCol=@refdCol OUTPUT
PRINT(@refdTable)
PRINT(@refdCol)
GO*/

CREATE OR ALTER PROCEDURE getRandomValueForTable(@tableName VARCHAR(50), @valueForQuery VARCHAR(max) OUTPUT)
AS
BEGIN
	SET @valueForQuery = '('

	DECLARE @noCols INT = (SELECT MAX(ORDINAL_POSITION)
							FROM INFORMATION_SCHEMA.COLUMNS
							WHERE TABLE_NAME = @tableName)

	DECLARE @currCol INT = 1
	WHILE @currCol <= @noCols 
	BEGIN
		PRINT(@currCol)
		DECLARE @colName VARCHAR(max) = (SELECT COLUMN_NAME
											FROM INFORMATION_SCHEMA.COLUMNS
											WHERE TABLE_NAME = @tableName AND ORDINAL_POSITION = @currCol)
		DECLARE @dataType VARCHAR(max) = (SELECT DATA_TYPE
											FROM INFORMATION_SCHEMA.COLUMNS
											WHERE TABLE_NAME = @tableName AND ORDINAL_POSITION = @currCol)

		/* if identity, skip it */
		IF (SELECT columnproperty(object_id(@tableName), @colName, 'IsIdentity')) = 1
		BEGIN
			SET @currCol = @currCol + 1
			CONTINUE
		END

		DECLARE @randomElement VARCHAR(max)
		EXEC getRandomElement @dataType, @randomElement = @randomElement OUTPUT 
		IF EXISTS (SELECT *
					FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE
					WHERE COLUMN_NAME = @colName)
		BEGIN
			/* the column appears in a key */
			/* keep generating until it didn't appear already */

			DECLARE @elementAppearsAlready INT = 0
			DECLARE @querySearchingElement NVARCHAR(max) = N'SELECT @elementAppearsAlready = COUNT(*) FROM ' + @tableName + ' WHERE ' + @colName + ' = @randomElement'
			/*exec('SELECT @elementAppearsAlready = COUNT(*) FROM ' + @tableName + ' WHERE ' + @colName + '=' + @randomElement + ')')*/
			EXEC sp_executesql @querySearchingElement, N'@randomElement VARCHAR(max), @elementAppearsAlready INT OUTPUT', @randomElement, @elementAppearsAlready OUTPUT

			WHILE @elementAppearsAlready > 0
			BEGIN
				EXEC getRandomElement @dataType, @randomElement = @randomElement OUTPUT 
				
				/*exec('SELECT @elementAppearsAlready = COUNT(*) FROM ' + @tableName + ' WHERE ' + @colName + '=' + @randomElement + ')')*/
				EXEC sp_executesql @querySearchingElement, N'@randomElement VARCHAR(max), @elementAppearsAlready INT OUTPUT', @randomElement, @elementAppearsAlready OUTPUT
			END
		END

		/* foreign key? */
		DECLARE @refdTable VARCHAR(max) = ''
		DECLARE @refdCol VARCHAR(max) = ''
		PRINT(@tableName + ' ' + @colName)
		EXEC getWhatItReferences @tableName, @colName, @refdTable=@refdTable OUTPUT, @refdCol=@refdCol OUTPUT
		IF @refdTable <> ''
		BEGIN
			PRINT('foreign:')
			PRINT(@refdTable)
			PRINT(@refdCol)

			DECLARE @queryInRefd NVARCHAR(MAX) 
				= N'SELECT TOP 1 @randomElement = CAST(' + @refdCol + ' AS VARCHAR(MAX))
				 FROM ' + @refdTable +
				' ORDER BY NEWID()'

			EXEC sp_executesql @queryInRefd,
							   N'@randomElement VARCHAR(MAX) OUTPUT',
							   @randomElement = @randomElement OUTPUT

			DECLARE @refdDataType VARCHAR(max) = (SELECT DATA_TYPE
												FROM INFORMATION_SCHEMA.COLUMNS
												WHERE TABLE_NAME = @refdTable AND COLUMN_NAME = @refdCol)
			IF @refdDataType <> 'int'
				SET @randomElement = '''' + @randomElement + ''''
			PRINT(@randomElement)
		END
		
		SET @valueForQuery = @valueForQuery + @randomElement
		IF @currCol < @noCols
			SET @valueForQuery = @valueForQuery + ','
		SET @currCol = @currCol + 1
	END

	SET @valueForQuery = @valueForQuery + ')'
END
GO

DECLARE @randomElement VARCHAR(max)
EXEC getRandomElement 'date', @randomElement = @randomElement OUTPUT
PRINT @randomElement
GO

DECLARE @result VARCHAR(max)
EXEC getRandomValueForTable 'PRACTICES_AT', @valueForQuery=@result OUTPUT
PRINT @result
GO
/*
DECLARE @refdTable VARCHAR(max)
DECLARE @refdCol VARCHAR(max)

EXEC getWhatItReferences 'PRACTICES_AT', 'paSince', @refdTable=@refdTable OUTPUT, @refdCol=@refdCol OUTPUT
IF @refdTable <> ''
	PRINT('not empty')
PRINT(@refdCol)*/



CREATE OR ALTER PROCEDURE uspAddRowsToTable(@noRowsToAdd INT, @tableName VARCHAR(50))
AS
	DECLARE @cntAdded INT = 0

	/*DECLARE @hugeQuery VARCHAR(max)
	SET @hugeQuery = 'INSERT INTO ' + @tableName + CHAR(10) + 'VALUES '*/

	WHILE @cntAdded < @noRowsToAdd
	BEGIN
		DECLARE @valueForQuery VARCHAR(max)
		/*SET @valueForQuery = '(12, ''Rimbaud'', ''1870-12-20'')'*/

		EXEC getRandomValueForTable @tableName, @valueForQuery = @valueForQuery OUTPUT

		/*SET @hugeQuery = @hugeQuery + @valueForQuery*/

		/*IF @cntAdded < @noRowsToAdd - 1
			SET @hugeQuery = @hugeQuery + ',' + CHAR(10)*/

		PRINT(@valueForQuery)
		exec('INSERT INTO ' + @tableName + ' VALUES ' + @valueForQuery)

		SET @cntAdded = @cntAdded + 1
	END

	/*PRINT @hugeQuery
	exec(@hugeQuery)*/
GO




EXEC uspAddRowsToTable 12, 'TalentPerAge'
GO

DECLARE @refdTable VARCHAR(max)
DECLARE @refdCol VARCHAR(max)
EXEC getWhatItReferences 'Book', 'poetName', @refdTable=@refdTable OUTPUT, @refdCol=@refdCol OUTPUT
PRINT(@refdTable)

SELECT *
FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS


DROP TABLE Poets
CREATE TABLE Poets(
	poetAge INT,
	poetName VARCHAR(50) PRIMARY KEY,
	poetBirthday DATE)

DROP TABLE Book
CREATE TABLE Book(
	isbn VARCHAR(50) PRIMARY KEY,
	someUnique INT UNIQUE,
	title VARCHAR(50),
	poetName VARCHAR(50) REFERENCES Poets(poetName))

DROP TABLE TalentPerAge
CREATE TABLE TalentPerAge(
	someUnique INT REFERENCES Book(someUnique),
	talent INT)