CC = g++
CFLAGS = -std=c++11 -O3 -D DEBUG
CFLAGS += -O3
# CFLAGS += -D DEBUG
BUILD_DIR = ./build
EXECS = oled display-a tmptest 

all: $(EXECS) | $(BUILD_DIR)

oled: $(BUILD_DIR)/oled.o $(BUILD_DIR)/ssd1306.o
	$(CC) $^ -o $@ $(CFLAGS)

tmptest: $(BUILD_DIR)/tmptest.o $(BUILD_DIR)/tmp.o
	$(CC) $^ -o $@ $(CFLAGS)

display-a: $(BUILD_DIR)/display-a.o $(BUILD_DIR)/ssd1306.o
	$(CC) $^ -o $@ $(CFLAGS)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CC) -c $^ -o $@ $(CFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(EXECS)
	rm -r $(BUILD_DIR)

