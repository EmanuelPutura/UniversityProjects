use TestDatabase;
go

drop table if exists Tasks;
drop table if exists TaskStatuses;
drop table if exists TaskPriorities;
drop table if exists TaskTypes;
drop table if exists Projects;
drop table if exists Developers;

create table Developers(
	id int not null primary key identity,
	firstName varchar(255) not null,
	lastName varchar(255) not null,
	
);

create table Projects(
	id int not null primary key identity,
	startDate date,
	endDate date
);

create table TaskTypes(
	id int not null primary key identity,
	name varchar(255),
	description varchar(255),
);

create table TaskPriorities(
	id int not null primary key identity,
	name varchar(255),
	description varchar(255),
);

create table TaskStatuses(
	id int not null primary key identity,
	statusName varchar(255) not null,
);

create table Tasks(
	id int not null primary key identity,
	title varchar(255),
	description varchar(255),
	developerId int not null references Developers(id),
	projectId int not null references Projects(id),
	taskTypeId int not null references TaskTypes(id),
	taskPriorityId int not null references TaskPriorities(id),
	taskStatusId int not null references TaskStatuses(id),
);

delete from Developers;
delete from Projects;
delete from TaskTypes;
delete from TaskPriorities;
delete from TaskStatuses;
delete from Tasks;


insert into Developers values ('Dev1F', 'Dev1L'), ('Dev2F', 'Dev2L'), ('Dev3F', 'Dev3L'), ('Dev4F', 'Dev4L'), ('Dev5F', 'Dev5L');

insert into Projects values ('2/2/2022', '6/6/2022'), ('2/1/2011', '1/1/2012'), ('1/1/2012', '5/2/2012');

insert into TaskTypes values ('TType1', 'TDesc1'), ('TType2', 'TDesc2'), ('TType3', 'TDesc3');

insert into TaskPriorities values ('PType1', 'PDesc1'), ('PType2', 'PDesc2'), ('PType3', 'PDesc3');

insert into TaskStatuses values ('status1'), ('status2'), ('status3');

insert into Tasks values ('title1', 'descr1', 1, 1, 1, 1, 1), ('title2', 'descr2', 1, 2, 1, 2, 1), ('title3', 'descr3', 2, 2, 1, 2, 2), 
				('title4', 'descr4', 2, 1, 1, 1, 2), ('title5', 'descr5', 2, 2, 1, 1, 1);

select * from Developers;
select * from Projects;
select * from TaskTypes;
select * from TaskPriorities;
select * from TaskStatuses;
select * from Tasks;
