CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = main.c cJSON.c
OBJS = $(SRCS:.c=.o)
TARGET = app

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

cJSON.o: cJSON.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
