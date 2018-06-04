#pragma once


// #ifdef __cplusplus
// extern "C" {
// #endif
#include <stdio.h> // perror, puts, ect
#include <errno.h>
#include <unistd.h> // exit(2)
#include <sys/types.h> // open(2)
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h> // EXIT_FAILURE
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

// #ifdef __cplusplus
// } // extern "C"
// #endif

#include <string>


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

    SSD1306(char path[] = "/dev/i2c-1", char addr = 0x3C);
    ~SSD1306();

    void clear_display();

private:
    int display_fd;
    char i2c_addr;
    DisplayMode mode = DisplayMode::SCROLL;
    unsigned char display_buffer[8][128];
};