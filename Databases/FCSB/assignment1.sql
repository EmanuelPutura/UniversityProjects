/*
USE [master];

DROP DATABASE IF EXISTS FCSB;
CREATE DATABASE FCSB;
*/

USE FCSB;

DROP TABLE IF EXISTS SeasonAssists;
DROP TABLE IF EXISTS PlayerHasPosition;
DROP TABLE IF EXISTS FitnessCoachesSalaries;
DROP TABLE IF EXISTS TeamCoachesSalaries;
DROP TABLE IF EXISTS PlayersSalaries;
DROP TABLE IF EXISTS SeasonGoals;
DROP TABLE IF EXISTS Players;
DROP TABLE IF EXISTS TeamCoaches;
DROP TABLE IF EXISTS FitnessCoaches;
DROP TABLE IF EXISTS Trophies;
DROP TABLE IF EXISTS TeamFormations;
DROP TABLE IF EXISTS FieldPositions;
DROP TABLE IF EXISTS TeamMatches;

CREATE TABLE FieldPositions (
	position varchar(255) NOT NULL,
	positionStyle varchar(255),
	PRIMARY KEY (position)
);

CREATE TABLE TeamFormations (
	formation varchar(255) UNIQUE NOT NULL,
	formationStyle varchar(255),
	PRIMARY KEY (formation)
);

CREATE TABLE Trophies (
	trophyID INT NOT NULL IDENTITY,
	trophyType varchar(255) NOT NULL,
	winningDate DATE,
	mostPlayedFormation varchar(255) NOT NULL REFERENCES TeamFormations(formation) ON DELETE CASCADE ON UPDATE CASCADE,
	PRIMARY KEY (trophyID)
);

CREATE TABLE FitnessCoaches (
	coachID INT NOT NULL IDENTITY,
	lastName varchar(255) NOT NULL,
	firstName varchar(255) NOT NULL,
	PRIMARY KEY (coachID)
);

CREATE TABLE TeamCoaches (
	coachID INT NOT NULL IDENTITY,
	lastName varchar(255) NOT NULL,
	firstName varchar(255) NOT NULL,
	coachRole varchar(255),
	prefferedFormation varchar(255) NOT NULL REFERENCES TeamFormations(formation) ON DELETE CASCADE ON UPDATE CASCADE,
	assistantFitnessCoach INT NOT NULL REFERENCES FitnessCoaches(coachID) ON DELETE CASCADE ON UPDATE CASCADE,
	PRIMARY KEY (coachID)
);

CREATE TABLE Players (
	playerID int NOT NULL IDENTITY,
	lastName varchar(255) NOT NULL,
	firstName varchar(255) NOT NULL,
	mainTeamCoach INT NOT NULL REFERENCES TeamCoaches(coachID) ON DELETE CASCADE ON UPDATE CASCADE,
	marketValueInEuros INT CHECK (marketValueInEuros >= 0),
	PRIMARY KEY (playerID),
	UNIQUE (lastName, firstName)
);

CREATE TABLE SeasonGoals (
	goalID INT NOT NULL IDENTITY,
	player INT NOT NULL REFERENCES Players (playerID) ON DELETE CASCADE ON UPDATE CASCADE,
	playedAgainst varchar(255),
	matchDate DATE,
	PRIMARY KEY (goalID)
);

CREATE TABLE SeasonAssists (
	assistID INT NOT NULL IDENTITY,
	player INT NOT NULL REFERENCES Players (playerID) ON DELETE CASCADE ON UPDATE CASCADE,
	playedAgainst varchar(255),
	matchDate DATE,
	PRIMARY KEY (assistID)
);

CREATE TABLE PlayersSalaries (
	player INT NOT NULL REFERENCES Players (playerID) ON DELETE CASCADE ON UPDATE CASCADE,
	amountInEuros DECIMAL (16, 2) CHECK (amountInEuros >= 0),
	/* PRIMARY KEY (player) */
);

CREATE TABLE TeamCoachesSalaries (
	coach INT NOT NULL REFERENCES TeamCoaches (coachID) ON DELETE CASCADE ON UPDATE CASCADE,
	amountInEuros DECIMAL (16, 2) CHECK (amountInEuros >= 0),
	PRIMARY KEY (coach)
);

CREATE TABLE FitnessCoachesSalaries (
	coach INT NOT NULL REFERENCES FitnessCoaches (coachID) ON DELETE CASCADE ON UPDATE CASCADE,
	amountInEuros DECIMAL (16, 2),
	PRIMARY KEY (coach)
);

CREATE TABLE PlayerHasPosition (
	player INT NOT NULL REFERENCES Players (playerID) ON DELETE CASCADE ON UPDATE CASCADE,
	position varchar(255) NOT NULL 
	REFERENCES FieldPositions(position) ON DELETE CASCADE ON UPDATE CASCADE,
	PRIMARY KEY (player, position)
);


