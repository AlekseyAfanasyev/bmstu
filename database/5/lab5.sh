# непрерывное архивирование
su - postgres
locate postgresql.conf # get postgresql.conf location
nano /etc/postgresql/12/main/postgresql.conf
# write to file:
# ...
# wal_level = replica
# archive_mode = on
# archive_command = 'test ! -f /mnt/server/archive_c/%f && cp %p /mnt/server/archive_c/%f'
service postgresql restart
rm -rf archive_b # delete folder if exists
pg_basebackup -D archive_b/ -Ft -z


# postgres:
# -- copy from table to csv
# COPY chessplayers TO '~/Database/chessplayers.csv' DELIMITER ',' CSV HEADER;

# -- copy to table from csv
# COPY chessplayers FROM '~/Database/chessplayers.csv' DELIMITER ',' CSV HEADER;
# -- change postgres password
# ALTER USER postgres PASSWORD '123'


# make backup via pg_dump
pg_dump chess_games -h localhost -p 5432 -U postgres > '/home/dmitriy/backup.sql'

# use backup
psql test_db < /home/dmitriy/backup.sql postgres

# backup via files
service postgresql stop
sudo tar -cf /var/lib/postgresql/12/main
service postgresql start

# use backup files
service postgresql stop
rm -rf /var/lib/postgresql/12/main
tar -xf backup.tar
service postgresql start

# may break dependency: sudo chown -R /var/lib/postgresql/12/main/
