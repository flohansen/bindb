CC ?= gcc

CFLAGS = -Wall -Wextra
DIST_DIR = dist
TARGET = $(DIST_DIR)/bindb
SRCS = src/main.c src/lexer.c
OBJS = $(patsubst src/%.c,$(DIST_DIR)/%.o, $(SRCS))

$(shell mkdir -p $(DIST_DIR))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

$(DIST_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
