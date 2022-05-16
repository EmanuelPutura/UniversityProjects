USE Football;
GO

CREATE OR ALTER PROCEDURE insertTeamOwnerAndTeamRollback(@fullName VARCHAR(50), @age INT, @teamName VARCHAR(50), @teamLeague VARCHAR(50)) AS
BEGIN
	SET NOCOUNT ON;

	BEGIN TRAN
	BEGIN TRY
		IF (dbo.validateTeamOwnerRecord(@fullName, @age) <> 1)
			RAISERROR('Invalid TeamOwner!', 14, 1);

		IF dbo.validateTeamRecord(@teamName, @teamLeague) <> 1
			RAISERROR('Invalid Team!', 14, 1);

		INSERT INTO TeamOwner VALUES(@fullName, @age);
		DECLARE @teamOwnerId INT = (SELECT IDENT_CURRENT('TeamOwner'));
		PRINT 'Inserted TeamOwner: (Id: ' + CONVERT(VARCHAR(10), @teamOwnerId) + '), named ' + @fullName + ', having ' + CONVERT(varchar(10), @age) + ' years old.';

		INSERT INTO Team VALUES(@teamName, @teamLeague);
		DECLARE @teamId INT = (SELECT IDENT_CURRENT('Team'));
		PRINT 'Inserted Team: (Id: ' + CONVERT(VARCHAR(10), @teamId) + '), named ' + @teamName + ', playing in league ' + @teamLeague + '.';

		INSERT INTO TeamOwnedBy VALUES(@teamOwnerId, @teamId);
		PRINT 'Linked TeamOwner with Team: (TeamOwnerId: ' + CONVERT(VARCHAR(10), @teamOwnerId) + ', ' + 'TeamId: ' + CONVERT(VARCHAR(10), @teamId) + ').';

		COMMIT TRAN
		PRINT 'Transaction commited!'
	END TRY

	BEGIN CATCH
		declare @errorMessage AS NVARCHAR(max) = error_message();
		PRINT @errorMessage

		rollback tran
		PRINT 'Transaction rollbacked!'
	END CATCH
END
GO

SET NOCOUNT ON;

DELETE FROM TeamOwnedBy;
DELETE FROM Team;
DELETE FROM TeamOwner;


EXEC insertTeamOwnerAndTeamRollback 'Gigi Becali', 63, 'FCSB', 'Liga 1';  -- should work

PRINT '-------------------------------------------------------------------';

EXEC insertTeamOwnerAndTeamRollback 'Gigi Becali', 63, 'FCSB', 'Liga 11'; -- should fail because of the league name

SELECT * FROM TeamOwner;
SELECT * FROM Team;
SELECT * FROM TeamOwnedBy;
