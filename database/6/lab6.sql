-- create procedure (insert)
create or replace procedure add_place(new_city varchar(50), new_country varchar(50))
language sql
as $$
	insert into places values (default, new_city, new_country);
$$;
call add_place('novosibirsk', 'russia');
select * from places;

--create procedure (theory example)
create procedure theory_example(x real)
language sql
as $$
	select *
	from chessplayers
	where elo_rating > x
	$$;
call theory_example(3);

--create procedure - select chessplayer from name
create or replace function theory_example(x real)
returns table(chessplayer_id int,
			name character(50),
			elo_rating int,
			birth_year int)
language plpgsql
as 
$func$
begin
	return query
	select *
	from chessplayers
	where chessplayers.elo_rating > x;
end 
$func$;
select * from theory_example(3000);

--search by chessplayer name
create or replace function select_chessplayer(x character(50))
returns table(chessplayer_id int,
			name character(50),
			elo_rating int,
			birth_year int)
language plpgsql
as 
$func$
begin
	return query
	select *
	from chessplayers
	where chessplayers.name = x;
end 
$func$;
select * from select_chessplayer('Мария Карповец');

-- search in range
create or replace function search_chessplayer_by_range(x int, y int)
returns table(chessplayer_id int,
			name character(50),
			elo_rating int,
			birth_year int)
language plpgsql
as 
$func$
begin
	return query
	select *
	from chessplayers
	where chessplayers.elo_rating between x and y;
end 
$func$;
select * from search_chessplayer_by_range(2000, 3000);

-- create insert/update trigger

create or replace function decrease_products() returns trigger as $decrease_products$
	begin
		if new.order_date > new.ship_date then
			raise exception 'Order date should be AFTER the ship_date';
		end if;
		return new;
	end;
$decrease_products$ language plpgsql;
create trigger decrease_products before insert or update on orders
	for each row execute procedure decrease_products();
insert into orders values(default, 1, '2017-03-14', '2016-10-10', '2017-12-30', 'P')

--create delete trigger

create or replace function check_delete_cutomer() returns trigger as $check_delete_customers$
declare amount bigint;
	begin
		select into amount count(*) from orders where orders.customer_id = old.customer_id; 
		if amount > 0 then
			raise exception 'You have orders from customer you trying to delete.';
		end if;
		return new;
	end;
$check_delete_customers$ language plpgsql;
create trigger check_delete_cutomer before insert or update on orders
	for each row execute procedure check_delete_cutomer();
delete from customers where customer_id  = 1;

-- 6
CREATE OR REPLACE FUNCTION delete_product() RETURNS TRIGGER AS $$
BEGIN
    DELETE FROM items WHERE items.product_id = OLD.product_id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER delete_product  BEFORE DELETE ON products
FOR EACH ROW
EXECUTE FUNCTION delete_product();




-- 19 вариант
create or replace function products_list(first_id real, second_id real)
returns table(product_id int,
			product_name character(150),
			in_stock int,
			re_order boolean,
			description text,
			product_price money)
language plpgsql
as 
$func$
begin
	return query
	select *
	from products
	where products.product_id in (
	select items.product_id from items where items.order_id = first_id or items.order_id = second_id );
end 
$func$;
select * fromm products_list(1, 2);

create or replace function products_in_city(search_city character(50))
returns table(product character(150),
			  amount bigint)
language plpgsql
as 
$func$
begin
	return query
	select products.product_name, count(*)
	from items
	inner join products on products.product_id = items.product_id
	inner join orders on orders.order_id = items.order_id
	where orders.customer_id in (
	select customers.customer_id from customers where customers.city = search_city)
	group by products.product_name;
end 
$func$;
select * from products_in_city('Moscow')


