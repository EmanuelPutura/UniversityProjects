/*
	----------------------------- Random Generators -----------------------------
*/

USE FCSB;

SET NOCOUNT OFF;

SET IDENTITY_INSERT TeamCoaches ON;

DROP PROCEDURE IF EXISTS generate_random_string;
GO

CREATE PROCEDURE generate_random_string (@string VARCHAR(16) OUTPUT)
AS
BEGIN
	DECLARE @counter INT = 0;
	DECLARE @limit INT = 5 + RAND() * 15;

	SET @string = '';
	WHILE (@counter < @limit)
	BEGIN
		SET @string = @string + CHAR((RAND()*25 + 97));
		SET @counter = @counter + 1;
	END
END
GO

DROP PROCEDURE IF EXISTS generate_random_integer;
GO

CREATE PROCEDURE generate_random_integer (@low_limit INT, @max_limit INT, @integer INT OUTPUT)
AS
BEGIN
	SET @integer = @low_limit + RAND() * @max_limit;
END
GO

DROP PROCEDURE IF EXISTS row_insert;
GO

DROP FUNCTION IF EXISTS table_foreign_keys;
GO

/*
	----------------------------- Foreign Keys Retrieval -----------------------------
*/

-- Gets data related to foreign key constrints as a table
CREATE FUNCTION table_foreign_keys (@table_name NVARCHAR(MAX))
RETURNS TABLE
AS
	RETURN
		SELECT OBJECT_NAME(FK.parent_object_id) AS 'Table', OBJECT_NAME(referenced_object_id) AS 'Referenced', C.name AS 'Table Column', COL_NAME(FK.referenced_object_id,FK.referenced_column_id) AS 'Referenced Column'
		FROM sys.foreign_key_columns AS FK
		INNER JOIN sys.tables AS T ON FK.parent_object_id = T.object_id
		INNER JOIN sys.columns AS C ON FK.parent_object_id = C.object_id AND FK.parent_column_id = C.column_id
		WHERE OBJECT_NAME(FK.parent_object_id) = @table_name;	
GO

DROP PROCEDURE IF EXISTS get_foreign_key_data;
GO

-- Check if there is a FK constraint for a given table and column. If not, output params are set to null string. Else, output params are the referenced table and column
CREATE PROCEDURE get_foreign_key_data (@table NVARCHAR(MAX), @column NVARCHAR(MAX), @referenced_table NVARCHAR(MAX) OUTPUT, @referenced_column NVARCHAR(MAX) OUTPUT)
AS
BEGIN
	SET @referenced_table = '';
	SET @referenced_column = '';
	SELECT @referenced_table = Referenced, @referenced_column = [Referenced Column]
	FROM table_foreign_keys(@table)
	WHERE [Table Column] = @column;
END
GO

/*
	----------------------------- Row Insertion -----------------------------
*/

