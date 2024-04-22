CC = gcc
CFLAGS = -Wall -Wextra -std=c99
VALGRIND = valgrind --leak-check=full

SRCS = main.c cJSON.c app_cjson_test.c app_asr_parse_resp.c base64.c
OBJS = $(SRCS:.c=.o)
TARGET = app

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

app_cjson_test.o: app_cjson_test.c
	$(CC) $(CFLAGS) -c $< -o $@

app_asr_parse_resp.o: app_asr_parse_resp.c
	$(CC) $(CFLAGS) -c $< -o $@

cJSON.o: cJSON.c
	$(CC) $(CFLAGS) -c $< -o $@

base64.o: base64.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

memcheck: $(TARGET)
	$(VALGRIND) ./$(TARGET)