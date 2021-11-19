/*
	a. modify the type of a column
*/

ALTER TABLE TeamCoachesSalaries
ADD CONSTRAINT df_amountInEuros
DEFAULT 0 FOR amountInEuros;
GO

/*
ALTER TABLE PlayersSalaries
DROP CONSTRAINT PK__PlayersS__A77BE328052EB5B1;
*/

DROP TABLE IF EXISTS TransferList;

ALTER TABLE SeasonGoals
DROP CONSTRAINT FK_match;

DROP PROCEDURE IF EXISTS modifyColumnType;
GO
DROP PROCEDURE IF EXISTS revertModifyColumnType;
GO
DROP PROCEDURE IF EXISTS addColumn;
GO
DROP PROCEDURE IF EXISTS reverseAddColumn;
GO
DROP PROCEDURE IF EXISTS addDefaultConstraint;
GO
DROP PROCEDURE IF EXISTS reverseAddDefaultConstraint;
GO
DROP PROCEDURE IF EXISTS addPrimaryKey;
GO
DROP PROCEDURE IF EXISTS removePrimaryKey;
GO
DROP PROCEDURE IF EXISTS addCandidateKey;
GO
DROP PROCEDURE IF EXISTS removeCandidateKey;
GO
DROP PROCEDURE IF EXISTS addForeignKey;
GO
DROP PROCEDURE IF EXISTS removeForeignKey;
GO
DROP PROCEDURE IF EXISTS createTable;
GO
DROP PROCEDURE IF EXISTS removeTable;
GO

/*
DROP TABLE IF EXISTS VersionChanges;
GO
*/

DROP TABLE IF EXISTS CurrentVersion;
GO
DROP TABLE IF EXISTS AllVersions;
GO

DROP PROCEDURE IF EXISTS goToVersion;
GO
DROP PROCEDURE IF EXISTS executeVersionAction;
GO
DROP PROCEDURE IF EXISTS revertVersionAction;
GO

/*
	a. modify the type of a column
*/

CREATE PROCEDURE modifyColumnType
AS
	ALTER TABLE FitnessCoachesSalaries
	ALTER COLUMN amountInEuros FLOAT(10)
GO

CREATE PROCEDURE revertModifyColumnType
AS
	ALTER TABLE FitnessCoachesSalaries
	ALTER COLUMN amountInEuros DECIMAL(16, 2)
GO

/*
	b. add / remove a column
*/

CREATE PROCEDURE addColumn
AS
	ALTER TABLE Trophies
	ADD winningStadium VARCHAR(50);
GO

CREATE PROCEDURE reverseAddColumn
AS
	ALTER TABLE Trophies
	DROP COLUMN IF EXISTS winningStadium;
GO

/*
	c. add / remove a DEFAULT constraint
*/

CREATE PROCEDURE addDefaultConstraint
AS
	ALTER TABLE TeamFormations
	ADD CONSTRAINT df_formationStyle
	DEFAULT 'Neutral' FOR formationStyle;
GO

CREATE PROCEDURE reverseAddDefaultConstraint
AS
	ALTER TABLE TeamFormations
	DROP CONSTRAINT IF EXISTS df_formationStyle;
GO

/*
	d. add / remove a primary key
*/

CREATE PROCEDURE addPrimaryKey
AS
	ALTER TABLE PlayersSalaries
	ADD CONSTRAINT PK_player PRIMARY KEY (player);
GO

CREATE PROCEDURE removePrimaryKey
AS
	ALTER TABLE PlayersSalaries
	DROP CONSTRAINT IF EXISTS PK_player;
GO

/*
	e. add / remove a candidate key
*/

CREATE PROCEDURE addCandidateKey
AS
	ALTER TABLE Trophies
	ADD CONSTRAINT UQ_winningDate UNIQUE (winningDate);
GO

CREATE PROCEDURE removeCandidateKey
AS
	ALTER TABLE Trophies
	DROP CONSTRAINT IF EXISTS UQ_winningDate;
GO

/*
	f. add / remove a foreign key
*/

CREATE PROCEDURE addForeignKey
AS
	ALTER TABLE SeasonGoals
	ADD CONSTRAINT FK_match
	FOREIGN KEY (matchID) REFERENCES TeamMatches (matchID) ON DELETE SET NULL ON UPDATE CASCADE;
GO

CREATE PROCEDURE removeForeignKey
AS
	ALTER TABLE SeasonGoals
	DROP CONSTRAINT IF EXISTS FK_match;
GO

/*
	g. create / drop a table
*/

CREATE PROCEDURE createTable
AS
	CREATE TABLE TransferList (
		lastName VARCHAR(50),
		firstName VARCHAR(50),
		currentTeam VARCHAR(50)
	);
