use Football;
go

SET DEADLOCK_PRIORITY HIGH;

--- Transaction T2
-- to be executed together with Transaction T1 from task3.sql file
BEGIN TRAN
-- print 'updating Team table...';
UPDATE Team
SET teamName='Univ. Craiova T2', teamLeague='Liga 2'
WHERE id > 0;

-- WAITFOR DELAY '00:00:05';

-- print 'updating TeamOwner table...';
UPDATE TeamOwner
set fullName='Mitrut Vasile T2', age = 999
WHERE id > 0;
COMMIT TRAN
