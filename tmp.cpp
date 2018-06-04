#include "tmp.h"

SSD1306::SSD1306(char *path, char addr) {
    D puts("SSD1306::SSD1306");
    this->i2c_addr = addr;
    this->display_fd = open(path, O_WRONLY);
    D puts("open");
    if (this->display_fd < 0) { // open file
        perror("open(2)");
        exit(EXIT_FAILURE);
    }
    D puts("open ok");
    D puts("ioctl");    
    if (ioctl(this->display_fd, I2C_SLAVE, this->i2c_addr) < 0) { // i2c device
            perror("ioctl(2)");
            exit(EXIT_FAILURE);
    }

    D puts("memset display_buffer");
    memset(this->display_buffer, 0, (size_t)(DISPLAY_ROWS*DISPLAY_COLS));    

    D printf("sizeof(init_seq) = %lu\n", sizeof(init_seq));
    write(display_fd, init_seq, sizeof(init_seq));
    
}

SSD1306::~SSD1306() {
    D puts("SSD1306::~SSD1306");
    if(this->display_fd > 0) {
        D puts("close");
        close(this->display_fd);
    }
}