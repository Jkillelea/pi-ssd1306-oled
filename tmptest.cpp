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
    display.putc('p');
    display.putc('o');
    display.putc('t');
    display.putc('a');
    display.putc('t');
    display.putc('o');
    display.putc('!');

    return 0;
}
