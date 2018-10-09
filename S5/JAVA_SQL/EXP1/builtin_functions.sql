--Question 1
select * from registration1 natural join staff1
where to_char(dateJoined,'mm')=10;
--Question 2
select 	memberNo,videoNo,to_char(dateReturn,'Day' ) as Day 
from RentalAgreement1;