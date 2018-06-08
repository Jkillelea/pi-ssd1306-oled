#include "ssd1306.h"

int main(int argc, char const *argv[]) {
    char msg[] = "POTATO!";
    SSD1306 display = SSD1306();

    display.clear();
    display.print((char *)msg);
    display.print((char *)msg);
    display.print((char *)msg);
    for (char ch = ' '; ch <= '`'; ch++) {
        display.putc(ch);
    }

    return 0;
}
