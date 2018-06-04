#include <unistd.h>        // Needed for I2C port
#include <fcntl.h>         // |
#include <sys/ioctl.h>     // |
#include <linux/i2c-dev.h> // |
#include <stdio.h>
#include <string.h>


int main() {
    char file_path[] = "/dev/i2c-1";
    char display_addr = 0x3C;
    int fd;
    
    if ((fd = open(file_path, O_WRONLY) < 0))
        return -1;
    
    if (ioctl(fd, I2C_SLAVE, display_addr) < 0)
        return -1;

    // initialise the display
    unsigned char init_seq[26] = {0x00,0xAE,0xA8,0x3F,0xD3,0x00,0x40,0xA1,0xC8,0xDA,0x12,0x81,0x7F,
                                          0xA4,0xA6,0xD5,0x80,0x8D,0x14,0xD9,0x22,0xD8,0x30,0x20,0x00,0xAF};

    write(fd, init_seq, sizeof(init_seq));

    // set the range we want to use (whole display)
    unsigned char set_full_range[7] = {0x00,0x21,0x00,0x7F,0x22,0x00,0x07};
    write(fd, set_full_range, sizeof(set_full_range));

    // send the letter A to the display
    unsigned char letter_A[5] = {0x40,0x7E,0x12,0x12,0x7E};
    write(fd, letter_A, sizeof(letter_A));

    if (fd > 0)
        return close(fd);
}



