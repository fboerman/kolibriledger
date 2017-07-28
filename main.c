#include <stdio.h>
#include <string.h>
#include <sodium.h>
#include <time.h>
#include "keypair.h"
#include "transaction.h"

int main(int argc, const char * argv[]) {
    if(sodium_init() == -1) {
        printf("Sodium not initialized!\n");
        return 1;
    }
    
    keypair* kpbuyer = keypair_generate();
    keypair* kpseller = keypair_generate();
    //keypair_save("testkeybuyer", kpbuyer);
    //keypair_save("testkeyseller", kpseller);

    transaction* ta = transaction_create_empty();
    memcpy(ta->buyerpk, kpbuyer->pk, crypto_sign_PUBLICKEYBYTES);
    memcpy(ta->sellerpk, kpseller->pk, crypto_sign_PUBLICKEYBYTES);
    ta->timestamp = (unsigned long int)time(NULL);
    memcpy(ta->bought, "grain", 5);
    memcpy(ta->sold, "cash", 4);
    ta->ammount_bought = 5;
    ta->ammount_sold = 10;

    transaction_sign(ta, kpbuyer, 0);
    transaction_sign(ta, kpseller, 1);

    char* ta_str_core = transaction_getstring_core(ta);
    char* ta_str_full = transaction_getstring_full(ta);
    printf("%s\n\n", ta_str_core);
    printf("%s\n\n", ta_str_full);

    free(ta_str_core);
    free(ta_str_full);
    keypair_destroy(kpbuyer);
    keypair_destroy(kpseller);
    transaction_destroy(ta);

    return 0;
}