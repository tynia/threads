all: threads

# which compiler
CC = g++

# include directory
INCLUDE = ../threads

# compile flags
CFLAGS = -O -ggdb -Wall -D_LINUX -D_DEBUG -I$(INCLUDE)

# link flags
LFLAGS = -lpthread -lm -ldl

# target
threads: threads.o threadMgr.o thdTaskMgr.o base.o writer.o thread.o \
IO.o
	$(CC) -o threads threads.o threadMgr.o thdTaskMgr.o base.o \
	writer.o thread.o IO.o $(LFLAGS)

threads.o: ../sample/threads.cpp
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ../sample/threads.cpp

thread.o: ../threads/thread.cpp
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ../threads/thread.cpp

threadMgr.o: ../threads/threadMgr.cpp
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ../threads/threadMgr.cpp

thdTaskMgr.o: ../threads/task/thdTaskMgr.cpp
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ../threads/task/thdTaskMgr.cpp

base.o: ../threads/logger/base.cpp
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ../threads/logger/base.cpp

writer.o: ../threads/logger/writer.cpp
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ../threads/logger/writer.cpp

IO.o: ../threads/util/file/IO.cpp
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ../threads/util/file/IO.cpp

clean:
	rm -f *.o
