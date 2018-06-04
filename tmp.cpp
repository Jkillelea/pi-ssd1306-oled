#include "tmp.h"

SSD1306::SSD1306(char *path, char addr) {
    D puts("SSD1306::SSD1306");
    this->i2c_addr = addr;

    D puts("open");
    this->display_fd = open(path, O_WRONLY);
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
    D puts("ioctl ok");    

    D puts("memset display_buffer");
    memset(this->display_buffer, 0, (size_t)(DISPLAY_ROWS * DISPLAY_COLS));    

    D printf("write(display_fd, init_seq, sizeof(init_seq)), sizeof(init_seq) = %lu\n", sizeof(init_seq));
    write(display_fd, init_seq, sizeof(init_seq));
}

uint SSD1306::print(const char *const msg) {
    return 0;
}

void SSD1306::clear() {
    D puts("clear");
   char send_buffer[DISPLAY_ROWS * DISPLAY_COLS] = {0}; // buffer we'll actually send
   send_buffer[0] = 0x40;

    D printf("memset(this->display_buffer, 0, sizeof(this->display_buffer)), sizeof(this->display_buffer) = %d\n", sizeof(this->display_buffer));
    memset(this->display_buffer, 0, sizeof(this->display_buffer)); // zero out display buffer

    D puts("write");
    write(this->display_fd, send_buffer, sizeof(send_buffer));
}

void SSD1306::testdraw() {
    D puts("testdraw");
    char send_buffer[DISPLAY_ROWS * DISPLAY_COLS] = {0}; // buffer we'll actually send
    send_buffer[0] = 0x40;

    D printf("memset(this->display_buffer, 0xFF, sizeof(this->display_buffer)), sizeof(this->display_buffer) = %d\n", sizeof(this->display_buffer));
    memset(this->display_buffer, 0xFF, sizeof(this->display_buffer)); // zero out display buffer

    D puts("write");
    write(this->display_fd, send_buffer, sizeof(send_buffer));
}

SSD1306::~SSD1306() {
    D puts("SSD1306::~SSD1306");
    if(this->display_fd > 0) {
        D puts("close");
        close(this->display_fd);
    }
}