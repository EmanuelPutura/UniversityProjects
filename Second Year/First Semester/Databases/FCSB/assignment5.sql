USE FCSB;
SET NOCOUNT ON;

DROP TABLE IF EXISTS U18ScoutedPlayers;
DROP TABLE IF EXISTS U18PlayersScouts;
DROP TABLE IF EXISTS U18Players;

-- TA(aid, a2, ...) table: scout_id <-> aid, agency <-> a2
CREATE TABLE U18PlayersScouts (
	scout_id INT NOT NULL PRIMARY KEY,
	club_id INT UNIQUE NOT NULL,  -- For the sake of this example, assume each club has at most one U18 scout
	last_name varchar(50) NOT NULL,
	first_name varchar(50) NOT NULL
);

-- TB(bid, b2, ...) table: player_id <-> bid, age <-> b2
CREATE TABLE U18Players (
	player_id INT NOT NULL PRIMARY KEY,
	age INT,
	last_name varchar(50) NOT NULL,
	first_name varchar(50) NOT NULL
);

-- TC(cid, aid, bid, ...) table: player_id <-> bid, age <-> b2
CREATE TABLE U18ScoutedPlayers (
	id INT NOT NULL PRIMARY KEY,
	scout_id INT NOT NULL REFERENCES U18PlayersScouts(scout_id) ON DELETE CASCADE ON UPDATE CASCADE,
	player_id INT NOT NULL REFERENCES U18Players(player_id) ON DELETE CASCADE ON UPDATE CASCADE,
	starting_year INT
);

-- ***************************************************************************************************
-- *************************************** GENERATORS ************************************************
-- ***************************************************************************************************

DROP PROCEDURE IF EXISTS TA_insert_rows;
GO

CREATE PROCEDURE TA_insert_rows (@rows_no INT)
AS
BEGIN
	DECLARE @scout INT = 1;
	DECLARE @club INT = 1;
	DECLARE @last_name NVARCHAR(MAX) = 'Default Last Name';
	DECLARE @first_name NVARCHAR(MAX) = 'Default First Name'

	WHILE @rows_no > 0
	BEGIN
		INSERT INTO U18PlayersScouts (scout_id, club_id, last_name, first_name)
		VALUES (@scout, @club, @last_name, @first_name);

		SET @scout = @scout + 1;
		SET @club = @club + 1;
		SET @rows_no = @rows_no - 1;
	END
END
GO

DROP PROCEDURE IF EXISTS TB_insert_rows;
GO

CREATE PROCEDURE TB_insert_rows (@rows_no INT)
AS
BEGIN
	DECLARE @player INT = 1;
	DECLARE @age INT = 11;
	DECLARE @last_name NVARCHAR(MAX) = 'Default Last Name';
	DECLARE @first_name NVARCHAR(MAX) = 'Default First Name'

	WHILE @rows_no > 0
	BEGIN
		INSERT INTO U18Players (player_id, age, last_name, first_name)
		VALUES (@player, @age, @last_name, @first_name);

		SET @age = @age + 1;
		IF @age = 20
			SET @age = 12;

		SET @player = @player + 1;
		SET @rows_no = @rows_no - 1;
	END
END
GO

DROP PROCEDURE IF EXISTS TC_insert_rows;
GO

CREATE PROCEDURE TC_insert_rows (@rows_no INT)
AS
BEGIN
	DECLARE @id INT = 1;
	DECLARE @scout INT = 1;
	DECLARE @player INT = 1;
	DECLARE @year INT = 2010;

	WHILE @rows_no > 0
	BEGIN
		INSERT INTO U18ScoutedPlayers (id, scout_id, player_id, starting_year)
		VALUES (@id, @scout, @player, @year);

		SET @year = @year + 1;
		IF @year > 2021
			SET @year = 2010;

		SET @id = @id + 1;
		SET @scout = @scout + 1;
		SET @player = @player + 1;
		SET @year = @year + 1;
		SET @rows_no = @rows_no - 1;
	END
END
GO

DROP PROCEDURE IF EXISTS multiple_rows_insert_v2;
GO

CREATE PROCEDURE multiple_rows_insert_v2 (@rows_no INT)
AS
BEGIN
	EXEC TA_insert_rows @rows_no;
	EXEC TB_insert_rows @rows_no;
	EXEC TC_insert_rows @rows_no;
END
GO

-- ***************************************************************************************************
-- ******************************* Create and Populate Tables ****************************************
-- ***************************************************************************************************

DELETE FROM U18PlayersScouts;
EXEC multiple_rows_insert_v2 100000;
GO

-- ***************************************************************************************************
-- ************************************ Solve Requirements *******************************************
-- ***************************************************************************************************

/*
	a. Write queries on TA such that their execution plans contain the following operators:
		• clustered index scan;
		• clustered index seek;
		• nonclustered index scan;
		• nonclustered index seek;
		• key lookup.
*/

-- Primary Key constraint on scout_id column from U18PlayersScouts => a clustered index is automatically created on scout_id column
-- Unique constraint on club_id column from U18PlayersScouts       => a non-clustered index is automatically created on club_id column

EXEC sp_helpindex U18PlayersScouts;

-- Part 1: clustered index scan
SELECT * FROM U18PlayersScouts
WHERE last_name LIKE 'a%';

-- Part 2: clustered index seek
SELECT * FROM U18PlayersScouts
WHERE scout_id < 900000;

