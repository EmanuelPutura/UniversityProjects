IF NOT EXISTS (SELECT * FROM sys.databases WHERE name = 'PracticalExamII')
BEGIN
  CREATE DATABASE PracticalExamII;
END;
GO

use PracticalExamII;
go

drop table if exists Clubs;
drop table if exists SportLocation;
drop table if exists Locations;
drop table if exists Sports;
drop table if exists SportTypes;


create table SportTypes (
	id int not null primary key identity,
	stDescr varchar(255)
);

create table Sports (
	id int not null primary key identity,
	sName varchar(255),
	sDescr varchar(255),
	maxPlayersNo int,
	sTypeId int references SportTypes(id)
);


create table Locations (
	id int not null primary key identity,
	lName varchar(255),
	/*
		cityName varchar(255),
		villageName varchar(255),
	*/

	lCounty varchar(255),
	lCountry varchar(255)
);

create table SportLocation (
	spid int not null references Sports(id),
	lid int not null references Locations(id),
	playersNo int,

	primary key (spid, lid)
);

create table Clubs (
	id int not null primary key identity,
	cName varchar(255),
	openingYear int,
	starsNo int,
	lid int not null references Locations(id)
);

delete from SportTypes;
insert into SportTypes values ('team sports'), ('individual sports'), ('contact sports');

delete from Sports;
insert into Sports values ('football', 'football description', 11, 1), ('tennis', 'tennis description', 1, 2);

delete from Locations;
insert into Locations values ('Cluj-Napoca', 'Cluj', 'Romania'), ('Bistrita', 'B-N', 'Romania');

delete from SportLocation;
insert into SportLocation values (1, 1, 120), (1, 2, 50), (2, 1, 100);

delete from Clubs;
insert into CLubs values ('CFR Cluj', 1907, 11, 1), ('Gloria Bistrita', 1941, 26, 2), ('U Cluj', 1930, 10, 1);

select * from SportTypes;
select * from Sports;
select * from Locations;
select * from SportLocation;
select * from Clubs;
