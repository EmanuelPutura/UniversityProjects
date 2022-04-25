/*
	a table with a single-column primary key and no foreign keys:
		- table: FieldPositions
		- PK: position
		- FK: none
*/

SELECT name AS [Key Constraints] FROM sys.key_constraints
WHERE OBJECT_NAME(parent_object_id) = 'FieldPositions';

SELECT OBJECT_NAME(constraint_object_id) AS [Foreign Key] FROM sys.foreign_key_columns
WHERE OBJECT_NAME(parent_object_id) = 'FieldPositions';

/*
	a table with a single-column primary key and at least one foreign key:
		- table: TeamCoaches
		- PK: coachID
		- FK: prefferedFormation, assistantFitnessCoach
*/

SELECT name AS [Key Constraints] FROM sys.key_constraints
WHERE OBJECT_NAME(parent_object_id) = 'TeamCoaches';

SELECT OBJECT_NAME(constraint_object_id) AS [Foreign Key] FROM sys.foreign_key_columns
WHERE OBJECT_NAME(parent_object_id) = 'TeamCoaches';

/*
	a table with a multicolumn primary key - table
		- table: PlayerHasPosition
		- PK: (player, position)
*/


SELECT name AS [Key Constraints] FROM sys.key_constraints
WHERE OBJECT_NAME(parent_object_id) = 'PlayerHasPosition';
