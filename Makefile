CC = gcc 
#orig CC = clang++
#-std=c11
CFLAGS = -Wall -mavx2
# DEBUG mode
#CFLAGS += -g
# RELEASE mode
CFLAGS += -O2 -DNDEBUG
LDFLAGS =

APP_NAME = streebog_bitslice_test
APP_SOURCES = $(wildcard *.c)
APP_OBJECTS = $(APP_SOURCES:%.c=%.o)

all: $(APP_OBJECTS)
	$(CC) $(LDFLAGS) $(APP_OBJECTS) -o $(APP_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

profile: $(APP_NAME)
	rm -f callgrind.out
	valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./$(APP_NAME)
	kcachegrind callgrind.out

clean:
	rm -f *.o $(APP_NAME) callgrind.out
	rm -rf TEST*

