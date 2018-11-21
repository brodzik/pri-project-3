TARGET = app

CXX = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

SOURCE_DIR = src
HEADER_DIR = src
BUILD_DIR = build

SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)

.PHONY: release
release: dirs
	$(MAKE) all

.PHONY: dirs
dirs:
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	$(RM) -rf $(BUILD_DIR)

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CXX) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@