-- Inserts a single row of random data in a given table
-- Data type must be varchar or int.
CREATE PROCEDURE row_insert (@table_name varchar(50))
AS
BEGIN
	DECLARE @get_columns_query NVARCHAR(MAX) = N'
		SELECT COLUMN_NAME, DATA_TYPE
		FROM INFORMATION_SCHEMA.COLUMNS
		WHERE TABLE_NAME = ''' + @table_name + '''
	';

	DECLARE @insert_query NVARCHAR(MAX) = N'INSERT INTO ' + @table_name;

	DECLARE @columns NVARCHAR(MAX);
	DECLARE @types NVARCHAR(MAX);
	DECLARE @rows_number INT = 0;

	DECLARE @cursor_query NVARCHAR(MAX) = N'
		DECLARE @column_name NVARCHAR(MAX);
		DECLARE @data_type NVARCHAR(MAX);
		
		DECLARE columns_cursor CURSOR FOR ' + @get_columns_query + '
		OPEN columns_cursor
		FETCH columns_cursor
		INTO @column_name, @data_type;

		IF @@FETCH_STATUS = 0
		BEGIN
			SET @columns = @column_name;
			SET @types = @data_type;
			SET @rows_number = 1;
		END

		WHILE @@FETCH_STATUS = 0
		BEGIN
			FETCH columns_cursor
			INTO @column_name, @data_type;
			IF @@FETCH_STATUS = 0
			BEGIN
				SET @columns = @columns + '', '' + @column_name;
				SET @types = @types + '', '' + @data_type;
				SET @rows_number = @rows_number + 1;
			END
		END

		CLOSE columns_cursor;
		DEALLOCATE columns_cursor;
	';

	EXEC sp_executesql @Query = @cursor_query, @Params = N'@columns NVARCHAR(MAX) OUTPUT, @types NVARCHAR(MAX) OUTPUT, @rows_number INT OUTPUT', @columns = @columns OUTPUT, @types = @types OUTPUT, @rows_number = @rows_number OUTPUT;

	SET @insert_query = @insert_query + '(' + @columns + ') VALUES (';
	
	SET @types = @types + ', ';
	SET @columns = @columns + ', ';

	DECLARE @index INT = 0;
	DECLARE @current NVARCHAR(MAX);
	DECLARE @current_column NVARCHAR(MAX);
	DECLARE @identity_constraint INT = 0;

	WHILE @index < @rows_number
	BEGIN
		SET @current = LEFT(@types, CHARINDEX(', ', @types) - 1);
		SET @types = SUBSTRING(@types, CHARINDEX(', ', @types) + 2, LEN(@types));

		SET @current_column = LEFT(@columns, CHARINDEX(', ', @columns) - 1);
		SET @columns = SUBSTRING(@columns, CHARINDEX(', ', @columns) + 2, LEN(@columns));

		IF @index != 0
			SET @insert_query = @insert_query + ', ';

		DECLARE @referenced_table NVARCHAR(MAX) = '';
		DECLARE @referenced_column NVARCHAR(MAX) = '';

		EXEC get_foreign_key_data @table_name, @current_column, @referenced_table = @referenced_table OUTPUT, @referenced_column = @referenced_column OUTPUT;

		DECLARE @identity_cols INT = 0;
		SELECT @identity_cols = COUNT(*) FROM sys.identity_columns WHERE name = @current_column AND OBJECT_NAME(object_id) = @table_name;

		IF @identity_cols != 0
			SET @identity_constraint = 1;

		IF @current = 'int'
		BEGIN
			IF @referenced_table != '' AND @referenced_column != ''
			BEGIN
				DECLARE @int_value INT;

				DECLARE @int_query NVARCHAR(MAX) = N'SELECT @int_value = ' + @referenced_column + ' FROM ' + @referenced_table +
						' WHERE ' + @referenced_column + ' NOT IN (SELECT ' + @current_column + ' FROM ' + @table_name + ')';

				EXEC sp_executesql @Query = @int_query, @Params = N'@int_value INT OUTPUT', @int_value = @int_value OUTPUT;
				SET @insert_query = @insert_query + CONVERT(NVARCHAR(MAX), @int_value);
			END
			ELSE
			BEGIN
				DECLARE @integer INT;
				EXEC generate_random_integer 0, 100000000, @integer = @integer OUTPUT;
				SET @insert_query = @insert_query + CONVERT(NVARCHAR(MAX), @integer);
			END
		END

		IF @current = 'varchar'
		BEGIN
			IF @referenced_table != '' AND @referenced_column != ''
			BEGIN
				DECLARE @str_value NVARCHAR(MAX);
				DECLARE @str_query NVARCHAR(MAX) = N'SELECT @str_value = ' + @referenced_column + ' FROM ' + @referenced_table;

				EXEC sp_executesql @Query = @str_query, @Params = N'@str_value NVARCHAR(MAX) OUTPUT', @str_value = @str_value OUTPUT;
				
				SET @insert_query = @insert_query + '''' + @str_value + '''';
			END
			ELSE
			BEGIN
				DECLARE @string NVARCHAR(16);
				EXEC generate_random_string @string = @string OUTPUT;

				SET @insert_query = @insert_query + '''' + @string + '''';
			END
		END

		SET @index = @index + 1;
	END

	SET @insert_query = @insert_query + ');';
	
	/*
	IF @identity_constraint = 1
	BEGIN
		DECLARE @query NVARCHAR(MAX) = N'SET IDENTITY_INSERT ' + @table_name + ' ON;';
		PRINT @query;
		EXEC sp_executesql @query;
	END
	*/

	EXEC sp_executesql @insert_query;

	/*
	IF @identity_constraint = 1
	BEGIN
		SET @query = N'SET IDENTITY_INSERT ' + @table_name + ' OFF;';
		EXEC sp_executesql @query;
	END
	*/
END
GO

DROP PROCEDURE IF EXISTS multiple_rows_insert;
GO

-- Inserts a given number of rows of random data in a given table
-- Data type must be varchar or int.
CREATE PROCEDURE multiple_rows_insert (@table_name NVARCHAR(MAX), @counter INT)
AS
BEGIN
	WHILE @counter > 0
	BEGIN
		DECLARE @error INT = 1;

		WHILE @error != 0
		BEGIN
			SET @error = 0;
			BEGIN TRY
				EXEC row_insert @table_name;
			END TRY
			BEGIN CATCH
				SET @error = 1;
			END CATCH
		END
		SET @counter = @counter - 1;
	END
END
GO

--------------------------------------------------------

DROP PROCEDURE IF EXISTS addTest;
GO

CREATE PROCEDURE addTest (@Name NVARCHAR(MAX))
AS
BEGIN
	INSERT INTO Tests (Name)
	VALUES (@Name);
END
GO

