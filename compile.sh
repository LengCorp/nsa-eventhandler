gcc main.c $(mysql_config --cflags) -o main $(mysql_config --libs) -Wall -ltelldus-core
