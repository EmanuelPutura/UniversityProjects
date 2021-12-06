USE FCSB;

DROP PROCEDURE IF EXISTS insertIntoTables;
GO

CREATE PROCEDURE insertIntoTables AS
	INSERT INTO Tables (Name)
	VALUES ('FieldPositions');

	INSERT INTO Tables (Name)
	VALUES ('Trophies');

	INSERT INTO Tables (Name)
	VALUES ('PlayerHasPosition');
GO

-- EXEC insertIntoTables;

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

-- EXEC insertIntoViews;