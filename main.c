# include "aes.h"
# define DISPLAY 1 // Set to 0 to avoid display

# if defined(DISPLAY) && (DISPLAY == 1)
    # include "aes_display.h"
# endif


int main() {
    uint8_t plaintext[DATA_SIZE] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    uint8_t key[DATA_SIZE] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    uint8_t ciphertext[DATA_SIZE];

    # if defined(DISPLAY) && (DISPLAY == 0)
        AESEncrypt(ciphertext, plaintext, key);
    # endif

    # if defined(DISPLAY) && (DISPLAY == 1)
        AESEncryptDisplay(ciphertext, plaintext, key);
    # endif

    return 0;
}