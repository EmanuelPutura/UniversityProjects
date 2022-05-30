USE Exam2
GO

-- INSERT

BEGIN TRAN
UPDATE TaskTypes SET name_ = 'Tran1' WHERE descript = 'Deadlock'
-- this tran has exclusively lock on table 
WAITFOR DELAY '00:00:05'
UPDATE TaskPriorites SET name_ = 'Tran1' WHERE descript = 'Deadlock'
COMMIT TRAN