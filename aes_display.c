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


void KeyGenDisplay(uint8_t roundkeys[][STATE_ROW_SIZE][STATE_COL_SIZE], uint8_t master_key[STATE_ROW_SIZE][STATE_COL_SIZE]){
        for(int round=0; round < ROUND_COUNT; round++){

            for (int j = 0; j < STATE_ROW_SIZE; j++) {
                for (int k = 0; k < STATE_COL_SIZE; k++) {
                    roundkeys[round][j][k] = (round == 0 ? master_key[j][k] : roundkeys[round-1][j][k]);
                }
            }

            ColumnFill(roundkeys, round);
            OtherColumnsFill(roundkeys, round);

            char label[50];
            sprintf(label, "Key round %d (4x4)", round);
            print_state(roundkeys[round], label);
    }
}


void AddRoundKeyDisplay(uint8_t state[STATE_ROW_SIZE][STATE_COL_SIZE], uint8_t roundkey[STATE_ROW_SIZE][STATE_COL_SIZE]){
    for(int i = 0; i < STATE_ROW_SIZE; i++){
        for(int j = 0; j < STATE_COL_SIZE; j++){
            state[i][j] ^= roundkey[i][j];
        }
    }
    print_state(state, "State after AddRoundKey (4x4)");
}


void SubBytesDisplay(uint8_t state[STATE_ROW_SIZE][STATE_COL_SIZE]){
    for(int i = 0; i < STATE_ROW_SIZE; i++){
        for(int j = 0; j < STATE_COL_SIZE; j++){
            uint8_t high_nibble = (state[i][j] >> 4) & 0x0F;
            uint8_t low_nibble = state[i][j] & 0x0F; 
            state[i][j] = sboxtab[(int)high_nibble * 16 + (int)low_nibble];
        }
    }
    print_state(state, "State after SubBytes (4x4)");
}


void ShiftRowsDisplay(uint8_t state[STATE_ROW_SIZE][STATE_COL_SIZE]){
    uint8_t temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    temp = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = temp;

    print_state(state, "State after ShiftRows (4x4)");
}


void MixColumnsDisplay(uint8_t state[STATE_ROW_SIZE][STATE_COL_SIZE]){
    for(int i=0; i < STATE_COL_SIZE; i++){
        uint8_t colonne[STATE_COL_SIZE] = {state[0][i], state[1][i], state[2][i], state[3][i]};
        MCMatrixColumnProduct(colonne);
        state[0][i] = colonne[0];
        state[1][i] = colonne[1];
        state[2][i] = colonne[2];
        state[3][i] = colonne[3];
    }
    print_state(state, "State after MixColumns (4x4)");
}