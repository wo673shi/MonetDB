start transaction;
create table analytics (aa int, bb int, cc bigint);
insert into analytics values (15, 3, 15), (3, 1, 3), (2, 1, 2), (5, 3, 5), (NULL, 2, NULL), (3, 2, 3), (4, 1, 4), (6, 3, 6), (8, 2, 8), (NULL, 4, NULL);

select percent_rank() over (partition by aa) from analytics;
select percent_rank() over (partition by aa order by aa asc) from analytics;
select percent_rank() over (partition by aa order by aa desc) from analytics;
select percent_rank() over (order by aa) from analytics;
select percent_rank() over (order by aa desc) from analytics;

select percent_rank() over (partition by bb) from analytics;
select percent_rank() over (partition by bb order by bb asc) from analytics;
select percent_rank() over (partition by bb order by bb desc) from analytics;
select percent_rank() over (order by bb) from analytics;
select percent_rank() over (order by bb desc) from analytics;

select cume_dist() over (partition by aa) from analytics;
select cume_dist() over (partition by aa order by aa asc) from analytics;
select cume_dist() over (partition by aa order by aa desc) from analytics;
select cume_dist() over (order by aa) from analytics;
select cume_dist() over (order by aa desc) from analytics;

select cume_dist() over (partition by bb) from analytics;
select cume_dist() over (partition by bb order by bb asc) from analytics;
select cume_dist() over (partition by bb order by bb desc) from analytics;
select cume_dist() over (order by bb) from analytics;
select cume_dist() over (order by bb desc) from analytics;

select ntile(1) over (partition by aa) from analytics;
select ntile(1) over (partition by aa order by aa asc) from analytics;
select ntile(1) over (partition by aa order by aa desc) from analytics;
select ntile(1) over (order by aa) from analytics;
select ntile(1) over (order by aa desc) from analytics;

select ntile(3) over (partition by bb) from analytics;
select ntile(3) over (partition by bb order by bb asc) from analytics;
select ntile(3) over (partition by bb order by bb desc) from analytics;
select ntile(3) over (order by bb) from analytics;
select ntile(3) over (order by bb desc) from analytics;

select ntile(10) over (partition by aa) from analytics;
select ntile(10) over (partition by aa order by aa asc) from analytics;
select ntile(10) over (partition by aa order by aa desc) from analytics;
select ntile(10) over (order by aa) from analytics;
select ntile(10) over (order by aa desc) from analytics;

select first_value(aa) over (partition by aa) from analytics;
select first_value(aa) over (partition by aa order by aa asc) from analytics;
select first_value(aa) over (partition by aa order by aa desc) from analytics;
select first_value(aa) over (order by aa) from analytics;
select first_value(aa) over (order by aa desc) from analytics;

select first_value(aa) over (partition by bb) from analytics;
select first_value(aa) over (partition by bb order by bb asc) from analytics;
select first_value(aa) over (partition by bb order by bb desc) from analytics;
select first_value(aa) over (order by bb) from analytics;
select first_value(aa) over (order by bb desc) from analytics;

select last_value(bb) over (partition by aa) from analytics;
select last_value(bb) over (partition by aa order by aa asc) from analytics;
select last_value(bb) over (partition by aa order by aa desc) from analytics;
select last_value(bb) over (order by aa) from analytics;
select last_value(bb) over (order by aa desc) from analytics;

select last_value(bb) over (partition by bb) from analytics;
select last_value(bb) over (partition by bb order by bb asc) from analytics;
select last_value(bb) over (partition by bb order by bb desc) from analytics;
select last_value(bb) over (order by bb) from analytics;
select last_value(bb) over (order by bb desc) from analytics;

select percent_rank() over () from analytics;
select cume_dist() over () from analytics;
select ntile(1) over () from analytics;
select ntile(2) over () from analytics;
select ntile(5) over () from analytics;
select ntile(11) over () from analytics;
select ntile(100) over () from analytics;

select first_value(aa) over () from analytics;
select first_value(bb) over () from analytics;
select last_value(aa) over () from analytics;
select last_value(bb) over () from analytics;

create table stressme (aa varchar(64), bb int);
insert into stressme values ('one', 1), ('another', 1), ('stress', 1), (NULL, 2), ('ok', 2), ('check', 3), ('me', 3), ('please', 3), (NULL, 4);

select first_value(aa) over (partition by bb) from stressme;
select first_value(aa) over (partition by bb order by bb asc) from stressme;
select first_value(aa) over (partition by bb order by bb desc) from stressme;
select first_value(aa) over (order by bb) from stressme;
select first_value(aa) over (order by bb desc) from stressme;

select last_value(aa) over (partition by bb) from stressme;
select last_value(aa) over (partition by bb order by bb asc) from stressme;
select last_value(aa) over (partition by bb order by bb desc) from stressme;
select last_value(aa) over (order by bb) from stressme;
select last_value(aa) over (order by bb desc) from stressme;

rollback;
