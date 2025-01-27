# AES 128-bits in C

## Set variables

In **main.c**, change the value of **plaintext** and **key**. They need to be declared as arrays :

``` C
// FIPS 197 example
// DATA_SIZE = 16 bytes

uint8_t plaintext[DATA_SIZE] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
uint8_t key[DATA_SIZE] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
```

Then, define the value of the constant **DISPLAY** also in **main.c** :

``` C
# define DISPLAY 1 // Set to 0 to avoid display
```

## Compile

Run the following command in the terminal :

``` bash
gcc main.c aes.c aes_display.c -o aes.exe
./aes.exe
```