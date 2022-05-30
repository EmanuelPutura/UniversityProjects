USE Exam2
GO

CREATE TABLE Developers (
	id INT PRIMARY KEY IDENTITY(1, 1),
	first_name VARCHAR(100),
	last_name VARCHAR(100)
)

CREATE TABLE Projects (
	id_project INT PRIMARY KEY IDENTITY(1, 1),
	start_date_ date,
	end_date date
)

CREATE TABLE TaskTypes (
	id INT PRIMARY KEY IDENTITY(1, 1),
	name_ VARCHAR(100),
	descript VARCHAR(100)
)

CREATE TABLE TaskPriorities (
	id INT PRIMARY KEY IDENTITY(1, 1),
	name_ VARCHAR(100),
	descript VARCHAR(100)
)

CREATE TABLE Statuses (
	id INT PRIMARY KEY IDENTITY(1, 1),
	current_status VARCHAR(100)
)

CREATE TABLE Tasks (
	id_task INT PRIMARY KEY IDENTITY(1, 1),
	title VARCHAR(100),
	descript VARCHAR(100),
	id_project INT FOREIGN KEY REFERENCES Projects(id_project),
	id_developer INT FOREIGN KEY REFERENCES Developers(id),
	task_type INT FOREIGN KEY REFERENCES TaskTypes(id),
	status_ INT FOREIGN KEY REFERENCES Statuses(id),
	task_priority INT FOREIGN KEY REFERENCES TaskPriorities(id),
	CONSTRAINT unique_task_dev UNIQUE(id_project, id_developer)
)

DROP TABLE Tasks
DROP TABLE TaskTypes
DROP TABLE TaskPriorities
DROP TABLE Statuses
DROP TABLE Developers
DROP TABLE Projects



INSERT INTO Statuses VALUES ('started'), ('in progress'), ('closed')
INSERT INTO TaskTypes VALUES	('technical', 'idk'),
								('bug', 'idk'),
								('improvement', 'idk')
INSERT INTO TaskPriorities VALUES ('critical', 'idk'),
									('show-stopper', 'idk'),
									('minor', 'idk'),
									('trivial', 'idk')

INSERT INTO Developers VALUES ('Jane', 'Doe'), ('John', 'Doe')

INSERT INTO Projects VALUES ('2/2/2022', '6/6/2022')
INSERT INTO Projects VALUES ('3/3/2022', '7/7/2022')
INSERT INTO Projects VALUES ('4/4/2022', '8/8/2022')
INSERT INTO Projects VALUES ('5/5/2022', '9/9/2022')

INSERT INTO Tasks VALUES ('task1', 'idk', 1, 1, 1, 1, 1)
INSERT INTO Tasks VALUES ('task2', 'idk', 2, 2, 2, 2, 2)

SELECT * FROM Developers
SELECT * FROM Projects
SELECT * FROM TaskTypes
SELECT * FROM TaskPriorities
SELECT * FROM Statuses
SELECT * FROM Tasks
