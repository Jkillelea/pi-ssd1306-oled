#include "tmp.h"

int main(int argc, char const *argv[]) {
    SSD1306 display = SSD1306();

    display.clear();
    for (char ch = ' '; ch <= 'Z'; ch++) {
        display.putc(ch);
    }
    // display.testdraw();
    // display.every_pixel();

    return 0;
}
