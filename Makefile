test : test.o list.o priority_queue.o optimized_converter.o
	gcc test.o list.o optimized_converter.o priority_queue.o -o test

test.o : test.c optimized_converter.h
	gcc -c test.c

list.o : list.c list.h
	gcc -c list.c

priority_queue.o : priority_queue.c priority_queue.h
	gcc -c priority_queue.c

optimized_converter.o : optimized_converter.c optimized_converter.h
	gcc -c optimized_converter.c

clean :
	rm test test.o list.o priority_queue.o optimized_converter.o
