use TestDatabase;
go

set deadlock_priority high;

begin tran
update Developers set firstName = 'Deadlock1' where id = 1;
waitfor delay '00:00:05'
update TaskTypes set name = 'Deadlock1' where id = 1;
commit tran

select * from Developers;
select * from TaskTypes;