-- Part 3: nonclustered index scan
SELECT scout_id, club_id FROM U18PlayersScouts;

-- Part 4: nonclustered index seek
SELECT scout_id, club_id FROM U18PlayersScouts
WHERE club_id > 85000000;

-- Part 5: key lookup
SELECT club_id, last_name FROM U18PlayersScouts
WHERE club_id = 53202421;

/*
	b. Write a query on table TB with a WHERE clause of the form
	WHERE b2 = value and analyze its execution plan. Create a nonclustered
	index that can speed up the query. Examine the execution plan again.
*/

DROP INDEX IF EXISTS IndexU18PlayersAge ON U18Players;
DROP TABLE IF EXISTS QueryTime
CREATE TABLE QueryTime (
	id INT NOT NULL UNIQUE,
	start_time DATETIME,
	end_time DATETIME
);

-----------------------------------------------------

UPDATE U18Players
SET age = 15
WHERE last_name LIKE 'a%';

UPDATE U18Players
SET age = 20
WHERE last_name LIKE 'b%';

UPDATE U18Players
SET age = 17
WHERE age % 3 = 1 OR last_name LIKE 'c%';

-----------------------------------------------------

DECLARE @next_id INT;
SELECT @next_id = COUNT(*) + 1
FROM QueryTime;

DECLARE @start_date DATETIME = GETDATE();
------------------------------------------------------
SELECT last_name, age
FROM U18Players
WHERE age = 11
ORDER BY last_name;
------------------------------------------------------

DECLARE @end_date DATETIME = GETDATE();
INSERT INTO QueryTime (id, start_time, end_time)
VALUES (@next_id, @start_date, @end_date);

PRINT 'b. Time needed for first query: ' + CONVERT(NVARCHAR(MAX), DATEDIFF(millisecond, @start_date, @end_date)) 
												+ ' millisecons.';

------------------------------------------------------
CREATE NONCLUSTERED INDEX IndexU18PlayersAge
ON U18Players(age ASC) INCLUDE(last_name);

SET @start_date = GETDATE();

SELECT last_name, age
FROM U18Players
WHERE age = 11
ORDER BY last_name;

SET @end_date = GETDATE();
------------------------------------------------------

SELECT @next_id = COUNT(*) + 1
FROM QueryTime;

INSERT INTO QueryTime (id, start_time, end_time)
VALUES (@next_id, @start_date, @end_date);

PRINT 'b. (Improved) Time needed for second query: ' + CONVERT(NVARCHAR(MAX), DATEDIFF(millisecond, @start_date, @end_date)) 
												+ ' millisecons.';

SELECT * FROM QueryTime;
GO

/*
	c. Create a view that joins at least 2 tables. Check whether existing
	indexes are helpful; if not, reassess existing indexes / examine the
	cardinality of the tables.
*/

DROP VIEW IF EXISTS TestOKView;
GO

CREATE VIEW TestOKView AS
SELECT P.last_name, P.age  
FROM U18Players P INNER JOIN U18ScoutedPlayers SP ON P.player_id = SP.player_id
WHERE P.age = 17;
GO

SELECT * FROM TestOKView;  -- index seek

DROP VIEW IF EXISTS TestCView;
GO

-------------------------------------------
CREATE VIEW TestCView AS
SELECT PS.scout_id, PS.last_name, SP.player_id, SP.starting_year
FROM U18PlayersScouts PS INNER JOIN U18ScoutedPlayers SP ON PS.scout_id = SP.scout_id
GO
-------------------------------------------

DECLARE @next_id INT;
SELECT @next_id = COUNT(*) + 1
FROM QueryTime;

DECLARE @start_date DATETIME = GETDATE();
SELECT * FROM TestCView; -- SELECT FROM VIEW
DECLARE @end_date DATETIME = GETDATE();
INSERT INTO QueryTime (id, start_time, end_time)
VALUES (@next_id, @start_date, @end_date);

PRINT 'c. Time needed for first query: ' + CONVERT(NVARCHAR(MAX), DATEDIFF(millisecond, @start_date, @end_date)) 
												+ ' millisecons.';
GO

DECLARE @next_id INT;
SELECT @next_id = COUNT(*) + 1
FROM QueryTime;

/*
	High cardinality (few duplicate elements in column scout_id) => it is worth to have a nonclustered index in order to not have to
	scan all scout_ids from SP table in the INNER JOIN
*/

DROP INDEX IF EXISTS CIndex1 ON U18ScoutedPlayers;
CREATE NONCLUSTERED INDEX CIndex1 ON U18ScoutedPlayers (scout_id) INCLUDE (starting_year, player_id);

DROP INDEX IF EXISTS CIndex2 ON U18PlayersScouts;
CREATE NONCLUSTERED INDEX CIndex2 ON U18PlayersScouts (scout_id) INCLUDE (last_name);

DECLARE @start_date DATETIME = GETDATE();
SELECT * FROM TestCView; -- SELECT FROM VIEW
DECLARE @end_date DATETIME = GETDATE();
INSERT INTO QueryTime (id, start_time, end_time)
VALUES (@next_id, @start_date, @end_date);

PRINT 'c. (Improved) Time needed for first query: ' + CONVERT(NVARCHAR(MAX), DATEDIFF(millisecond, @start_date, @end_date)) 
												+ ' millisecons.';
