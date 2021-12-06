USE FCSB;

DROP PROCEDURE IF EXISTS associateTestWithTable;
GO

CREATE PROCEDURE associateTestWithTable (@test_id INT, @table_id INT, @rows_no INT, @position INT)
AS
BEGIN
	DECLARE @values NVARCHAR(MAX) = '(' + CONVERT(NVARCHAR(MAX), @test_id) + ', ' + CONVERT(NVARCHAR(MAX), @table_id) + ', ' + 
				CONVERT(NVARCHAR(MAX), @rows_no) + ', ' + CONVERT(NVARCHAR(MAX), @position) + ');';
	DECLARE @query NVARCHAR(MAX) = N'INSERT INTO TestTables (TestID, TableID, NoOfRows, Position) VALUES ' + @values;
	EXEC sp_executesql @query;
END
GO

--------------------------------------------------------

DROP PROCEDURE IF EXISTS associateTestWithView;
GO

CREATE PROCEDURE associateTestWithView (@test_id INT, @view_id INT)
AS
BEGIN
	DECLARE @values NVARCHAR(MAX) = '(' + CONVERT(NVARCHAR(MAX), @test_id) + ', ' + CONVERT(NVARCHAR(MAX), @view_id) + ');';
	DECLARE @query NVARCHAR(MAX) = N'INSERT INTO TestViews (TestID, ViewID) VALUES ' + @values;
	EXEC sp_executesql @query;
END
GO

--------------------------------------------------------

DROP PROCEDURE IF EXISTS insertIntoTables;
GO

DELETE FROM Tables;
DELETE FROM Views;
DELETE FROM Tests;
DELETE FROM TestViews;
DELETE FROM TestTables;
GO

CREATE PROCEDURE insertIntoTables AS
	INSERT INTO Tables (Name)
	VALUES ('FieldPositions');

	INSERT INTO Tables (Name)
	VALUES ('TeamCoaches');

	INSERT INTO Tables (Name)
	VALUES ('PlayerHasPosition');
GO

EXEC insertIntoTables;
GO

DROP PROCEDURE IF EXISTS insertIntoViews;
GO

CREATE PROCEDURE insertIntoViews AS
	INSERT INTO Views (Name)
	VALUES ('BestFormation');

	INSERT INTO Views (Name)
	VALUES ('TeamGoalScorers');
	
	INSERT INTO Views (Name)
	VALUES ('BestFormationStyles');
GO

EXEC insertIntoViews;
GO

DROP PROCEDURE IF EXISTS insertDefaultTests;
GO

CREATE PROCEDURE insertDefaultTests AS
	EXEC addTest 'Testing table (FieldPositions) and view (BestFormation)';
	EXEC addTest 'Testing table (FieldPositions) and view (BestFormationStyles)';
	EXEC addTest 'Testing table (FieldPositions, PlayerHasPosition) and views (BestFormation, TeamGoalScorers)';
	EXEC addTest 'Testing table (FieldPositions, TeamCoaches, PlayerHasPosition) and view (BestFormation)';
	EXEC addTest 'Testing table (TeamCoaches) and view (BestFormationStyles)';
GO

EXEC insertDefaultTests;
GO

DROP PROCEDURE IF EXISTS insertDefaultTestTables;
GO

-- associateTestWithTable (@test_id INT, @table_id INT, @rows_no INT, @position INT)
CREATE PROCEDURE insertDefaultTestTables AS
	EXEC associateTestWithTable  1, 1, 100, 1;
	EXEC associateTestWithTable  2, 1, 100, 1;
	EXEC associateTestWithTable  3, 1, 100, 5;
	EXEC associateTestWithTable  3, 3, 100, 2;
	EXEC associateTestWithTable  4, 1, 100, 6;
	EXEC associateTestWithTable  4, 2, 100, 4;
	EXEC associateTestWithTable  4, 3, 100, 7;
	EXEC associateTestWithTable  5, 2, 100, 7;
GO

EXEC insertDefaultTestTables;
GO

DROP PROCEDURE IF EXISTS insertDefaultTestViews;
GO

-- associateTestWithView (@test_id INT, @view_id INT)
CREATE PROCEDURE insertDefaultTestViews AS
	EXEC associateTestWithView  1, 1;
	EXEC associateTestWithView  2, 3;
	EXEC associateTestWithView  3, 1;
	EXEC associateTestWithView  3, 2;
	EXEC associateTestWithView  4, 1;
	EXEC associateTestWithView  5, 3;
GO

EXEC insertDefaultTestViews;
GO
