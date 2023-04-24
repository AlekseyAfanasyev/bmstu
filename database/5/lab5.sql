-- copy from table to csv
COPY chessplayers TO '~/Database/chessplayers.csv' DELIMITER ',' CSV HEADER;

-- copy to table from csv
COPY chessplayers FROM '~/Database/chessplayers.csv' DELIMITER ',' CSV HEADER;

-- change postgres password
ALTER USER postgres PASSWORD '123'

