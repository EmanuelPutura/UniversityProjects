USE Football;
GO

DROP TABLE IF EXISTS TeamOwnedBy;
DROP TABLE IF EXISTS TeamOwner;
DROP TABLE IF EXISTS Team;
DROP TABLE IF EXISTS LogTable;

CREATE TABLE TeamOwner (
	id INT NOT NULL PRIMARY KEY IDENTITY,
	fullName varchar(50) NOT NULL,
	age INT NOT NULL
);

CREATE TABLE Team (
	id INT NOT NULL PRIMARY KEY IDENTITY,
	teamName varchar(50) NOT NULL,
	teamLeague varchar(50) NOT NULL
);

CREATE TABLE TeamOwnedBy (
	ownerId INT NOT NULL REFERENCES TeamOwner(id) ON DELETE CASCADE ON UPDATE CASCADE,
	teamId INT NOT NULL REFERENCES Team(id) ON DELETE CASCADE ON UPDATE CASCADE,
	PRIMARY KEY(ownerId, teamId)
);

CREATE TABLE LogTable (
	Lid INT IDENTITY PRIMARY KEY,
	TypeOperation VARCHAR(50),  -- can be Update, Select, ...
	TableOperation VARCHAR(50),
	ExecutionDate DATETIME
);
