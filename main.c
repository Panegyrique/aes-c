# include "aes.h"
# define DISPLAY 1 // Set to 0 to avoid display

# if defined(DISPLAY) && (DISPLAY == 1)
    # include "aes_display.h"
# endif


int main() {
    uint8_t plaintext[DATA_SIZE] = {
        0x32, 0x88, 0x31, 0xe0, 
        0x43, 0x5a, 0x31, 0x37, 
        0xf6, 0x30, 0x98, 0x07, 
        0xa8, 0x8d, 0xa2, 0x34
    };

    uint8_t key[DATA_SIZE] = {
        0x2b, 0x28, 0xab, 0x09, 
        0x7e, 0xae, 0xf7, 0xcf, 
        0x15, 0xd2, 0x15, 0x4f, 
        0x16, 0xa6, 0x88, 0x3c
    };

    uint8_t ciphertext[DATA_SIZE];

    # if defined(DISPLAY) && (DISPLAY == 0)
        AESEncrypt(ciphertext, plaintext, key);
    # endif

    # if defined(DISPLAY) && (DISPLAY == 1)
        AESEncryptDisplay(ciphertext, plaintext, key);
    # endif

    return 0;
}