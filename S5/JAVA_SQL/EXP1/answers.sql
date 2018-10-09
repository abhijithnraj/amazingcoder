--prettify
set lines 256
set trimout on
set tab off

-- Question number 1
update video1 set dailyrental=dailyrental+dailyrental*0.1 where category='Fantasy' ;
commit;
-- Question number 2
select DISTINCT(category) from video1;
-- Question number 3
select title,dailyrental*3 as ThreeDayRate from video1;
-- Question number 4
select * from staff1 where salary between 45000 and 50000;
-- Question number 5
select * from video1 where category in ('Action','Children');
-- Question number 6
select * from staff1 where name like 'Sally %';
-- Question number 7
select * from RentalAgreement1 where dateReturn is NULL;
-- Question number 8
select position from staff1 where name like '_o%';
-- Question number 9
select name from staff1 where position!='Manager' order by (name);
-- Question number 10
select * from video1 where price>20 order by (price);
-- Question number 11
--alter table video1 add constraint 
--delete from video1 where catalogno=634817 cascade constraint;
