CC = gcc
CFLAGS = -std=c++11 -O3
BUILD_DIR = ./build

all: oled display-a | $(BUILD_DIR)
	gcc oled.cpp ssd1306.cpp -o oled -std=c++11

oled: $(BUILD_DIR)/oled.o $(BUILD_DIR)/ssd1306.o
	$(CC) $^ -o $@ $(CFLAGS)

display-a: $(BUILD_DIR)/display-a.o $(BUILD_DIR)/ssd1306.o
	$(CC) $^ -o $@ $(CFLAGS)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CC) -c $^ -o $@ $(CFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f oled
	rm -f display-a
	rm -r $(BUILD_DIR)

