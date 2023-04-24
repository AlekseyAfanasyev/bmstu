-- select all from table
SELECT * FROM customers;

-- select only several
SELECT first_name, last_name, city, company_name
FROM customers;

--select with sorting
SELECT order_id, ship_date, paid_date, status
FROM orders
ORDER BY ship_date

--select with limitation
SELECT order_id, ship_date, paid_date, status
FROM orders
ORDER BY ship_date
LIMIT 5

--select with compares
SELECT item_id, product_id, quantity
FROM items
WHERE quantity > 1000

--select with between
SELECT *
from customers
where customer_id between 1 and 3

-- select with in and subquery
SELECT order_id, order_date, paid_date, status
FROM orders
INNER JOIN customers ON orders.customer_id = customers.customer_id
WHERE customers.city = 'Moscow'

--select with like and string functions
SELECT * FROM customers WHERE city LIKE 'M%' AND CHAR_LENGTH(company_name) = 5

-- select with is null
SELECT * FROM customers WHERE address is null

--select with aggregate functions
select max(total) from items

-- select with aggregate functoins and having
SELECT city, count(*)
FROM customers
GROUP BY city
HAVING city LIKE 'M%'

--select with predicate joining
--final task 1

--select with distinct
--final task 2

--select with exists
SELECT * 
FROM customers
WHERE NOT EXISTS
(SELECT * FROM orders WHERE status = 'P' AND orders.cutomer_id = customers.customer_id)

--select with case
SELECT customer_id,
    CASE WHEN customer_id = 2 THEN 'two'
    ELSE 'not two'
    END
FROM customers



-- final task 1
SELECT customers.company_name, customers.last_name, customers.first_name, customers.address, customers.phone, customers.city
FROM orders
INNER JOIN customers ON orders.customer_id = customers.customer_id
WHERE orders.status = 'P'
ORDER BY customers.city, customers.last_name;

SELECT company_name, last_name, first_name, address, phone, city
FROM customers
WHERE customer_id IN (
SELECT customer_id FROM orders WHERE status = 'P')
ORDER BY city, last_name
-- final task 2
SELECT DISTINCT customers.city, COUNT(customers.customer_id)
FROM orders
INNER JOIN customers ON orders.customer_id = customers.customer_id
WHERE orders.status = 'P'
GROUP BY customers.city;
