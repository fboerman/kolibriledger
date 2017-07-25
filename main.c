#include <stdio.h>
#include <string.h>
#include <sodium.h>
#include "keypair.h"

int main(int argc, const char * argv[]) {
    if(sodium_init() == -1) {
        printf("Sodium not initialized!\n");
        return 1;
    }
    keypair* kp = keypair_generate();
    keypair_save("testkey", kp);
    keypair_destroy(kp);

    kp = keypair_load("testkey");
    keypair_save("testkey2", kp);
    keypair_destroy(kp);

    return 0;
}