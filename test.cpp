#include "ssd1306.h"

int main(int argc, char const *argv[]) {
    SSD1306 display = SSD1306();

    display.clear();
    display.print((char *)"P\tO\tT\tA\tT\tO\t!\n");
    for (char ch = ' '; ch <= '`'; ch++) {
        display.putc(ch);
    }

    return 0;
}
