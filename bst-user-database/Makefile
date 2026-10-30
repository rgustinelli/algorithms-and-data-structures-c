CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c11 -Iinclude
BUILD_DIR := build

SRC_DIR := src
TEST_DIR := tests

LIB_SOURCES := $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
MAIN_SOURCE := $(SRC_DIR)/main.c

TARGET := $(BUILD_DIR)/bst_user_database
TEST_BINARIES := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%, $(wildcard $(TEST_DIR)/*.c))

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(MAIN_SOURCE) $(LIB_SOURCES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TEST_BINARIES)
	@for bin in $(TEST_BINARIES); do \
		echo "Running $$bin"; \
		./$$bin || exit 1; \
	done

$(BUILD_DIR)/%: $(TEST_DIR)/%.c $(LIB_SOURCES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $< $(LIB_SOURCES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
