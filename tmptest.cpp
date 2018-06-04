#include "tmp.h"

int main(int argc, char const *argv[]) {
    SSD1306 display = SSD1306();

    display.clear();
    display.testdraw();
    // display.clear();

    return 0;
}
