USE FCSB;

/* Inserts */
INSERT INTO TeamMatches (playedAgainst, matchDate)
VALUES ('FC Barcelona', '2022-05-07');

INSERT INTO TeamMatches (playedAgainst, matchDate)
VALUES ('CFR Cluj', '2022-01-21');

INSERT INTO TeamMatches (playedAgainst, matchDate)
VALUES ('Real Madrid', '2022-04-11');

INSERT INTO TeamMatches (playedAgainst, matchDate)
VALUES ('Mioveni', '2021-12-12');

INSERT INTO TeamMatches (playedAgainst, matchDate)
VALUES ('Gloria Bistrita', '2021-12-12');

SELECT * FROM TeamMatches;

/*
/* Insert violating referential integrity constraint (matchID is a foreign key, but the given ID is not valid) */
INSERT INTO SeasonGoals (player, matchID)
VALUES (1, 7);

/* Insert violating referential integrity constraint (matchID is a foreign key, but the given ID is not valid) */
INSERT INTO SeasonAssists (player, matchID)
VALUES (2, 10);
*/

/* Updates */
UPDATE SeasonGoals
SET matchID = 1
WHERE matchID is NULL AND (player IN (2, 3) OR goalID = 1);

UPDATE SeasonGoals
SET matchID = 2
WHERE matchID is NULL AND goalID BETWEEN 4 AND 5 AND player <> 2;

UPDATE SeasonGoals
SET matchID = 5
WHERE goalID = 2;

UPDATE SeasonAssists
SET matchID = 2
WHERE assistID % 2 = 0 AND matchID is NULL;

UPDATE SeasonAssists
SET matchID = 3
WHERE assistID % 2 = 1 AND matchID is NULL AND assistID <> 1; 

UPDATE Players
SET marketValueInEuros = marketValueInEuros * 1.2
WHERE lastName LIKE 'Pop%';

/* Deletes */
DELETE FROM TeamMatches WHERE playedAgainst = 'Mioveni';
DELETE FROM SeasonAssists WHERE matchID IS NULL;
DELETE FROM SeasonGoals WHERE matchID IS NULL;

/*
	Unions:
	1. Select all the players that have scored at least a goal or an assist
	2. Select all the players that have a market value greater than the average market value of the team or have a salary greater than average
*/

SELECT playerID, lastName, firstName
FROM Players
WHERE playerID = ANY (SELECT player FROM SeasonGoals)
UNION
SELECT playerID, lastName, firstName
FROM Players
WHERE playerID = ANY (SELECT player FROM SeasonAssists)

SELECT AVG(amountInEuros) as 'Average Team Salary'
FROM PlayersSalaries;

SELECT AVG(marketValueInEuros) as 'Average Team Market Value'
FROM Players;

SELECT P.lastName, P.firstName, P.marketValueInEuros, PS.amountInEuros
FROM Players P, PlayersSalaries PS
WHERE P.playerID = PS.player AND (marketValueInEuros > (SELECT AVG(marketValueInEuros) FROM Players) OR PS.amountInEuros > (SELECT AVG(amountInEuros) FROM PlayersSalaries));

/*
	Intersects:
	1. Select all the players that have scored at least a goal and an assist
	2. Select all the players that have a market value greater than the average market value of the team and that have a salary greater than average
*/

SELECT playerID, lastName, firstName
FROM Players
WHERE playerID = ANY (SELECT player FROM SeasonGoals)
INTERSECT
SELECT playerID, lastName, firstName
FROM Players
WHERE playerID = ANY (SELECT player FROM SeasonAssists)

SELECT P.lastName, P.firstName, P.marketValueInEuros, PS.amountInEuros
FROM Players P, PlayersSalaries PS
WHERE P.playerID = PS.player AND (marketValueInEuros > (SELECT AVG(marketValueInEuros) FROM Players) AND P.playerID IN (
	SELECT P.playerID FROM Players P, PlayersSalaries PS WHERE P.playerID = PS.player AND PS.amountInEuros > (SELECT AVG(amountInEuros) FROM PlayersSalaries))
);

/*
	Excepts:
	1. Select all the players that have scored at least a goal, but not a single assist yet
	2. Select all the players that have a market value greater than the average market value of the team, but that do not have a salary greater than average
*/

SELECT playerID, lastName, firstName
FROM Players
WHERE playerID = ANY (SELECT player FROM SeasonGoals)
EXCEPT
SELECT playerID, lastName, firstName
FROM Players
WHERE playerID = ANY (SELECT player FROM SeasonAssists)

SELECT P.lastName, P.firstName, P.marketValueInEuros, PS.amountInEuros
FROM Players P, PlayersSalaries PS
WHERE P.playerID = PS.player AND (marketValueInEuros > (SELECT AVG(marketValueInEuros) FROM Players) AND P.playerID NOT IN (
	SELECT P.playerID FROM Players P, PlayersSalaries PS WHERE P.playerID = PS.player AND PS.amountInEuros > (SELECT AVG(amountInEuros) FROM PlayersSalaries))
);

