#include "tmp.h"

int main(int argc, char const *argv[]) {
    SSD1306 display = SSD1306();

    display.print("potato!");
    return 0;
}
