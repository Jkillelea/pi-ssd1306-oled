// tmp.cpp - An interface for the SSD1306 display driver chip
#include "tmp.h"
#include "charmap.h"


/* Init object, open file, zero out data buffer
 */
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

    D printf("write(display_fd, init_seq, sizeof(init_seq)), "
             "sizeof(init_seq) = %lu\n", sizeof(init_seq));
    write(this->display_fd, init_seq, sizeof(init_seq));
}

size_t SSD1306::print(const char *const msg) {
    return 0;
}

size_t SSD1306::putc(char ch) {
    char *bitmap = charmap[ch - ' '];
    size_t bitmap_size = BITMAP_SIZE;
    
    if ((DISPLAY_COLS - this->cursor_col) < BITMAP_SIZE) {
        this->cursor_col = 0;
        this->cursor_row++;
    }

    printf("row %d, col %d\n" this->cursor_row, this->cursor_col);

    size_t offset = (this->cursor_row * DISPLAY_COLS) 
                    + (this->cursor_col * BITMAP_SIZE);

    memcpy(&this->display_buffer[offset], bitmap, BITMAP_SIZE);
    this->cursor_col++;

    return send();
}

void SSD1306::clear() {
    D puts("clear");
    this->cursor_col = 0;
    this->cursor_row = 0;

    *(this->cmd) = (1 << 6); // data only
    D puts("memset(this->display_buffer, 0, DISPLAY_ROWS * DISPLAY_COLS)");
    memset(this->display_buffer, 0, DISPLAY_ROWS*DISPLAY_COLS); // zero out display buffer
    send();
}

void SSD1306::testdraw() {
    D puts("testdraw");
    *this->cmd = (1 << 6); // data only

    size_t charsize = 6*sizeof(char); // bytes
    for(char c = ' '; c <= '`'; c++) {
        clear();
        char *data = charmap[c - ' '];
        memcpy(this->display_buffer, data, charsize);
        send();
    }
    
}

void SSD1306::every_pixel() {
    D puts("testdraw");
    // *this->cmd = (1 << 6); // data only
    *this->cmd = 0x40;
    for (int i = 0; i < DISPLAY_ROWS; i++) {
        D printf("row %d\n", i);
        for (int j = 0; j < DISPLAY_COLS; j++) {
            for (int k = 0; k < 8; k++) {
                this->display_buffer[i*DISPLAY_COLS + j] |= (1 << k);
                send();
            }
        }
    }
}


size_t SSD1306::send() {
    D puts("write");
    size_t nbytes_written;
    if((nbytes_written = write(this->display_fd, 
                               this->send_buffer, 
                               sizeof(this->send_buffer))) < 0) {
        perror("write(2) failed:");
        exit(EXIT_FAILURE);
    }
    return nbytes_written;
}

SSD1306::~SSD1306() {
    D puts("SSD1306::~SSD1306");
    if(this->display_fd > 0) {
        D puts("close");
        close(this->display_fd);
    }
}