/* FieldPositions */
INSERT INTO FieldPositions (position, positionStyle) 
VALUES ('GK', 'Goalkeeper');

INSERT INTO FieldPositions (position, positionStyle) 
VALUES ('CB', 'Defender');

INSERT INTO FieldPositions (position, positionStyle) 
VALUES ('RB', 'Defender');

INSERT INTO FieldPositions (position, positionStyle) 
VALUES ('LB', 'Defender');

INSERT INTO FieldPositions (position, positionStyle) 
VALUES ('CDM', 'Midfielder');

INSERT INTO FieldPositions (position, positionStyle) 
VALUES ('CM', 'Midfielder');

INSERT INTO FieldPositions (position, positionStyle) 
VALUES ('ST', 'Attacker');

INSERT INTO FieldPositions (position, positionStyle) 
VALUES ('RW', 'Winger');

INSERT INTO FieldPositions (position, positionStyle) 
VALUES ('LW', 'Winger');


/* FitnessCoaches */
INSERT INTO FitnessCoaches (lastName, firstName) 
VALUES ('Moldovan', 'Andrei');

INSERT INTO FitnessCoaches (lastName, firstName) 
VALUES ('Prodan', 'Viorel');

INSERT INTO FitnessCoaches (lastName, firstName) 
VALUES ('Baciu', 'Mihai');

INSERT INTO FitnessCoaches (lastName, firstName) 
VALUES ('Muresan', 'Alex');


/* TeamFormations */
INSERT INTO TeamFormations (formation, formationStyle) 
VALUES ('4-3-3', 'Attacking');

INSERT INTO TeamFormations (formation, formationStyle) 
VALUES ('4-2-3-1', 'Neutral');

INSERT INTO TeamFormations (formation, formationStyle) 
VALUES ('5-3-2', 'Defensive');

INSERT INTO TeamFormations (formation, formationStyle) 
VALUES ('4-4-2', 'Neutral');

INSERT INTO TeamFormations (formation, formationStyle) 
VALUES ('4-2-2-2', 'Attacking');


/* TeamCoaches */
INSERT INTO TeamCoaches (lastName, firstName, coachRole, prefferedFormation, assistantFitnessCoach) 
VALUES ('Iordanescu', 'Eduard', 'Principal', '4-3-3', 1);

INSERT INTO TeamCoaches (lastName, firstName, coachRole, prefferedFormation, assistantFitnessCoach) 
VALUES ('Pintili', 'Mihai', 'Secondary ', '4-2-3-1', 2);

INSERT INTO TeamCoaches (lastName, firstName, coachRole, prefferedFormation, assistantFitnessCoach) 
VALUES ('Vintila', 'Bogdan', 'Second team principal', '4-3-3', 2);

INSERT INTO TeamCoaches (lastName, firstName, coachRole, prefferedFormation, assistantFitnessCoach) 
VALUES ('Becali', 'Gigi', 'Tactics coach', '4-2-3-1', 3);


/* Players */
INSERT INTO Players (lastName, firstName, mainTeamCoach, marketValueInEuros)
VALUES ('Coman', 'Florinel', 1, POWER(10, 7));

INSERT INTO Players (lastName, firstName, mainTeamCoach, marketValueInEuros)
VALUES ('Popescu', 'Octavian', 1, POWER(10, 6) * 7);

INSERT INTO Players (lastName, firstName, mainTeamCoach, marketValueInEuros)
VALUES ('Olaru', 'Darius', 2, POWER(10, 6) * 5);

INSERT INTO Players (lastName, firstName, mainTeamCoach, marketValueInEuros)
VALUES ('Vlad', 'Andrei', 3, POWER(10, 6) * 3);

INSERT INTO Players (lastName, firstName, mainTeamCoach, marketValueInEuros)
VALUES ('Cristea', 'Iulian', 4, POWER(10, 6) * 3);

INSERT INTO Players (lastName, firstName, mainTeamCoach, marketValueInEuros)
VALUES ('Popescu', 'Ovidiu', 4, POWER(10, 6) * 2);

INSERT INTO Players (lastName, firstName, mainTeamCoach, marketValueInEuros)
VALUES ('Keseru', 'Claudiu', 3, POWER(10, 6) * 6);

INSERT INTO Players (lastName, firstName, mainTeamCoach, marketValueInEuros)
VALUES ('Budescu', 'Constantin', 1
, POWER(10, 6) * 6);


/* PlayersSalaries */
INSERT INTO PlayersSalaries (player, amountInEuros) 
VALUES (1, 10000);

INSERT INTO PlayersSalaries (player, amountInEuros) 
VALUES (2, 15000);

INSERT INTO PlayersSalaries (player, amountInEuros) 
VALUES (3, 12000);

INSERT INTO PlayersSalaries (player, amountInEuros) 
VALUES (4, 20000);

INSERT INTO PlayersSalaries (player, amountInEuros) 
VALUES (5, 8000);

