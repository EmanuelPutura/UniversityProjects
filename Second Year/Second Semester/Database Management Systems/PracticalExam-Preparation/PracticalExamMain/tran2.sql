use PracticalExamII;
go

set transaction isolation level repeatable read;

begin tran
select * from Locations;
waitfor delay '00:00:05';
select * from Locations;
commit tran

-- solution
set transaction isolation level serializable;
