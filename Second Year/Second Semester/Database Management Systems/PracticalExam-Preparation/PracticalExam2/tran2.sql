use TestDatabase;
go

begin tran
update TaskTypes set name = 'Deadlock2' where id = 1;
waitfor delay '00:00:05'
update Developers set firstName = 'Deadlock2' where id = 1;
commit tran
