#include "transaction.h"

transaction* transaction_create_empty() {
    transaction* ta = (transaction*)malloc(sizeof(transaction));

    if(ta == NULL) {
        return NULL;
    }

    memset(ta, 0, sizeof(transaction));

    return ta;
}

void transaction_destroy(transaction* ta) {
    free(ta);
}

int transaction_sign(transaction* ta, keypair* kp, int type) {
    long long unsigned int signed_message_len;

    switch(type) {
        case 0: //buyer
            if(strncmp((const char*)(ta->buyerpk), (const char*)(kp->pk), crypto_sign_PUBLICKEYBYTES) != 0) {
                return 1;
            }
            crypto_sign((unsigned char*)(ta->buyer_sig), &signed_message_len, (const unsigned char*)ta, TRANSACTION_SIGN_LEN, (const unsigned char*)kp->sk);
            break;

        case 1: //seller
            if(strncmp((const char*)(ta->sellerpk), (const char*)(kp->pk), crypto_sign_PUBLICKEYBYTES) != 0) {
                return 1;
            }
            crypto_sign((unsigned char*)(ta->seller_sig), &signed_message_len, (const unsigned char*)ta, TRANSACTION_SIGN_LEN, (const unsigned char*)kp->sk);
            break;

        default: //invalid
            return 1;
            break;
    }
    if(signed_message_len == crypto_sign_BYTES + TRANSACTION_SIGN_LEN) {
        return 0;
    } else {
        return signed_message_len;
    }
}

 int transaction_verify(transaction* ta, int type) {
    unsigned char unsigned_message[TRANSACTION_SIGN_LEN];
    long long unsigned int unsigned_message_len;

    switch(type) {
        case 0: //buyer
            if(crypto_sign_open(unsigned_message, &unsigned_message_len, (const unsigned char*)(ta->buyer_sig), crypto_sign_BYTES + TRANSACTION_SIGN_LEN, (const unsigned char*)ta->buyerpk) != 0) {
                return 1;
            }
            break;
        case 1: //seller
            if(crypto_sign_open(unsigned_message, &unsigned_message_len, (const unsigned char*)(ta->seller_sig), crypto_sign_BYTES + TRANSACTION_SIGN_LEN, (const unsigned char*)ta->sellerpk) != 0) {
                return 1;
            }
            break;

        default: //invalid
            return 1;
            break;
    }

    if(transaction_checkequal(ta, (transaction*)unsigned_message)) {
        return 1;
    } else {
        return 0;
    }
 }

int transaction_verify_full(transaction* ta) {
    int buyer = transaction_verify(ta, 0);

    if(buyer != 0) {
        return buyer;
    }

    int seller = transaction_verify(ta, 1);

    if(seller != 0) {
        return seller;
    }

    return 0;
}

int transaction_checkequal(transaction* ta1, transaction* ta2) {
    //we now the size and the structure is aligned to 4 bytes (a word) so we can use memcmp to compare
    
    return memcmp((const void*)ta1, (const void*)ta2, TRANSACTION_SIGN_LEN);
}