USE Football;
GO

CREATE OR ALTER PROCEDURE insertTeamOwnerAndTeamRollback(@fullName VARCHAR(50), @age INT, @teamName VARCHAR(50), @teamLeague VARCHAR(50)) AS
BEGIN
	SET NOCOUNT ON;
	declare @tempLogTable table(TypeOperation varchar(255), TableOperation varchar(255), ExecutionDate datetime)

	BEGIN TRAN
	BEGIN TRY
		IF (dbo.validateTeamOwnerRecord(@fullName, @age) <> 1)
			RAISERROR('Invalid TeamOwner name or age!', 14, 1);

		IF dbo.validateTeamRecord(@teamName, @teamLeague) <> 1
			RAISERROR('Invalid Team name or league!', 14, 1);

		INSERT INTO TeamOwner VALUES(@fullName, @age);
		DECLARE @teamOwnerId INT = (SELECT IDENT_CURRENT('TeamOwner'));
		PRINT 'Inserted TeamOwner: (Id: ' + CONVERT(VARCHAR(10), @teamOwnerId) + '), named ' + @fullName + ', having ' + CONVERT(varchar(10), @age) + ' years old.';
		insert into @tempLogTable values('TeamOwner', 'Insert', SYSDATETIME());

		INSERT INTO Team VALUES(@teamName, @teamLeague);
		DECLARE @teamId INT = (SELECT IDENT_CURRENT('Team'));
		PRINT 'Inserted Team: (Id: ' + CONVERT(VARCHAR(10), @teamId) + '), named ' + @teamName + ', playing in league ' + @teamLeague + '.';
		insert into @tempLogTable values('Team', 'Insert', SYSDATETIME());

		INSERT INTO TeamOwnedBy VALUES(@teamOwnerId, @teamId);
		PRINT 'Linked TeamOwner with Team: (TeamOwnerId: ' + CONVERT(VARCHAR(10), @teamOwnerId) + ', ' + 'TeamId: ' + CONVERT(VARCHAR(10), @teamId) + ').';
		insert into @tempLogTable values('TeamOwnedBy', 'Insert', SYSDATETIME());

		COMMIT TRAN
		PRINT 'Transaction commited!'
		insert into @tempLogTable values('All', 'Commit', SYSDATETIME());
	END TRY

	BEGIN CATCH
		declare @errorMessage AS NVARCHAR(max) = error_message();
		PRINT @errorMessage

		rollback tran
		PRINT 'Transaction rollbacked!'
		insert into @tempLogTable values('All', 'Rollback', SYSDATETIME());
	END CATCH

	INSERT INTO LogTable SELECT * FROM @tempLogTable;
END
GO

SET NOCOUNT ON;

DELETE FROM TeamOwnedBy;
DELETE FROM Team;
DELETE FROM TeamOwner;
DELETE FROM LogTable;


EXEC insertTeamOwnerAndTeamRollback 'Gigi Becali', 63, 'FCSB', 'Liga 1';  -- should work

PRINT '-------------------------------------------------------------------';

EXEC insertTeamOwnerAndTeamRollback 'Gigi Becali', 63, 'FCSB', 'Liga 11'; -- should fail because of the league name

SELECT * FROM TeamOwner;
SELECT * FROM Team;
SELECT * FROM TeamOwnedBy;
SELECT * FROM LogTable;
