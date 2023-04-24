-- create view
create view strong_players (name) as
select name from chessplayers where elo_rating > 2000

-- select view
select * from strong_players

-- check data
select name from chessplayers where elo_rating > 2000

-- alter view
alter view strong_players rename strongest_players

--insert view
insert into strong_players values('Михаил Елизаров')

--with check
create or replace view strong_players as
select name from chessplayers where elo_rating > 2000 with check option

--rename column
alter table strong_players rename column fio to name

-- create from 2 tables
create view vTournaments (tournament, winner) as
select tournaments.name, winner.name
from tournaments
inner join chessplayers as winner on winner.chessplayer_id=tournaments.winner_id

-- delete view
drop view strong_players

--create role
create role selectel_user with
	login
	nosuperuser
	nocreaterole
	inherit
	noreplication
	connection limit -1;
grant pg_monitor to selectel_user

--let user1 create db
ALTER ROLE user1 CREATEDB;

--let user1 edit data

--create db and 2 tables on user1
CREATE table test_table (
	id int not null)
	
CREATE table test_table_based (
	id int not null)
	
--delete pg_monitor from user
revoke pg_monitor from selectel_user

--create new users
create role user1
create role user2

--grant read rights to user1 and write rights to user2
grant select on all tables in schema public to user1

grant select on all tables in schema public to user2
grant insert on all tables in schema public to user2
grant update on all tables in schema public to user2

--grant user1 to user3
grant user1 to user3

--remove select orders from user1=3
revoke select on orders from user3

--delete bd and roles
drop database test
drop role user1
drop role user2


