--SET DEADLOCK_PRIORITY LOW

BEGIN TRAN
UPDATE TaskPriorites SET name_ = 'Tran2' WHERE descript = 'Deadlock'
-- this tran has exclusively lock on table 
WAITFOR DELAY '00:00:05'
UPDATE TaskTypes SET name_ = 'Tran2' WHERE descript = 'Deadlock'
COMMIT TRAN