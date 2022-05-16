use Football;
go

create or alter procedure insertTeamOwnerAndTeamRecover(@fullName VARCHAR(50), @age INT, @teamName VARCHAR(50), @teamLeague VARCHAR(50)) as
begin
	set nocount on
	declare @shouldLinkViaJoinTable int = 1
	declare @errorMessage as nvarchar(max) = null

	declare @teamOwnerId int = null
	declare @teamId int = null

	declare @tempLogTable table(TypeOperation varchar(255), TableOperation varchar(255), ExecutionDate datetime)

	begin try
		if dbo.validateTeamOwnerRecord(@fullName, @age) <> 1
			raiserror('Invalid TeamOwner name or age!', 14, 1)
		
		insert into TeamOwner values(@fullName, @age)
		set @teamOwnerId = (select IDENT_CURRENT('TeamOwner'))
		print 'Inserted TeamOwner: (Id: ' + CONVERT(VARCHAR(10), @teamOwnerId) + '), named ' + @fullName + ', having ' + CONVERT(varchar(10), @age) + ' years old.';
		
		insert into @tempLogTable values('TeamOwner', 'Insert', SYSDATETIME());
		insert into @tempLogTable values('TeamOwner', 'Commit', SYSDATETIME());
	end try
	begin catch
		set @shouldLinkViaJoinTable = 0

		set @errorMessage = error_message();
		print @errorMessage
		
		insert into @tempLogTable values('TeamOwner', 'Rollback', SYSDATETIME());
	end catch

	begin try 
		if dbo.validateTeamRecord(@teamName, @teamLeague) <> 1
			raiserror('Invalid Team name or league!', 14, 1)

		insert into Team values(@teamName, @teamLeague)
		set @teamId = (select IDENT_CURRENT('Team'))
		print 'Inserted Team: (Id: ' + CONVERT(VARCHAR(10), @teamId) + '), named ' + @teamName + ', playing in league ' + @teamLeague + '.';
	
		insert into @tempLogTable values('Team', 'Insert', SYSDATETIME());
		insert into @tempLogTable values('Team', 'Commit', SYSDATETIME());
	end try
	begin catch
		set @shouldLinkViaJoinTable = 0

		set @errorMessage = error_message();
		print @errorMessage
		
		insert into @tempLogTable values('Team', 'Rollback', SYSDATETIME());
	end catch

	if @shouldLinkViaJoinTable <> 1
	begin
		insert into LogTable select * from @tempLogTable;
		return
	end

	insert into TeamOwnedBy values(@teamOwnerId, @teamId)
	print 'Linked TeamOwner with Team: (TeamOwnerId: ' + CONVERT(VARCHAR(10), @teamOwnerId) + ', ' + 'TeamId: ' + CONVERT(VARCHAR(10), @teamId) + ').';
	
	insert into @tempLogTable values('TeamOwnedBy', 'Insert', SYSDATETIME());
	insert into @tempLogTable values('TeamOwnedBy', 'Commit', SYSDATETIME());

	insert into LogTable select * from @tempLogTable;
end
go

SET NOCOUNT ON;

DELETE FROM TeamOwnedBy;
DELETE FROM Team;
DELETE FROM TeamOwner;
DELETE FROM LogTable;


EXEC insertTeamOwnerAndTeamRecover 'Gigi Becali', 63, 'FCSB', 'Liga 1';  -- should work

PRINT '-------------------------------------------------------------------';

EXEC insertTeamOwnerAndTeamRecover 'Lutu', 50, 'FCSB 2', 'Liga 22'; -- should fail because of the league name, however TeamOwner gets inserted
EXEC insertTeamOwnerAndTeamRecover 'Gheorghe Hagi', 55, '', 'Liga 1'; -- should fail because of the team name, however TeamOwner gets inserted
EXEC insertTeamOwnerAndTeamRecover 'mihai rotaru', 55, 'Univ. Craiova', 'Liga 1'; -- should fail because of the owner name, nothing gets inserted
EXEC insertTeamOwnerAndTeamRecover 'Nelutu Varga', 50, 'CFR', 'Liga 1';  -- should work


SELECT * FROM TeamOwner;
SELECT * FROM Team;
SELECT * FROM TeamOwnedBy;
SELECT * FROM LogTable;