GO

CREATE PROCEDURE removeTable
AS
	DROP TABLE IF EXISTS TransferList;
GO

/*
	-------------------------------------------------------
	Versioning Mechanism
	-------------------------------------------------------
*/

CREATE TABLE AllVersions (
	ID INT NOT NULL,
	ActionProcedure VARCHAR(50) NOT NULL,
	ReverseProcedure VARCHAR(50) NOT NULL
	PRIMARY KEY(ID),
	UNIQUE(ActionProcedure, ReverseProcedure)
);

INSERT INTO AllVersions (ID, ActionProcedure, ReverseProcedure)
VALUES (1, 'modifyColumnType', 'revertModifyColumnType');

INSERT INTO AllVersions (ID, ActionProcedure, ReverseProcedure)
VALUES (2, 'addColumn', 'reverseAddColumn');

INSERT INTO AllVersions (ID, ActionProcedure, ReverseProcedure)
VALUES (3, 'addDefaultConstraint', 'reverseAddDefaultConstraint');

INSERT INTO AllVersions (ID, ActionProcedure, ReverseProcedure)
VALUES (4, 'addPrimaryKey', 'removePrimaryKey');

INSERT INTO AllVersions (ID, ActionProcedure, ReverseProcedure)
VALUES (5, 'addCandidateKey', 'removeCandidateKey');

INSERT INTO AllVersions (ID, ActionProcedure, ReverseProcedure)
VALUES (6, 'addForeignKey', 'removeForeignKey');

INSERT INTO AllVersions (ID, ActionProcedure, ReverseProcedure)
VALUES (7, 'createTable', 'removeTable');

/*
CREATE TABLE CurrentVersion (
	ID INT NOT NULL,
	PRIMARY KEY (ID)
);
*/

CREATE TABLE CurrentVersion (
	ActionProcedure VARCHAR(50) NOT NULL,
	ReverseProcedure VARCHAR(50) NOT NULL,
	ID INT NOT NULL,
	PRIMARY KEY(ID),
	UNIQUE(ActionProcedure, ReverseProcedure)
);

/*
INSERT INTO CurrentVersion(ID)
VALUES (1);
*/

INSERT INTO CurrentVersion(ActionProcedure, ReverseProcedure, ID)
VALUES ('modifyColumnType', 'revertModifyColumnType', 1);
GO

CREATE PROCEDURE executeVersionAction
AS
BEGIN
	DECLARE @sqlstmt NVARCHAR(MAX);
	SET @sqlstmt = (SELECT ActionProcedure FROM CurrentVersion);
	EXEC sp_executesql @sqlstmt;
END
GO

CREATE PROCEDURE revertVersionAction
AS
BEGIN
	DECLARE @sqlstmt NVARCHAR(MAX);
	SET @sqlstmt = (SELECT ReverseProcedure FROM CurrentVersion);
	EXEC sp_executesql @sqlstmt;
END
GO

CREATE PROCEDURE goToVersion(@newVersion VARCHAR(5))
AS
BEGIN
	DECLARE @currentVersion INT;
	SET @currentVersion = (SELECT ID FROM CurrentVersion);

	BEGIN TRY
		SET @newVersion = CAST(@newVersion AS INT);
	END TRY
	BEGIN CATCH
		RAISERROR('Invalid version', 10, 1);
		RETURN 
	END CATCH

	IF @newVersion < 0 OR @newVersion > 7
	BEGIN
		RAISERROR('Invalid version', 10, 1);
		RETURN 
	END

	EXEC revertVersionAction;

	/* TRUNCATE TABLE VersionChanges; */
	TRUNCATE TABLE CurrentVersion;

	DECLARE @actionProcedure VARCHAR(50);
	SET @actionProcedure = (SELECT ActionProcedure FROM AllVersions AV WHERE AV.ID = @newVersion);
	DECLARE @reverseProcedure VARCHAR(50);
	SET @reverseProcedure = (SELECT ReverseProcedure FROM AllVersions AV WHERE AV.ID = @newVersion);
	
	DECLARE @sqlstmt NVARCHAR(MAX);
	SET @sqlstmt = @actionProcedure;
	EXEC sp_executesql @sqlstmt;

	/*
	INSERT INTO CurrentVersion(ID)
	VALUES (@newVersion);
	*/

	INSERT INTO CurrentVersion(ActionProcedure, ReverseProcedure, ID)
	VALUES (@actionProcedure, @reverseProcedure, @newVersion);
END
GO

EXEC goToVersion '1'
GO

EXEC goToVersion '7'
GO

/*
EXEC goToVersion '1.3'
GO

EXEC goToVersion 'test'
GO
*/

/*
EXEC goToVersion 10
GO
*/
