all:
	gcc printer_race_condition.c -o prog -lpthread
	gcc printer_race_condition_mutex.c -o prog-mutex -lpthread

run:
	./prog
	
mutex:
	./prog-mutex