INSERT INTO PlayersSalaries (player, amountInEuros) 
VALUES (6, 10000);

INSERT INTO PlayersSalaries (player, amountInEuros) 
VALUES (7, 30000);

INSERT INTO PlayersSalaries (player, amountInEuros) 
VALUES (8, 10000);


/* PlayerHasPosition */
INSERT INTO PlayerHasPosition (player, position)
VALUES (1, 'LW');

INSERT INTO PlayerHasPosition (player, position)
VALUES (2, 'LW');

INSERT INTO PlayerHasPosition (player, position)
VALUES (3, 'CM');

INSERT INTO PlayerHasPosition (player, position)
VALUES (4, 'GK');

INSERT INTO PlayerHasPosition (player, position)
VALUES (5, 'CB');

INSERT INTO PlayerHasPosition (player, position)
VALUES (6, 'CDM');

INSERT INTO PlayerHasPosition (player, position)
VALUES (7, 'ST');

INSERT INTO PlayerHasPosition (player, position)
VALUES (7, 'LW');

INSERT INTO PlayerHasPosition (player, position)
VALUES (8, 'CM');

INSERT INTO PlayerHasPosition (player, position)
VALUES (6, 'RB');

INSERT INTO PlayerHasPosition (player, position)
VALUES (8, 'ST');

INSERT INTO PlayerHasPosition (player, position)
VALUES (1, 'ST');


/* SeasonAssists */
INSERT INTO SeasonAssists (player)
VALUES (1);

INSERT INTO SeasonAssists (player)
VALUES (2);

INSERT INTO SeasonAssists (player)
VALUES (6);

INSERT INTO SeasonAssists (player)
VALUES (8);

INSERT INTO SeasonAssists (player)
VALUES (1);


/* FitnessCoachesSalaries */
INSERT INTO FitnessCoachesSalaries (coach, amountInEuros) 
VALUES (1, 10000);

INSERT INTO FitnessCoachesSalaries (coach, amountInEuros) 
VALUES (2, 7000);

INSERT INTO FitnessCoachesSalaries (coach, amountInEuros) 
VALUES (3, 5000);

INSERT INTO FitnessCoachesSalaries (coach, amountInEuros) 
VALUES (4, 1000);


/* SeasonGoals */
INSERT INTO SeasonGoals (player)
VALUES (1);

INSERT INTO SeasonGoals (player)
VALUES (2);

INSERT INTO SeasonGoals (player)
VALUES (3);

INSERT INTO SeasonGoals (player)
VALUES (8);

INSERT INTO SeasonGoals (player)
VALUES (1);


/* Trophies */
INSERT INTO Trophies (trophyType, winningDate, mostPlayedFormation) 
VALUES ('European Cup', '1986-05-7', '4-3-3');

INSERT INTO Trophies (trophyType, winningDate, mostPlayedFormation) 
VALUES ('European Super Cup', '1987-02-24', '4-3-3');

INSERT INTO Trophies (trophyType, winningDate, mostPlayedFormation) 
VALUES ('League', '2015-05-10', '4-2-3-1');

INSERT INTO Trophies (trophyType, winningDate, mostPlayedFormation) 
VALUES ('Domestic Cup', '2020-03-29', '4-3-3');

INSERT INTO Trophies (trophyType, winningDate, mostPlayedFormation) 
VALUES ('Domestic Super Cup', '2013-07-10', '4-2-3-1');


/* TeamCoachesSalaries */
INSERT INTO TeamCoachesSalaries (coach, amountInEuros) 
VALUES (1, 10000);

INSERT INTO TeamCoachesSalaries (coach, amountInEuros) 
VALUES (2, 15000);

INSERT INTO TeamCoachesSalaries (coach, amountInEuros) 
VALUES (3, 12000);

INSERT INTO TeamCoachesSalaries (coach, amountInEuros) 
VALUES (4, 20000);

/* assignment 1 structure modifications */
CREATE TABLE TeamMatches (
	matchID int NOT NULL IDENTITY,
	playedAgainst varchar(255) NOT NULL,
	matchDate DATE NOT NULL,
	PRIMARY KEY (matchID),
	UNIQUE (playedAgainst, matchDate)
);

ALTER TABLE SeasonGoals
DROP COLUMN playedAgainst;

ALTER TABLE SeasonGoals
DROP COLUMN matchDate;

ALTER TABLE SeasonGoals
ADD matchID int;

ALTER TABLE SeasonGoals
ADD CONSTRAINT FK_match
FOREIGN KEY (matchID) REFERENCES TeamMatches (matchID) ON DELETE SET NULL ON UPDATE CASCADE;

ALTER TABLE SeasonAssists
DROP COLUMN playedAgainst;

ALTER TABLE SeasonAssists
DROP COLUMN matchDate;

ALTER TABLE SeasonAssists
ADD matchID int REFERENCES TeamMatches (matchID) ON DELETE SET NULL ON UPDATE CASCADE;

