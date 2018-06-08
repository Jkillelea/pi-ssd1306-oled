#include "ssd1306.h"

int main(int argc, char const *argv[]) {
    char msg[] = "potato!";
    SSD1306 display = SSD1306();

    display.clear();
    display.print("potato\n");
    // for (char ch = ' '; ch <= '`'; ch++) {
    //     display.putc(ch);
    // }

    return 0;
}
