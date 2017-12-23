CC      = gcc
CCLIBS  = -I/usr/include/mysql/ -lmysqlclient
CCFLAGS = -Wall -Wextra
PROGRAM = ../app
OBJ     =             \
    main.o            \
    database.o        \
    command.o         \
    utils.o           \
    menu.o
VPATH    = src


%.o: %.c
	$(CC) -c -o $@ $< $(CCLIBS) $(CCFLAGS)

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $^ $(CCLIBS) $(CCFLAGS)
	cat scripts/create.sql scripts/trigger.sql scripts/insert.sql | mysql -u root -p

.PHONY: clean

clean:
	rm -f src/*.swp *.swp *~ src/*~ *.o