/*
	INNER JOIN: For each goal of a player select the match date and the team FCSB played against, together with the player's full name
*/

SELECT P.lastName, P.firstName, TM.playedAgainst, TM.matchDate
FROM Players P
INNER JOIN SeasonGoals SG ON P.playerID = SG.player
INNER JOIN TeamMatches TM ON SG.matchID = TM.matchID;

/*
	INNER JOIN: Select all the players and their number of goals
*/

SELECT P.lastName AS 'Last Name', P.firstName AS 'First Name', COUNT(P.playerID) AS 'Goals Number'
FROM Players P
INNER JOIN SeasonGoals SG ON P.playerID = SG.player
GROUP BY P.lastName, P.firstName;

/*
	INNER JOIN: Select all players that have scored a goal and their position (join two m:n relationships)
*/

SELECT *
FROM SeasonGoals SG
INNER JOIN PlayerHasPosition P ON SG.player = P.player;

/*
	LEFT JOIN: Select all the players' goals and the match when the goal was scored, include players with no goals
*/

SELECT *
FROM Players P
LEFT JOIN SeasonGoals SG ON P.playerID = SG.player
LEFT JOIN TeamMatches TM ON SG.matchID = TM.matchID;

/*
	RIGHT JOIN: Select all the trophies and the team formations used to win that trophy; include formations with no trophies won
*/

SELECT *
FROM Trophies T
RIGHT JOIN TeamFormations TF ON T.mostPlayedFormation = TF.formation;

/*
	FULL JOIN: Find all assists that happened in the same match as a goal; include matches with assists but no goals and goals but no assists
*/

SELECT *
FROM SeasonGoals SG
FULL JOIN SeasonAssists SA ON SG.matchID = SA.matchID;

/* 
	Two queries with the IN operator and a subquery in the WHERE clause; in at least one case, the subquery should include a subquery in its own WHERE clause:
	1. Select the players that are training mostly in the 4-3-3 formation
	2. Select the goals scored by players with a market value above average
*/

SELECT P.lastName, P.firstName
FROM Players P
WHERE P.mainTeamCoach IN (
	SELECT C.coachID
	FROM TeamCoaches C
	WHERE C.prefferedFormation IN (
		SELECT F.formation
		FROM TeamFormations F
		WHERE F.formation = '4-3-3'
	)
);

SELECT SG.goalID, SG.matchID
FROM SeasonGoals SG
WHERE SG.player IN (
	SELECT P.playerID
	FROM Players P
	WHERE P.marketValueInEuros > (SELECT AVG(marketValueInEuros) FROM Players)
);

/*
	Two queries with the EXISTS operator and a subquery in the WHERE clause
	1. Select all the players that have scored at least a goal in 2022
	2. Select all the players that have at least an assist
*/

SELECT P.lastName, P.firstName
FROM Players P
WHERE EXISTS (
	SELECT *
	FROM SeasonGoals SG
	WHERE SG.player = P.playerID AND EXISTS (
		SELECT *
		FROM TeamMatches TM
		WHERE SG.matchID = TM.matchID AND YEAR(TM.matchDate) = 2022
	)
);

SELECT P.lastName, P.firstName
FROM Players P
WHERE EXISTS (
	SELECT *
	FROM SeasonAssists SA
	WHERE SA.player = P.playerID
);

/*
	Two queries with a subquery in the FROM clause
	1. Select all the players that are prepared by Prodan Viorel (fitness coach)
	2. Select all the players and their coach's preferred formation style
*/

SELECT P.lastName, P.firstName
FROM Players P, (
	SELECT TC.coachID
	FROM TeamCoaches TC INNER JOIN FitnessCoaches FC ON TC.assistantFitnessCoach = FC.coachID
	WHERE FC.firstName = 'Viorel' AND FC.lastName = 'Prodan'
	) AS C
WHERE P.mainTeamCoach = C.coachID;

SELECT P.lastName, P.firstName, FS.formationStyle
FROM Players P, (
	SELECT TC.coachID, FC.formationStyle
	FROM TeamCoaches TC INNER JOIN TeamFormations FC ON TC.prefferedFormation = FC.formation
	) AS FS
WHERE P.mainTeamCoach = FS.coachID;

/*
	Four queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 2 of the latter will also have a subquery in the HAVING clause
	Use the aggregation operators: COUNT, SUM, AVG, MIN, MAX.
	1. Get the average market value of the players playing a certain formation style
	2. Select formations styles used for winning more than one trophy
	3. Select the competitional years and the number of matches in each year from 2021 to 2022
	4. Select formations and the total sum of players that use it. Select only the top 50% of the formations styles by usage
*/

