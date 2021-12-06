/*
	A view with a SELECT statement operating on one table
		- select all trophies won by having 4-3-3 as the most played formation
*/

CREATE OR ALTER VIEW BestFormation
AS
	SELECT * FROM Trophies
	WHERE mostPlayedFormation = '4-3-3';
GO

SELECT * FROM BestFormation;
GO

/*
	A view with a SELECT statement operating on at least 2 tables:
		- select all players that have scored a goal and their position
*/

CREATE OR ALTER VIEW TeamGoalScorers
AS
	SELECT P.player as [Player ID], P.position as [Field Position]
	FROM SeasonGoals SG
	INNER JOIN PlayerHasPosition P ON SG.player = P.player;
GO

SELECT * FROM TeamGoalScorers;
GO

/*
	A view with a SELECT statement that has a GROUP BY clause and operates on at least 2 tables
		- select formations styles used for winning more than one trophy
*/

CREATE OR ALTER VIEW BestFormationStyles
AS
	SELECT F.formationStyle, COUNT(T.trophyID) AS [Trophies]
	FROM TeamFormations F
	INNER JOIN Trophies T ON F.formation = T.mostPlayedFormation
	GROUP BY F.formationStyle
	HAVING (SELECT COUNT(T.trophyID) FROM Trophies T) >= 2;
GO

SELECT * FROM BestFormationStyles;
