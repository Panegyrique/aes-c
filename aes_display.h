#ifndef AES_DISPLAY_H
#define AES_DISPLAY_H

#include <stdint.h>

void print_state(const uint8_t state[STATE_ROW_SIZE][STATE_COL_SIZE], const char *label);
void AESEncryptDisplay(uint8_t ciphertext[DATA_SIZE], uint8_t plaintext[DATA_SIZE], uint8_t key[DATA_SIZE]);

#endif