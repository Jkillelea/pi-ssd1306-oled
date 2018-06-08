CC = g++
CFLAGS = -std=c++11
CFLAGS += -O3
CFLAGS += -D DEBUG
BUILD_DIR = ./build
EXECS = clear test

all: $(EXECS) | $(BUILD_DIR)

test: $(BUILD_DIR)/test.o $(BUILD_DIR)/ssd1306.o
	$(CC) $^ -o $@ $(CFLAGS)

clear: $(BUILD_DIR)/clear.o $(BUILD_DIR)/ssd1306.o
	$(CC) $^ -o $@ $(CFLAGS)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CC) -c $^ -o $@ $(CFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(EXECS)
	rm -r $(BUILD_DIR)

