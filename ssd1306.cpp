// tmp.cpp - An interface for the SSD1306 display driver chip
#include "ssd1306.h"
#include "charmap.h"

/* Init object, open file, zero out data buffer */
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
             "sizeof(init_seq) = %zu\n", sizeof(init_seq));
    if (write(this->display_fd, init_seq, sizeof(init_seq)) != sizeof(init_seq)) {
        perror("writing init sequence failed");
        exit(EXIT_FAILURE);
    }
}

size_t SSD1306::print(char *msg) { // null terminated string
    D printf("print(%s)\n", msg);

    *this->cmd = (1 << 6);
    while (*msg) {
        if (!handle_ctrl_char(*msg)) { // if not control char
            char *bitmap;
            if (*msg <= '`') // uppercase ASCII -> subtract one space to get offset
                bitmap = charmap[*msg - ' '];
            else                                    // convert lowercase to upercase by 
                bitmap = charmap[*msg - ' ' - ' ']; // subtracting space twice (ascii math)

            // see if there's enough space on this line for character
            if ((DISPLAY_COLS - BITMAP_SIZE*this->cursor_col) < BITMAP_SIZE) {
                newline(); // if not, newline
            }
            D printf("row %d, col %d\n", this->cursor_row, this->cursor_col);

            size_t offset = (this->cursor_row * DISPLAY_COLS) 
                            + (this->cursor_col * BITMAP_SIZE);

            memcpy(&this->display_buffer[offset], bitmap, BITMAP_SIZE);
            this->cursor_col++; // increment cursor

            D {
                printf("\n");
                for (int i = 0; i < BITMAP_SIZE; i++) {
                    printf("%#08x\n", bitmap[i]);
                }
            }
        }
        msg++;
    }

    return send();
}

size_t SSD1306::println(char *msg) {
    size_t nbytes = print(msg);
    newline();
    return nbytes+1;
}

void SSD1306::newline() {
    D puts("newline");
    this->cursor_col = 0;
    this->cursor_row++;
}

size_t SSD1306::putc(char ch) {
    D puts("putc");
    const char *bitmap = charmap[ch - ' ']; // get bitmap
    // see if there's enough space on this line for character
    if ((DISPLAY_COLS - BITMAP_SIZE*this->cursor_col) < BITMAP_SIZE) {
        newline(); // if not, newline
    }
    D printf("row %d, col %d\n", this->cursor_row, this->cursor_col);
    // use row and col to get buffer offset
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
        const char *data = charmap[c - ' '];
        memcpy(this->display_buffer, data, charsize);
        send();
    }
    
}

void SSD1306::every_pixel() {
    D puts("testdraw");
    // *this->cmd = (1 << 6); // data only
    *this->cmd = 0x40;
    for (uint i = 0; i < DISPLAY_ROWS; i++) {
        D printf("row %d\n", i);
        for (uint j = 0; j < DISPLAY_COLS; j++) {
            for (uint k = 0; k < 8; k++) {
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

bool SSD1306::handle_ctrl_char(char ch) {
    switch (ch) {
        case '\n':
            newline();
            return true;
        case '\t':
            this->cursor_col += 2;
            return true;
        case '\r':
            this->cursor_col = 0;
            return true;
    }
    return false;
}

SSD1306::~SSD1306() {
    D puts("SSD1306::~SSD1306");
    if(this->display_fd > 0) {
        D puts("close");
        close(this->display_fd);
    }
}
