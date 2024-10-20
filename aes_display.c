# include "aes.h"
# include "aes_display.h"
# include <stdio.h>


void print_state(const uint8_t state[STATE_ROW_SIZE][STATE_COL_SIZE], const char *label){
    printf("%s:\n", label);
    for(int i=0; i < STATE_ROW_SIZE; i++){
        for(int j=0; j < STATE_COL_SIZE; j++){
            printf("%02x ", state[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void AESEncryptDisplay(uint8_t ciphertext[DATA_SIZE], uint8_t plaintext[DATA_SIZE], uint8_t key[DATA_SIZE]){
    uint8_t state[STATE_ROW_SIZE][STATE_COL_SIZE];
    MessageToState(state, plaintext);
    printf("### Input ###\n\n");
    print_state(state, "Plaintext (4x4)");

    uint8_t master_key[STATE_ROW_SIZE][STATE_COL_SIZE];
    MessageToState(master_key, key);
    print_state(master_key, "Key (4x4)");

    uint8_t roundkeys[ROUND_COUNT][STATE_ROW_SIZE][STATE_COL_SIZE];
    KeyGen(roundkeys, master_key);

    uint8_t roundkey[STATE_ROW_SIZE][STATE_COL_SIZE];

    AddRoundKey(state, master_key);
    printf("### Round Init ###\n\n");
    print_state(master_key, "Round Key (4x4)");
    print_state(state, "State after AddRoundKey (4x4)");

    for(int i=0; i < ROUND_COUNT; i++){
        printf("### Round %d ###\n\n", i+1);

        SubBytes(state);
        print_state(state, "State after SubBytes (4x4)");

        ShiftRows(state);
        print_state(state, "State after ShiftRows (4x4)");

        if(i != 9){
            MixColumns(state);
            print_state(state, "State after MixColumns (4x4)");
        }

        GetRoundKey(roundkey, roundkeys, i);
        print_state(roundkey, "Round Key (4x4)");

        AddRoundKey(state, roundkey);
        print_state(state, "State after AddRoundKey (4x4)");
    }

    StateToMessage(ciphertext, state);
    printf("### Output ###\n\n");
    printf("Ciphertext (4x4)\n");
    for(int i=0; i < DATA_SIZE; i++){
        printf("%02x ", ciphertext[i]);
        if((i+1)%4 == 0){
            printf("\n");
        }
    }
}