SELECT TF.formationStyle AS 'Formation Style', AVG(P.marketValueInEuros) AS 'Average Market Value'
FROM Players P
INNER JOIN TeamCoaches TC ON P.mainTeamCoach = TC.coachID
INNER JOIN TeamFormations TF ON TC.prefferedFormation = TF.formation
GROUP BY TF.formationStyle
HAVING MIN(P.marketValueInEuros) >= 10000
ORDER BY AVG(P.marketValueInEuros) DESC;

SELECT F.formationStyle, COUNT(T.trophyID)
FROM TeamFormations F
INNER JOIN Trophies T ON F.formation = T.mostPlayedFormation
GROUP BY F.formationStyle
HAVING (SELECT COUNT(T.trophyID) FROM Trophies T) >= 2;

SELECT TOP 10 YEAR(M.matchDate) AS 'Competitional Year', COUNT(M.matchID) AS 'Matched Number'
FROM TeamMatches M
GROUP BY YEAR(M.matchDate)
HAVING MIN(YEAR(M.matchDate)) >= 2021 AND (SELECT MAX(YEAR(M.matchDate)) FROM TeamMatches M) <= 2022
ORDER BY (COUNT(M.matchID));

SELECT TOP 50 PERCENT F.formation, SUM(P.marketValueInEuros) AS 'Total market value'
FROM Players P
INNER JOIN TeamCoaches C ON P.mainTeamCoach = C.coachID
INNER JOIN TeamFormations F ON C.prefferedFormation = F.formation
GROUP BY F.formation
ORDER BY SUM(P.marketValueInEuros) DESC

/*
	Select distinct players with their preffered formations
*/
SELECT DISTINCT P.lastName, P.firstName, C.prefferedFormation
FROM Players P, TeamCoaches C;

/*
	Count the number of distinct goal scorers
*/
SELECT COUNT(DISTINCT SG.player) AS 'Distinct Goal Scoreres No'
FROM SeasonGoals SG;

/*
	Count the number of distinct players that have at least an assist
*/
SELECT COUNT(DISTINCT SA.player) AS 'Players With At Least An Assist No'
FROM SeasonAssists SA;

/*
	Count the number of goals + the number of assists
*/
SELECT Count(A.assistID) + Count(G.goalID)
FROM SeasonAssists A INNER JOIN SeasonGoals G ON A.player = G.player;

/*
	Count the number of goals * the number of assists
*/
SELECT Count(A.assistID) * Count(G.goalID)
FROM SeasonAssists A INNER JOIN SeasonGoals G ON A.player = G.player;

/*
	How many goals still needed for the team to have 25 goals scored?
*/
SELECT 25 - COUNT(G.goalID) as 'Goals still needed to reach 25 scored goals'
FROM SeasonGoals G;

/*
	Four queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator).
	Rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.
	
	1. Select formations played by at least a coach
	2. Select players that gave at least an assist
	3. Select the formations such that all the trophies with that formation were won on day 10
	4. Select the player with the highest market value
*/

SELECT F.formation
FROM TeamFormations F
WHERE F.formation = ANY(SELECT F.formation FROM TeamFormations F INNER JOIN TeamCoaches C ON F.formation = C.prefferedFormation);

SELECT F.formation
FROM TeamFormations F
WHERE F.formation IN (SELECT F.formation FROM TeamFormations F INNER JOIN TeamCoaches C ON F.formation = C.prefferedFormation);

SELECT P.lastName, P.firstName
FROM Players P
WHERE P.playerID = ANY(SELECT A.player FROM SeasonAssists A WHERE P.playerID = A.player);

SELECT P.lastName, P.firstName
FROM Players P
WHERE P.playerID IN (SELECT A.player FROM SeasonAssists A WHERE P.playerID = A.player);

SELECT F.formation
FROM TeamFormations F
WHERE F.formation = ALL(SELECT T.mostPlayedFormation FROM Trophies T WHERE DAY(T.winningDate) = 10);

SELECT F.formation
FROM TeamFormations F
WHERE (SELECT COUNT(T.mostPlayedFormation) FROM Trophies T WHERE DAY(T.winningDate) = 10 AND T.mostPlayedFormation <> F.formation) = 0 AND 
	F.formation IN (SELECT T.mostPlayedFormation FROM Trophies T WHERE DAY(T.winningDate) = 10);

SELECT P.lastName, P.firstName, P.marketValueInEuros
FROM Players P
WHERE P.marketValueInEuros >= ALL(SELECT PLY.marketValueInEuros FROM Players PLY WHERE PLY.playerID <> P.playerID);

SELECT P.lastName, P.firstName, P.marketValueInEuros
FROM Players P
WHERE (SELECT COUNT(PLY.marketValueInEuros) FROM Players PLY WHERE PLY.playerID <> P.playerID AND PLY.marketValueInEuros > P.marketValueInEuros) = 0;