CREATE OR ALTER PROCEDURE uspRunTest(@testName VARCHAR(max))
AS
	DECLARE @nextTestRunId INt = (SELECT COALESCE(MAX(TR.TestRunId), 0)
								FROM TestRuns TR) + 1
	DECLARE @startTime DATETIME = GETDATE()
	
	INSERT INTO TestRuns
	VALUES ('Ran test ' + @testName, @startTime, GETDATE())

	DECLARE @testId INT
	SELECT @testId = (SELECT TOP(1) T.TestID
						FROM Tests T 
						WHERE T.Name=@testName)
	
	DECLARE @noTables INT = (SELECT COUNT(*)
							FROM TestTables TT
							WHERE TT.TestID=@testId)

	/* delete all tables, in inverse order */
	DECLARE @currPosition INT = @noTables
	WHILE @currPosition >= 1
	BEGIN
		DECLARE @tableId INT = (SELECT TT.TableID
								FROM TestTables TT
								WHERE TT.Position=@currPosition
								AND TT.TestID=@testId)
		DECLARE @tableName VARCHAR(max) = (SELECT T.Name
											FROM Tables T
											WHERE T.TableID=@tableId)
		exec('DELETE FROM ' + @tableName)

		SET @currPosition = @currPosition - 1
	END

	/* execute the inserts */
	SET @currPosition = 1
	WHILE @currPosition <= @noTables
	BEGIN
		SET @tableId = (SELECT TT.TableID
							FROM TestTables TT
							WHERE TT.Position=@currPosition
							AND TT.TestID=@testId)
		SET @tableName = (SELECT T.Name
									FROM Tables T
									WHERE T.TableID=@tableId)
		DECLARE @noRowsToAdd INT = (SELECT TT.NoOfRows
									FROM TestTables TT
									WHERE TT.TestID=@testId AND TT.TableID=@tableId)
	
		PRINT(@noRowsToAdd)
		PRINT(@tableName)

		DECLARE @insertStartTime DATETIME = GETDATE()
		EXEC uspAddRowsToTable @noRowsToAdd, @tableName 
		DECLARE @insertEndTime DATETIME = GETDATE()
		INSERT INTO TestRunTables
		VALUES (@nextTestRunId, @tableId, @insertStartTime, @insertEndTime)


		SET @currPosition = @currPosition + 1
	END


	/* run views */
	DECLARE @noViews INT = (SELECT COUNT(*)
							FROM TestViews TV
							WHERE TV.TestID=@testId)

	DECLARE viewNameCursor CURSOR FOR
		SELECT V.Name
		FROM TestViews TV
		INNER JOIN Views V ON TV.ViewId = V.ViewID
		WHERE TV.TestID=@testId

	DECLARE @viewName VARCHAR(max)
	OPEN viewNameCursor
	FETCH NEXT FROM viewNameCursor INTO @viewName
	WHILE @@FETCH_STATUS = 0
	BEGIN
		DECLARE @viewId INT
		SELECT @viewId = V.ViewID
		FROM Views V
		WHERE V.Name=@viewName 

		DECLARE @viewStartTime DATETIME = GETDATE()
		exec('SELECT * FROM ' + @viewName)
		INSERT INTO TestRunViews
		VALUES (@nextTestRunId, @viewId, @viewStartTime, GETDATE())

		FETCH NEXT FROM viewNameCursor INTO @viewName
	END

	CLOSE viewNameCursor
	DEALLOCATE viewNameCursor


	/* delete again */
	SET @currPosition = @noTables
	WHILE @currPosition >= 1
	BEGIN
		SET @tableId = (SELECT TT.TableID
								FROM TestTables TT
								WHERE TT.Position=@currPosition
								AND TT.TestID=@testId)
		SET @tableName = (SELECT T.Name
											FROM Tables T
											WHERE T.TableID=@tableId)
		exec('DELETE FROM ' + @tableName)

		SET @currPosition = @currPosition - 1
	END

	DECLARE @endTime DATETIME = GETDATE()

	UPDATE TestRuns 
	SET EndAt = GETDATE()
	WHERE StartAt = @startTime
GO

uspRunTest 'Another'
GO

