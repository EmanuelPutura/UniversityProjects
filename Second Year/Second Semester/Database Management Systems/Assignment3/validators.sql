USE Football;
GO

CREATE OR ALTER FUNCTION validateGenericStringName(@string varchar(50)) RETURNS INT AS
BEGIN
	IF (LEN(@string) < 1 OR SUBSTRING(@string COLLATE Latin1_General_CS_AS, 1, 1) = LOWER(SUBSTRING(@string COLLATE Latin1_General_CS_AS, 1, 1)))
		RETURN 0;
	RETURN 1;
END
GO

CREATE OR ALTER FUNCTION validateTeamLeague (@league varchar(50)) RETURNS INT AS
BEGIN
	IF(@league IN ('Liga 1', 'Liga 2', 'Liga 3', 'Liga 4') AND dbo.validateGenericStringName(@league) = 1)
		RETURN 1;
	
	RETURN 0;
END
GO

CREATE OR ALTER FUNCTION validateIntegerGreaterThanInfLimit(@number INT, @infLimit INT) RETURNS INT AS
BEGIN
	IF (@number > @infLimit)
		RETURN 1;
	RETURN 0;
END
GO

CREATE OR ALTER FUNCTION validateTeamOwnerRecord(@fullName varchar(50), @age INT) RETURNS INT AS
BEGIN
	IF (dbo.validateIntegerGreaterThanInfLimit(@age, 17) = 1 AND dbo.validateGenericStringName(@fullName) = 1)
		RETURN 1;
	RETURN 0;
END
GO

CREATE OR ALTER FUNCTION validateTeamRecord(@teamName varchar(50), @teamLeague varchar(50)) RETURNS INT AS
BEGIN
	IF (dbo.validateGenericStringName(@teamName) = 1 AND dbo.validateTeamLeague(@teamLeague) = 1)
		RETURN 1;
	RETURN 0;
END
GO
