CC = gcc
CONSERVATIVE_FLAGS = -std=c99 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)


#Add a target to create the project executable here
pproject: project.o ppm_io.o imageManip.o
	$(CC) -lm project.o ppm_io.o -o project imageManip.o

test: testImageManip.o imageManip.o
	$(CC) -o test  testImageManip.o imageManip.o -lm
	./test

project.o: project.c ppm_io.h imageManip.h
	$(CC) $(CFLAGS) -c project.c

# Compiles imageManip.c into an object file
imageManip.o: imageManip.c imageManip.h ppm_io.h
	$(CC) $(CFLAGS) -c imageManip.c

# Compiles ppm_io.o into an object file
ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c

testImageManip.o: testImageManip.c imageManip.h
	$(CC) $(CFLAGS) -c testImageManip.c
# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o project
	rm  -f *.o test