--------------------------------------------------------

DROP PROCEDURE IF EXISTS runSingleTest;
GO

CREATE PROCEDURE runSingleTest (@test_id INT)
AS
BEGIN
	DECLARE @tests      INT =  0;
	DECLARE @table_id   INT = -1;
	DECLARE @view_id    INT = -1;
	DECLARE @rows_no    INT = -1;
	DECLARE @run_id     INT = -1;
	DECLARE @test_start DATETIME = GETDATE();

	INSERT INTO TestRuns (Description, StartAt)
	VALUES ((SELECT Name FROM Tests WHERE TestID = @test_id), @test_start);

	SELECT @run_id = TestRunID FROM TestRuns
	WHERE Description = (SELECT Name FROM Tests WHERE TestID = @test_id) AND StartAt = @test_start;

	SELECT @tests = COUNT(*) FROM Tests
	WHERE TestID = CONVERT(INT, @test_id);

	IF @tests <= 0
	BEGIN
		RAISERROR('Invalid test ID!', 10, 1);
		RETURN 
	END
	
	/*
		Run test for tables
	*/

	DECLARE @table_name NVARCHAR(MAX) = ''
	DECLARE @query NVARCHAR(MAX) = '';

	-------------------------------------------

	DECLARE TestCursor CURSOR FOR 
	SELECT TableID FROM TestTables
	WHERE TestID = CONVERT(INT, @test_id)
	ORDER BY Position;

	OPEN TestCursor
	FETCH TestCursor
	INTO @table_id;

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SELECT @table_name = Name FROM Tables
		WHERE TableID = CONVERT(INT, @table_id);

		SET @query = N'DELETE FROM ' + @table_name;
		EXEC sp_executesql @query;

		FETCH TestCursor
		INTO @table_id;
	END

	CLOSE TestCursor;
	DEALLOCATE TestCursor;

	-------------------------------------------

	DECLARE TestCursor CURSOR FOR 
	SELECT TableID, NoOfRows FROM TestTables
	WHERE TestID = CONVERT(INT, @test_id)
	ORDER BY Position DESC;

	OPEN TestCursor
	FETCH TestCursor
	INTO @table_id, @rows_no;

	DECLARE @start DATETIME;
	DECLARE @end   DATETIME;

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SELECT @table_name = Name FROM Tables
		WHERE TableID = CONVERT(INT, @table_id);

		SET @start = GETDATE();
		EXEC multiple_rows_insert @table_name, @rows_no;
		SET @end = GETDATE();

		INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt)
		VALUES (@run_id, @table_id, @start, @end);

		FETCH TestCursor
		INTO @table_id, @rows_no;
	END

	CLOSE TestCursor;
	DEALLOCATE TestCursor;

	-------------------------------------------

	/*
		Run test for views
	*/

	DECLARE @view_name NVARCHAR(MAX) = '';

	DECLARE TestCursor CURSOR FOR 
	SELECT ViewID FROM TestViews
	WHERE TestID = CONVERT(INT, @test_id)

	OPEN TestCursor
	FETCH TestCursor
	INTO @view_id;
	
	WHILE @@FETCH_STATUS = 0
	BEGIN
		SELECT @view_name = Name FROM Views
		WHERE ViewID = CONVERT(INT, @view_id);

		SET @query = 'SELECT * FROM ' + @view_name;
		
		SET @start = GETDATE();
		EXEC sp_executesql @query;
		SET @end = GETDATE();

		INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, EndAt)
		VALUES (@run_id, @view_id, @start, @end);

		FETCH TestCursor
		INTO @view_id;
	END
	
	CLOSE TestCursor;
	DEALLOCATE TestCursor;

	/*
		Set TestRuns table data
	*/

	UPDATE TestRuns
	SET EndAt = GETDATE()
	WHERE Description = (SELECT Name FROM Tests WHERE TestID = @test_id) AND StartAt = @test_start;
END
GO

--------------------------------------------------------

-- EXEC runSingleTest 5;

--------------------------------------------------------

DROP PROCEDURE IF EXISTS runAllTests;
GO

CREATE PROCEDURE runAllTests
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @test_id INT = -1;

	DECLARE AllTestsCursor CURSOR FOR 
	SELECT TestID FROM Tests
	
	OPEN AllTestsCursor
	FETCH AllTestsCursor
	INTO @test_id;
	
	WHILE @@FETCH_STATUS = 0
	BEGIN
		PRINT '...executing test ' + CONVERT(NVARCHAR(MAX), @test_id);
		EXEC runSingleTest @test_id;

		FETCH AllTestsCursor
		INTO @test_id;
	END
	
	CLOSE AllTestsCursor;
	DEALLOCATE AllTestsCursor;
	SET NOCOUNT OFF;
END
GO

EXEC runAllTests;
PRINT 'All tests done!';
