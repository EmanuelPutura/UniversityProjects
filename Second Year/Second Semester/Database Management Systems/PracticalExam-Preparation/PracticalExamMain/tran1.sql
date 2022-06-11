use PracticalExamII;
go

/*
	The phantom read concurrency issue is produced under an isolation level <= REPEATABLE READ.
	The solution is setting the isolation level to SERIALIZABLE.

	The problem occurs when a transaction T reads a set of objects based on a search predicate and the set can be changed by other
	transactions that are also in progress. By setting the isolation level to SERIALIZABLE, the set of objects search by a predicate is "locked", 
	such that any other transactions cannot modify it until the transaction commits (these locks are held until the end).
*/

begin tran
waitfor delay '00:00:05';
insert into Locations (lName, lCounty, lCountry) values ('TestName1', 'TestCounty1', 'TestCountry1');
commit tran
