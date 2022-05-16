USE Football;

DROP FUNCTION IF EXISTS validateTeamLeague;
GO

DROP FUNCTION IF EXISTS validateGenericString;
GO

DROP FUNCTION IF EXISTS validateIntegerGreaterThanInfLimit;
GO

DROP FUNCTION IF EXISTS validateTeamOwnerRecord;
GO

DROP FUNCTION IF EXISTS validateTeamRecord;
GO

DROP FUNCTION IF EXISTS validateTeamOwnedByRecord;
GO

CREATE FUNCTION validateGenericString(@string varchar(50)) RETURNS INT AS
BEGIN
	IF (LEN(@string) < 1)
		RETURN 0;
	RETURN 1;
END
GO

CREATE FUNCTION validateTeamLeague (@league varchar(50)) RETURNS INT AS
BEGIN
	IF(@league IN ('Liga 1', 'Liga 2', 'Liga 3', 'Liga 4') AND dbo.validateGenericString(@league) = 1)
		RETURN 1;
	
	RETURN 0;
END
GO

CREATE FUNCTION validateIntegerGreaterThanInfLimit(@number INT, @infLimit INT) RETURNS INT AS
BEGIN
	IF (@number > @infLimit)
		RETURN 1;
	RETURN 0;
END
GO

CREATE FUNCTION validateTeamOwnerRecord(@id INT, @fullName varchar(50)) RETURNS INT AS
BEGIN
	IF (dbo.validateIntegerGreaterThanInfLimit(@id, 0) = 1 AND dbo.validateGenericString(@fullName) = 1)
		RETURN 1;
	RETURN 0;
END
GO

CREATE FUNCTION validateTeamRecord(@id INT, @teamName varchar(50), @teamLeague varchar(50)) RETURNS INT AS
BEGIN
	IF (dbo.validateIntegerGreaterThanInfLimit(@id, 0) = 1 AND dbo.validateGenericString(@teamName) = 1 AND dbo.validateTeamLeague(@teamLeague) = 1)
		RETURN 1;
	RETURN 0;
END
GO

CREATE FUNCTION validateTeamOwnedByRecord(@ownerId INT, @teamId INT) RETURNS INT AS
BEGIN
	IF (dbo.validateIntegerGreaterThanInfLimit(@ownerId, 0) = 1 AND dbo.validateIntegerGreaterThanInfLimit(@teamId, 0) = 1)
		RETURN 1;
	RETURN 0;
END
GO

/* PRINT dbo.validateTeamRecord(1, 'FCSB', 'Liga 1'); */
