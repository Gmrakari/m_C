# CC = gcc
# CFLAGS = -Wall -Wextra -std=c99

# SRCS = jpg_2_base64.c utils_base64/01_base64.c
# OBJS = $(SRCS:.c=.o)
# TARGET = app

# $(TARGET): $(OBJS)
# 	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) 

# read_jpg_img.o: jpg_2_base64.c utils_base64/01_base64.h
# 	$(CC) $(CFLAGS) -c $< -o $@ 

# clean:
# 	rm -f $(OBJS) $(TARGET)

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

SRCS = jpg_2_base64.c utils_base64/01_base64.c
OBJS = $(SRCS:.c=.o)
TARGET = app

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) 

read_jpg_img.o: jpg_2_base64.c utils_base64/01_base64.h
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY: clean test

test: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
