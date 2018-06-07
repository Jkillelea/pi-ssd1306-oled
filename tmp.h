#pragma once

#include <stdio.h>         // perror, puts, ect
#include <errno.h>
#include <unistd.h>        // exit(2)
#include <sys/types.h>     // open(2)
#include <sys/stat.h>      // |
#include <fcntl.h>         // | 
#include <stdlib.h>        // EXIT_FAILURE
#include <sys/ioctl.h>     // ioctl(2)
#include <linux/i2c-dev.h> // I2C_SLAVE
#include <string.h>        // memset(2)
#include <stdint.h>

#ifdef DEBUG
 #define D if(1) 
#else
 #define D if(0) 
#endif

class SSD1306 {
public:
    enum class DisplayMode {
        SCROLL,
        WRAP
    };

    SSD1306(char path[] = (char *)"/dev/i2c-1", char addr = 0x3C);
    ~SSD1306();

    void testdraw();
    void every_pixel();
#ifdef putc // putc is defined in stdio.h as a macro
#undef putc
#endif
    void newline();
    size_t putc(char ch);
    size_t print(const char *const msg);
    void clear();

private:
    uint32_t cursor_row = 0;
    uint32_t cursor_col = 0;

    size_t send(); // write out the data

    static const uint32_t DISPLAY_ROWS = 8;
    static const uint32_t DISPLAY_COLS = 128;
    int display_fd;
    uint8_t i2c_addr;
    // DisplayMode mode = DisplayMode::SCROLL;
    /* send_buffer holds all the data
     * cmd is a pointer to the first element
     * display_buffer is a pointer to the second (and all the elements thereafter)
     */
    uint8_t send_buffer[DISPLAY_ROWS * DISPLAY_COLS + 1] = {0};
    uint8_t *cmd = send_buffer;                // first byte is command
    uint8_t *display_buffer = send_buffer + 1; // remaining is screen data

    // ssd1306 command sequences
    uint8_t init_seq[26] = {0x00,0xAE,0xA8,0x3F,
                            0xD3,0x00,0x40,0xA1,
                            0xC8,0xDA,0x12,0x81,
                            0x7F,0xA4,0xA6,0xD5,
                            0x80,0x8D,0x14,0xD9,
                            0x22,0xD8,0x30,0x20,
                            0x00,0xAF};

    uint8_t set_full_range_seq[7] = {0x00,0x21,0x00,0x7F,
                                           0x22,0x00,0x07};

    uint8_t scroll_up_seq[3] = {0x00,0xD3,0x08};
};
