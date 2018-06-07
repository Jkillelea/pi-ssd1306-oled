#include "tmp.h"

int main(int argc, char const *argv[]) {
    SSD1306 display = SSD1306();

    display.clear();
    //display.print("potato!");
    // for (char ch = ' '; ch <= '`'; ch++) {
    //     display.putc(ch);
    // }
    // display.testdraw();
    // display.every_pixel();
    display.putc('P');
    display.putc('O');
    display.putc('T');
    display.putc('A');
    display.putc('T');
    display.putc('O');
    display.putc('!');

    return 0;
}
