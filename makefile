
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CC 			= gcc
CFLAGS 	= -g -Wall
RM 			= rm -f

TARGET = mainCinstructions

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) route-records.c $(TARGET).c

clean:
	$(RM) $(TARGET)