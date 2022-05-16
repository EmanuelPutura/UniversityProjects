use Football;
go

delete from TeamOwner;

insert into TeamOwner values ('Gigi Becali', 63);
insert into TeamOwner values ('Mihai Rotaru', 55);
insert into TeamOwner values ('Nelutu Varga', 45);
insert into TeamOwner values ('Felix Pop', 19);

select * from TeamOwner;


delete from Team;

insert into Team values ('FCSB', 'Liga 1');
insert into Team values ('Univ. Craiova', 'Liga 1');
insert into Team values ('CFR', 'Liga 4');

select * from Team;

delete from TeamOwnedBy;
