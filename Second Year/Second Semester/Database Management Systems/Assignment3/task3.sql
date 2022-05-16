use Football;
go

-- DIRTY READS
delete from TeamOwner;
insert into TeamOwner values ('Gigi Becali', 63);

begin tran;
print 'updating TeamOwner table...';
update TeamOwner
set fullName = 'Mitrut Vasile', age = 999
where id > 0;
waitfor delay '00:00:05';
rollback tran;
print 'Rolled back TeamOwner update';


-- NON-REPEATABLE READS
delete from TeamOwner;
insert into TeamOwner values ('Gigi Becali', 63);

begin tran;
waitfor delay '00:00:05';
print 'updating TeamOwner table...';
UPDATE TeamOwner
set fullName='Mitrut Vasile', age = 999
WHERE id > 0;
commit tran
print 'Rolled back TeamOwner update';

-- PHANTOM READS
delete from TeamOwner;
BEGIN TRAN
WAITFOR DELAY '00:00:04';
insert into TeamOwner values ('Gigi Becali', 63);
COMMIT TRAN

-- DEADLOCKS
delete from TeamOwner;
insert into TeamOwner values ('Gigi Becali', 63);

delete from Team;
insert into Team values ('FCSB', 'Liga 1');

--- Transaction T1
BEGIN TRAN
UPDATE TeamOwner
set fullName='Mitrut Vasile T1', age = 999
WHERE id > 0;

WAITFOR DELAY '00:00:05';

UPDATE Team
SET teamName='Univ. Craiova T1', teamLeague='Liga 2'
WHERE id > 0;
COMMIT TRAN

select * from TeamOwner;
select * from Team;

-- UPDATE CONFLICT
delete from TeamOwner;
insert into TeamOwner values ('Gigi Becali', 63);

-- Transaction T1
WAITFOR DELAY '00:00:05';
BEGIN TRAN
UPDATE TeamOwner
set fullName='Mitrut Vasile T1', age = 999
WHERE id > 0;
WAITFOR DELAY '00:00:05';
COMMIT TRAN
