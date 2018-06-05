#include "tmp.h"

int main(int argc, char const *argv[]) {
    SSD1306 display = SSD1306();

    for (char i = 0; i < 256; i <<= 1) {
        printf("%d\n", i);
        display.clear();
        display.testdraw(i);
    }

    return 0;
}
